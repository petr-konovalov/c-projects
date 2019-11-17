#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int len[100][100];
vector<int> edge[100];

const int INF = 1000000000;

int main()
{
    int n, m;
    int res = 0;
    scanf("%i %i", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            len[i][j] = INF;
    for (int i = 0; i < n; ++i)
        len[i][i] = 0;
    for (int i = 0; i < m; ++i)
    {
        int l, r, c;
        scanf("%i %i %i", &l, &r, &c);
        --l;
        --r;
        if (len[l][r] == INF)
        {
            edge[l].push_back(r);
            edge[r].push_back(l);
            len[l][r] = c;
        }
        else
            len[l][r] = min(len[l][r], c);
        len[r][l] = len[l][r];
    }
    int d[100];
    bool used[100] = {false};
    d[0] = 0;
    for (int i = 1; i < n; ++i)
        d[i] = INF;
    for (int i = 0; i < n; ++i)
    {
        int v = -1;
        int mEdge = INF;
        for (int j = 0; j < n; ++j)
            if (!used[j] && d[j] < mEdge)
                v = j, mEdge = d[j];
        used[v] = true;
        res += mEdge;
        for (int j = 0; j < edge[v].size(); ++j)
            if (!used[edge[v][j]] && len[v][edge[v][j]] < d[edge[v][j]])
                d[edge[v][j]] = len[v][edge[v][j]];
    }
    printf("%i", res);
    return 0;
}
