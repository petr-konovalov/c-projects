#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

typedef enum {Ago = 0, Forward = 1} Direction;

typedef enum {Undefined = 0, Solvable = 1, NotSolvable = -1} ProblemStatus;

typedef struct
{
    int BlockNumber;
    int step;
    Direction direction;
    ProblemStatus status;
} Problem;

typedef enum {Vertical = 0, Horizontal = 1} Orientation;

typedef struct
{
    int x;
    int y;
    int size;
    Orientation orientation;

    int problemsCount;
    Problem problems[64];
} Block;

void getBlocks(Block **blocks, int *blocksCount)
{
    int i = 0;

    printf("enter blocks count: ");
    scanf("%i", blocksCount);
    (*blocks) = new Block[*blocksCount];

    for (i = 0; i < *blocksCount; ++i)
    {
        char orientation = 'h';

        printf("enter block(x y size orientation(v|h)): ");
        scanf("%i %i %i %c", &(*blocks)[i].x, &(*blocks)[i].y, &(*blocks)[i].size, &orientation);

        (*blocks)[i].orientation = orientation == 'v' ? Vertical : Horizontal;
        (*blocks)[i].problemsCount = 0;
    }
}

void getBlocksMapSize(int *height, int *width)
{
    printf("enter height: ");
    scanf("%i", height);
    printf("enter width: ");
    scanf("%i", width);
}

void getProblem(Problem *problem)
{
    char direction;
    printf("enter problem(block_number direction(f|a) step): ");
    scanf("%i %c %i", &problem->BlockNumber, &direction, &problem->step);
    problem->direction = direction == 'f' ? Forward : Ago;
}

void drawBlock(const Block *block, int **blocksMap, const int index)
{
    int x = block->x;
    int y = block->y;
    int ex = block->x + (block->orientation == Horizontal ? block->size : 1);
    int ey = block->y + (block->orientation == Vertical ? block->size : 1);

    for (x = block->x; x < ex; ++x)
        for (y = block->y; y < ey; ++y)
            blocksMap[y][x] = index;
}

void createBlocksMap(const Block *blocks, const int blocksCount, const int height, const int width, int ***blocksMap)
{
    int i = 0;
    int j = 0;

    (*blocksMap) = new int*[height];
    for (i = 0; i < height; ++i)
    {
        (*blocksMap)[i] = new int[width];
        for (j = 0; j < width; ++j)
            (*blocksMap)[i][j] = 0;
    }

    for (i = 0; i < blocksCount; ++i)
        drawBlock(blocks + i, *blocksMap, i + 1);
}

void printBlocksMap(const int height, const int width, int **blocksMap)
{
    int x;
    int y;

    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
            printf("%3i", blocksMap[y][x]);
        printf("\n");
    }
}

void freeBlocksMap(const int height, const int width, int **blocksMap)
{
    int i = 0;

    for (i = 0; i < height; ++i)
        free(blocksMap[i]);
    free(blocksMap);
}

typedef struct Node
{
    Problem problem;
    struct Node *child;
    struct Node *sibling;
} ProblemTree;

void addChild(ProblemTree *tree, ProblemTree *child)
{
    child->sibling = tree->child;
    tree->child = child;
}

ProblemTree *createProblemsTree(const int height, const int width, int **blockMap, const Problem *problem,
                                Block *blocks);

int initializeCoordinateHorizontal(int *x, int *y, int *ex, int *dx, const Problem *problem, const Block *block)
{
    *y = block->y;
    if (problem->direction)
    {
        *x = block->x + block->size;
        *ex = *x + problem->step;
    }
    else
    {
        *x = block->x - 1;
        *ex = *x - problem->step;
        *dx = -1;
    }
}

int createNewProblemHorizontal(ProblemTree *tree, const int height, const int width, int **blockMap,
                               const Problem *problem, Block *blocks, const int x, const int y)
{
    Problem newProblem;
    newProblem.BlockNumber = blockMap[y][x] - 1;
    if (blocks[blockMap[y][x] - 1].orientation == Vertical)
    {
        newProblem.direction = Forward;
        newProblem.step = y - blocks[blockMap[y][x] - 1].y + 1;
        addChild(tree, createProblemsTree(height, width, blockMap, &newProblem, blocks));
        newProblem.direction = Ago;
        newProblem.step = (blocks[blockMap[y][x] - 1].y + blocks[blockMap[y][x] - 1].size) - y;
        addChild(tree, createProblemsTree(height, width, blockMap, &newProblem, blocks));
        if (tree->child->problem.status == NotSolvable && tree->child->sibling->problem.status == NotSolvable)
        {
            tree->problem.status = NotSolvable;
            return 1;
        }
    }
    else
    {
        newProblem.direction = problem->direction;
        if (problem->direction)
            newProblem.step = blocks[problem->BlockNumber].x + blocks[problem->BlockNumber].size + problem->step - x;
        else
            newProblem.step = x - blocks[problem->BlockNumber].x + problem->step + 1;
        addChild(tree, createProblemsTree(height, width, blockMap, &newProblem, blocks));
        if (tree->child->problem.status == NotSolvable)
        {
            tree->problem.status = NotSolvable;
            return 1;
        }
    }
    return 0;
}

void checkHorizontal(ProblemTree *tree, const int height, const int width, int **blockMap,
                     const Problem *problem, Block *blocks)
{
    int x = 0;
    int y = 0;
    int ex = 0;
    int dx = 1;
    int b = 1;
    int p = -1;
    initializeCoordinateHorizontal(&x, &y, &ex, &dx, problem, blocks + problem->BlockNumber);
    if (ex < -1 || ex > width)
    {
        tree->problem.status = NotSolvable;
        return;
    }
    while (x != ex)
    {
        if (blockMap[y][x] && blockMap[y][x] != p)
        {
            if (createNewProblemHorizontal(tree, height, width, blockMap, problem, blocks, x, y))
                return;
            b = 0;
            p = blockMap[y][x];
        }
        x += dx;
    }
    if (b)
        tree->problem.status = Solvable;
}

int initializeCoordinateVertical(int *x, int *y, int *ey, int *dy, const Problem *problem, const Block *block)
{
    *x = block->x;
    if (problem->direction)
    {
        *y = block->y + block->size;
        *ey = *y + problem->step;
    }
    else
    {
        *y  = block->y - 1;
        *ey = *y - problem->step;
        *dy = -1;
    }
}

int createNewProblemVertical(ProblemTree *tree, const int height, const int width, int **blockMap,
                             const Problem *problem, Block *blocks, const int x, const int y)
{
    Problem newProblem;
    newProblem.BlockNumber = blockMap[y][x] - 1;
    if (blocks[blockMap[y][x] - 1].orientation == Horizontal)
    {
        newProblem.direction = Forward;
        newProblem.step = x - blocks[blockMap[y][x] - 1].x + 1;
        addChild(tree, createProblemsTree(height, width, blockMap, &newProblem, blocks));
        newProblem.direction = Ago;
        newProblem.step = (blocks[blockMap[y][x] - 1].x + blocks[blockMap[y][x] - 1].size) - x;
        addChild(tree, createProblemsTree(height, width, blockMap, &newProblem, blocks));
        if (tree->child->problem.status == NotSolvable && tree->child->sibling->problem.status == NotSolvable)
        {
            tree->problem.status = NotSolvable;
            return 1;
        }
    }
    else
    {
        newProblem.direction = problem->direction;
        if (problem->direction)
            newProblem.step = blocks[problem->BlockNumber].y + blocks[problem->BlockNumber].size + problem->step - y;
        else
            newProblem.step = y - blocks[problem->BlockNumber].y + problem->step + 1;
        addChild(tree, createProblemsTree(height, width, blockMap, &newProblem, blocks));
        if (tree->child->problem.status == NotSolvable)
        {
            tree->problem.status = NotSolvable;
            return 1;
        }
    }
    return 0;
}

void checkVertical(ProblemTree *tree, const int height, const int width, int **blockMap,
                   const Problem *problem, Block *blocks)
{
    int x = 0;
    int y = 0;
    int ey = 0;
    int dy = 1;
    int b = 1;
    int p = -1;
    initializeCoordinateVertical(&x, &y, &ey, &dy, problem, blocks + problem->BlockNumber);
    if (ey < -1 || ey > height)
    {
        tree->problem.status = NotSolvable;
        return;
    }
    while (y != ey)
    {
        if (blockMap[y][x] && blockMap[y][x] != p)
        {
            if (createNewProblemVertical(tree, height, width, blockMap, problem, blocks, x, y))
                return;
            b = 0;
            p = blockMap[y][x];
        }
        y += dy;
    }
    if (b)
        tree->problem.status = Solvable;
}

int compareProblem(const Problem *firstProblem, const Problem *secondProblem)
{
    if (firstProblem->BlockNumber == secondProblem->BlockNumber &&
        firstProblem->direction == secondProblem->direction &&
        firstProblem->step == secondProblem->step)
        return 1;

    return 0;
}

int findProblem(const Problem *problem, const Block *block)
{
    int i = 0;
    for (i = 0; i < block->problemsCount; ++i)
    {
        if (compareProblem(block->problems + i, problem))
        {
            if (block->problems[i].status == NotSolvable)
                return -1;
            return 1;
        }
    }

    return 0;
}

void changeProblemStatus(const Problem *problem, Block *block, const ProblemStatus newStatus)
{
    int i = 0;
    for (i = 0; i < block->problemsCount; ++i)
    {
        if (compareProblem(block->problems + i, problem))
        {
            block->problems[i].status = newStatus;
            return;
        }
    }
}

int addProblem(const Problem *problem, Block *block)
{
    block->problems[block->problemsCount++] = *problem;
}

ProblemTree *createProblemsTree(const int height, const int width, int **blockMap, const Problem *problem,
                                Block *blocks)
{
    int r = 0;
    ProblemTree *tree =new ProblemTree;
    tree->child = NULL;
    tree->sibling = NULL;
    tree->problem = *problem;
    tree->problem.status = Undefined;
    if (r = findProblem(problem, blocks + problem->BlockNumber))
    {
        if (r == -1)
            tree->problem.status = NotSolvable;
        return tree;
    }
    addProblem(problem, blocks + problem->BlockNumber);
    if (blocks[problem->BlockNumber].orientation)
        checkHorizontal(tree, height, width, blockMap, problem, blocks);
    else
        checkVertical(tree, height, width, blockMap, problem, blocks);
    changeProblemStatus(problem, blocks + problem->BlockNumber, tree->problem.status);

    return tree;
}

void destroyProblemTree(ProblemTree **tree)
{
    if (*tree)
    {
        destroyProblemTree(&(*tree)->child);
        destroyProblemTree(&(*tree)->sibling);
        free(*tree);
        *tree = NULL;
    }
}

void printProblem(const Problem *problem)
{
    printf("[%i %c %i %c]", problem->BlockNumber, problem->direction == Forward ? 'f' : 'a', problem->step,
           problem->status == Solvable ? 's' : problem->status == NotSolvable ? 'n' : 'u');
}

void printBlockProblem(const Block *block)
{
    int i;
    for (i = 0; i < block->problemsCount; ++i)
        printProblem(block->problems + i);
}

void printBlocksProblem(const int blockCount, const Block *blocks)
{
    int i;
    for (i = 0; i < blockCount; ++i)
    {
        printf("%i: ", i);
        printBlockProblem(blocks + i);
        printf("\n");
    }
}

void printTree(ProblemTree *tree)
{
    if (!tree)
        return;
    printTree(tree->sibling);
    printProblem(&tree->problem);
    if (tree->child)
    {
        printf("(");
        printTree(tree->child);
        printf(")");
    }
}

void problemTreeGetProblems(ProblemTree *tree, queue<Problem> *problems)
{
    queue<ProblemTree*> q;
    q.push(tree);

    while (!q.empty())
    {
        ProblemTree *currentNode = q.front();
        if (currentNode->problem.status == Solvable)
            problems->push(currentNode->problem);
        q.pop();
        for (ProblemTree *child = currentNode->child; child != NULL; child = child->sibling)
            if (child->problem.status != NotSolvable)
                q.push(child);
    }
}

void executeProblem(Block *block, Problem *problem, int **blockMap, Problem *mainProblem)
{
    if (mainProblem->BlockNumber == problem->BlockNumber)
        if (mainProblem->direction == problem->direction)
            mainProblem->step -= problem->step;
        else
            mainProblem->step += problem->step;
    drawBlock(block, blockMap, 0);
    if (block->orientation)
    {
        if (problem->direction)
            block->x += problem->step;
        else
            block->x -= problem->step;
    }
    else
    {
        if (problem->direction)
            block->y += problem->step;
        else
            block->y -= problem->step;
    }
    drawBlock(block, blockMap, problem->BlockNumber + 1);
}

void cancelProblem(Block *block, Problem *problem, int **blockMap, Problem *mainProblem)
{
    if (mainProblem->BlockNumber == problem->BlockNumber)
        if (mainProblem->direction == problem->direction)
            mainProblem->step += problem->step;
        else
            mainProblem->step -= problem->step;
    drawBlock(block, blockMap, 0);
    if (block->orientation)
    {
        if (problem->direction)
            block->x -= problem->step;
        else
            block->x += problem->step;
    }
    else
    {
        if (problem->direction)
            block->y -= problem->step;
        else
            block->y += problem->step;
    }
    drawBlock(block, blockMap, problem->BlockNumber + 1);
}

typedef struct Solve
{
    int length;
    Problem moves[1024];
} Solve;

void initializeSolve(Solve &solve)
{
    solve.length = 0;
}

void addMove(Solve &solve, const Problem move)
{
    solve.moves[solve.length++] = move;
}

void popMove(Solve &solve)
{
    --solve.length;
}

void copySolve(Solve &dest, const Solve &source)
{
    for (int i = 0; i < source.length; ++i)
        dest.moves[i] = source.moves[i];
    dest.length = source.length;
}

void printSolve(const Solve &solve)
{
    for (int i = 0; i < solve.length; ++i)
        printProblem(solve.moves + i);
    printf("\n");
}

void drawSolve(Solve &solve,int height, int width, int **blockMap, Block *blocks)
{
    Problem problem;
    problem.BlockNumber = -1;
    printBlocksMap(height, width, blockMap);
    for (int i = 0; i < solve.length; ++i)
    {
        printf("\n");
        executeProblem(&blocks[solve.moves[i].BlockNumber], solve.moves + i, blockMap, &problem);
        printBlocksMap(height, width, blockMap);
    }
}

void clearBlocksProblem(Block *blocks, const int blocksCount)
{
    for (int i = 0; i < blocksCount; ++i)
        blocks[i].problemsCount = 0;
}

void calcProblem(const int height, const int width, int **blockMap, Problem *mainProblem,
                 Block *blocks, const int blocksCount, Solve &solve, Solve &optimalSolve)
{
    if (solve.length > optimalSolve.length)
        return;

    clearBlocksProblem(blocks, blocksCount);
    ProblemTree *tree = createProblemsTree(height, width, blockMap, mainProblem, blocks);
    if (tree->problem.status == Solvable)
    {
        addMove(solve, tree->problem);
        if (solve.length < optimalSolve.length)
            copySolve(optimalSolve, solve);
        popMove(solve);
    }
    else
    {
        queue<Problem> problems;
        problemTreeGetProblems(tree, &problems);
        while (!problems.empty())
        {
            executeProblem(&blocks[problems.front().BlockNumber], &problems.front(), blockMap, mainProblem);
            addMove(solve, problems.front());
            calcProblem(height, width, blockMap, mainProblem, blocks, blocksCount, solve, optimalSolve);
            popMove(solve);
            cancelProblem(&blocks[problems.front().BlockNumber], &problems.front(), blockMap, mainProblem);
            problems.pop();
        }
    }
    destroyProblemTree(&tree);
}

void solveProblem(const int height, const int width, int **blockMap, Problem *mainProblem,
                  Block *blocks, int blocksCount, Solve &optimalSolve)
{
    Solve solve;
    optimalSolve.length = 128;
    initializeSolve(solve);
    calcProblem(height, width, blockMap, mainProblem, blocks, blocksCount, solve, optimalSolve);
}

int main()
{
    Block *blocks = NULL;
    int blocksCount = 0;

    int **blocksMap = NULL;
    int height = 0;
    int width = 0;
    int minSolve = 50;

    Problem mainProblem;

    getBlocks(&blocks, &blocksCount);
    getBlocksMapSize(&height, &width);
    createBlocksMap(blocks, blocksCount, height, width, &blocksMap);
    printBlocksMap(height, width, blocksMap);
    getProblem(&mainProblem);

    Solve optimalSolve;
    solveProblem(height, width, blocksMap, &mainProblem, blocks, blocksCount, optimalSolve);
    printSolve(optimalSolve);
    drawSolve(optimalSolve, height, width, blocksMap, blocks);

    free(blocks);
    freeBlocksMap(height, width, blocksMap);
    return 0;
}
