#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

vector<int> edge[100];
bool used[100];

void dfs(int v)
{
    used[v] = true;
    for (int i = 0; i < edge[v].size(); ++i)
        if (!used[edge[v][i]])
        {
            dfs(edge[v][i]);
            printf("%i %i\n", v + 1, edge[v][i] + 1);
        }
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
        edge[l].push_back(r);
        edge[r].push_back(l);
    }
    dfs(0);
    return 0;
}
