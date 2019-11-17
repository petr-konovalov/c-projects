#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000

struct Element
{
    int key;
    char value[50];
    int left, right;
    int height;
} tree[MAXSIZE];

void insert(struct Element *tree, const int next, int *sizetree, struct Element *item)
{
    if (tree[next].key == -1)
    {
        tree[next] = *item;
        (*sizetree)++;
    }
    else
    {
        if (tree[next].key > item->key)
        {
            if (tree[next].left == -1)
            {
                tree[next].left = *sizetree;
                tree[next].height = 1;
                tree[(*sizetree)++] = *item;
            }
            else
            {
                insert (tree, tree[next].left, sizetree, item);
                if (tree[next].left > tree[next].right) tree[next].height = tree[next].left + 1;
            }
        }
        else
        {
            if (tree[next].right == -1)
            {
                tree[next].right = *sizetree;
                tree[next].height = 1;
                tree[(*sizetree)++] = *item;
            }
            else
            {
                insert (tree, tree[next].right, sizetree, item);
                if (tree[next].right > tree[next].left) tree[next].height = tree[next].right + 1;
            }
        }
    }
}

int main()
{
    struct Element temp;
    int sizetree = 0;
    int i = 0;
    for (i = 0; i < MAXSIZE; ++i)
        tree[i].left = tree[i].right = tree[i].key = -1;
    temp.left = temp.right = -1;
    temp.height = 0;
    scanf("%i %s", &temp.key, &temp.value);

    while (temp.key > 0)
    {
        insert(tree, 0, &sizetree, &temp);
        scanf("%i %s", &temp.key, &temp.value);
    }

    for (i = 0; i < sizetree; ++i)
    {
        printf("%i %10s %5i %5i %5i\n", tree[i].key, tree[i].value, tree[i].left, tree[i].right, tree[i].height);
    }
    return 0;
}
