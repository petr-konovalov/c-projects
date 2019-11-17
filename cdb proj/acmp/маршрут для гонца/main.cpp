#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

vector<int> g[1000];
pair<int, int> edge[2000];
bool used[2000];

void getCycle(int v = 0)
{
    for (int i = 0; i < 4; ++i)
        if (!used[g[v][i]])
        {
            used[g[v][i]] = true;
            int v1 = (edge[g[v][i]].second - 1) / 4;
            int v2 = (edge[g[v][i]].first - 1) / 4;
            if (v1 == v)
            {
                getCycle(v2);
                printf("%i %i ", edge[g[v][i]].first, edge[g[v][i]].second);
            }
            else
            {
                getCycle(v1);
                printf("%i %i ", edge[g[v][i]].second, edge[g[v][i]].first);
            }
        }
}

bool usedV[1000];

void dfs(int v = 0)
{
    usedV[v] = true;
    for (int i = 0; i < 4; ++i)
    {
        int v1 = (edge[g[v][i]].second - 1) / 4;
        int v2 = (edge[g[v][i]].first - 1) / 4;
        int next = v1;
        if (next == v)
            next = v2;
        if (!usedV[next])
            dfs(next);
    }
}

int main()
{
    int n;
    scanf("%i", &n);
    for (int i = 0, ei = 2 * n; i < ei; ++i)
    {
        scanf("%i %i", &edge[i].first, &edge[i].second);
        g[(edge[i].first - 1) / 4].push_back(i);
        g[(edge[i].second - 1) / 4].push_back(i);
    }
    dfs();
    for (int i = 0; i < n; ++i)
        if (!usedV[i])
        {
            printf("No\n");
            return 0;
        }
    printf("Yes\n");
    getCycle();
    return 0;
}
