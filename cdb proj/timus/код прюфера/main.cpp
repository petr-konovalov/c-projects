#include <iostream>
#include <stdio.h>
#include <set>
#include <vector>

using namespace std;

int code[7500];
int size = 0;
int n;
set<int> g[7500];

void makeTree()
{
    int ptr = 0;
    vector <int> deg(n, 1);
    for (int i = 0; i < size; ++i)
        ++deg[code[i]];
    while (deg[ptr] != 1)
        ++ptr;
    int leaf = ptr;
    for (int i = 0; i < size; ++i)
    {
        int v = code[i];
        --deg[leaf];
        --deg[v];
        g[leaf].insert(v);
        g[v].insert(leaf);
        if (deg[v] == 1 && v < ptr)
            leaf = v;
        else
        {
            ++ptr;
            while (ptr < n && deg[ptr] != 1)
                ++ptr;
            leaf = ptr;
        }
    }
    for (int i = 0; i < n - 1; ++i)
        if (deg[i] == 1)
        {
            g[i].insert(n - 1);
            g[n - 1].insert(i);
        }
}

int main()
{
    int nextn;
    while (!feof(stdin) && scanf("%i", &nextn))
        code[size++] = nextn - 1;
    n = size;
    size -= 2;
    makeTree();
    for (int i = 0; i < n; ++i)
    {
        printf("%i: ", i + 1);
        for (set<int>::iterator it = g[i].begin(); it != g[i].end(); ++it)
            printf("%i ", *it + 1);
        printf("\n");
    }

    return 0;
}
