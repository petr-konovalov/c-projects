#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int ancestor[200000];
int parent[200000];
int size[200000];

void makeSet(int v)
{
    parent[v] = v;
    size[v] = 1;
    ancestor[v] = v;
}

int findSet(int v)
{
    return parent[v] == v ? v : parent[v] = findSet(parent[v]);
}

void unionSet(int a, int b, int ancs)
{
    a = findSet(a);
    b = findSet(b);
    if (a != b)
    {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        ancestor[a] = ancs;
    }
}

vector<int> g[200000];
vector<pair<int, int> > req[200000];
int resp[1000000];
bool used[200000];

void getAns(int v)
{
    used[v] = true;
    makeSet(v);
    for (unsigned int i = 0; i < g[v].size(); ++i)
        if (!used[g[v][i]])
        {
            getAns(g[v][i]);
            unionSet(v, g[v][i], v);
        }
    for (unsigned int i = 0; i < req[v].size(); ++i)
        if (used[req[v][i].first])
            resp[req[v][i].second] = ancestor[findSet(req[v][i].first)] + 1;
}

int main()
{
    int n, q;
    scanf("%i", &n);
    for (int i = 1; i < n; ++i)
    {
        int a, b;
        scanf("%i %i", &a, &b);
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    scanf("%i", &q);
    for (int i = 0; i < q; ++i)
    {
        int a, b;
        scanf("%i %i", &a, &b);
        --a;
        --b;
        req[a].push_back(make_pair(b, i));
        req[b].push_back(make_pair(a, i));
    }
    getAns(0);
    for (int i = 0; i < q; ++i)
        printf("%i\n", resp[i]);
    return 0;
}
