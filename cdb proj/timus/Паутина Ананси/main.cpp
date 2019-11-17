#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int parent[100000];
int rankSet[100000];
int ccomp = 0;

int findSet(int v)
{
    return parent[v] == v ? v : parent[v] = findSet(parent[v]);
}

void makeSet(int v)
{
    parent[v] = v;
    rankSet[v] = 0;
    ++ccomp;
}

void unionSet(int a, int b)
{
    a = findSet(a);
    b = findSet(b);
    if (a != b)
    {
        --ccomp;
        if (rankSet[a] < rankSet[b])
            swap(a, b);
        parent[b] = a;
        if (rankSet[a] == rankSet[b])
            ++rankSet[a];
    }
}

bool breaks[100000];
int breakOrd[100000];
int l[100000];
int r[100000];

void printAns(int i)
{
    int c = ccomp;
    if (i >= 0)
    {
        unionSet(l[breakOrd[i]], r[breakOrd[i]]);
        printAns(i - 1);
        printf("%i ", c);
    }
}

int main()
{
    int n, m;
    scanf("%i %i", &n, &m);
    for (int i = 0; i < n; ++i)
        makeSet(i);
    for (int i = 0; i < m; ++i)
    {
        scanf("%i %i", l + i, r + i);
        --l[i];
        --r[i];
    }
    int q;
    scanf("%i", &q);
    for (int i = 0; i < q; ++i)
    {
        scanf("%i", breakOrd + i);
        --breakOrd[i];
        breaks[breakOrd[i]] = true;
    }
    for (int i = 0; i < m; ++i)
        if (!breaks[i])
            unionSet(l[i], r[i]);
    printAns(q - 1);
    return 0;
}
