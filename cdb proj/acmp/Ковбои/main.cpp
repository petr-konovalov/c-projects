#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

vector<int> g[1000];
bool used[1000];

void dfs(int v, int &res)
{
    used[v] = true;
    if ((g[v].size() & 1))
        ++res;
    for (int i = 0; i < g[v].size(); ++i)
        if (!used[g[v][i]])
            dfs(g[v][i], res);
}

int main()
{
    int res = 0;
    int n, m;
    scanf("%i %i", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf("%i %i", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i)
        if (!used[i] && g[i].size() != 0)
        {
            int r = 0;
            dfs(i, r);
            res += max(1, r / 2);
        }
    printf("%i", res);
    return 0;
}
