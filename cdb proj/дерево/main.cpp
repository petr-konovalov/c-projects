#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdlib.h>

using namespace std;

struct Tree
{
    int id;
    int value;
    Tree *left;
    Tree *right;
};

struct List
{
    int value;
    List *next;
};

void addTree(Tree **tree, int id, int value)
{
    if (!(*tree))
    {
        (*tree) = new Tree;
        (*tree)->id = id;
        (*tree)->value = value;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
    }
    else
    {
        if (id < (*tree)->id)
            addTree(&(*tree)->left, id, value);
        else if (id > (*tree)->id)
            addTree(&(*tree)->right, id, value);
    }
}

void showTree(Tree *tree, const int depth)
{
    if (tree)
    {
        showTree(tree->right, depth + 1);
        cout << setw(depth * 8) << tree->id << '(' << tree->value << ')' << endl;
        showTree(tree->left, depth + 1);
    }
}

void deleteTree(Tree **tree)
{
    Tree *newTree = NULL;
    if (!(*tree)->left)
        newTree = (*tree)->right;
    else if(!(*tree)->right)
        newTree = (*tree)->left;
    else
    {
        newTree = (*tree)->left;
        if (newTree->right)
        {
            while (newTree->right->right)
                newTree = newTree->right;
            Tree *tempTree = newTree->right;
            newTree->right = tempTree->left;
            newTree = tempTree;
            newTree->left = (*tree)->left;
        }
        newTree->right = (*tree)->right;
    }
    delete *tree;
    *tree = newTree;
}

void delElement(Tree **tree, int id)
{
    if (*tree)
    {
        if (id < (*tree)->id)
            delElement(&(*tree)->left, id);
        else if(id > (*tree)->id)
            delElement(&(*tree)->right, id);
        else
            deleteTree(tree);
    }
}

void calcLevelSum(Tree *tree, List **levels)
{
    if (tree)
    {
        if (!(*levels))
        {
            *levels = new List;
            (*levels)->value = 0;
            (*levels)->next = NULL;
        }
        (*levels)->value += tree->value;
        calcLevelSum(tree->left, &(*levels)->next);
        calcLevelSum(tree->right, &(*levels)->next);
    }
}

int getMaxElement(List *levels)
{
    int result = -1024 * 1024;
    while (levels)
    {
        if (levels->value > result)
            result = levels->value;
        levels = levels->next;
    }
    return result;
}

int putMaxLevelElement(Tree *tree, List *levels, int maxLevelSum)
{
    if (tree)
    {
        if (levels->value == maxLevelSum)
            cout << tree->id << ' ';

        putMaxLevelElement(tree->left, levels->next, maxLevelSum);
        putMaxLevelElement(tree->right, levels->next, maxLevelSum);
    }
}

void clearList(List **numbers)
{
    List *temp = NULL;
    while (*numbers)
    {
        temp = *numbers;
        *numbers = (*numbers)->next;
        delete temp;
    }
}

void printMaxLevelElement(Tree *tree)
{
    List *levels = NULL;
    int maxLevelSum = 0;

    calcLevelSum(tree, &levels);
    maxLevelSum = getMaxElement(levels);
    putMaxLevelElement(tree, levels, maxLevelSum);
    cout << endl;

    clearList(&levels);
}

int main()
{
    Tree *tree = NULL;
    char cmd = 'n';

    srand(time(0));
    while (cmd != 'q')
    {
        cin >> cmd;
        if (cmd == 'c')
            printMaxLevelElement(tree);
        else if (cmd == 's')
            showTree(tree, 0);
        else if (cmd == '+' || cmd == '-' || cmd == '*')
        {
            int id = 0;
            cin >> id;
            if (cmd == '*')
            {
                int value = 0;
                cin >> value;
                addTree(&tree, id, value);
            }
            else
                while(id != 0)
                {
                    if (cmd == '+')
                        addTree(&tree, id, rand() % 3 - 1);
                    else
                        delElement(&tree, id);
                    cin >> id;
                }
        }
    }
    return 0;
}
