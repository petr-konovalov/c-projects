#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

vector<int> g[20000];
vector<int> gr[20000];
vector<int> order;
vector<int> comp;
int used[20000];

void dfs1(int v)
{
    used[v] = 1;
    for (int i = 0; i < g[v].size(); ++i)
        if (used[g[v][i]] != 1)
            dfs1(g[v][i]);
    order.push_back(v);
}

void dfs2(int v)
{
    used[v] = 2;
    comp.push_back(v);
    for (int i = 0; i < gr[v].size(); ++i)
        if (used[gr[v][i]] != 2)
            dfs2(gr[v][i]);
}

int main()
{
    int n, m;
    scanf("%i %i", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        int l, r;
        scanf("%i %i", &l, &r);
        --l;
        --r;
        g[l].push_back(r);
        gr[r].push_back(l);
    }
    for (int i = 0; i < n; ++i)
        if (used[i] != 1)
            dfs1(i);
    int compCount = 0;
    int res[20000];
    for (int i = n - 1; i >= 0; --i)
        if (used[order[i]] != 2)
        {
            comp.clear();
            ++compCount;
            dfs2(order[i]);
            for (int j = 0; j < comp.size(); ++j)
                res[comp[j]] = compCount;
        }
    printf("%i\n", compCount);
    for (int i = 0; i < n; ++i)
        printf("%i ", res[i]);
    printf("\n");
    return 0;
}
