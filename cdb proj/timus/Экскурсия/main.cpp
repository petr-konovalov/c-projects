#include <iostream>
#include <vector>
#include <set>
#include <stdio.h>

using namespace std;

const int INF = 1000000000;

int n, m;
vector<int> g[100];
int len[100][100];

struct Road
{
    int s, e;
    Road(){};
    Road(int s, int e): s(s), e(e){};
};

vector<Road> roads;
vector<int> optWay;
int optSum = INF;
int p[100];

void improveWay(int a, int b)
{
    if (a != b)
        improveWay(a, p[b]);
    optWay.push_back(b);
}

void getWay(int a)
{
    int d[100];
    bool used[100][100];
    for (int i = 0; i < n; ++i)
        d[i] = INF;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            used[i][j] = false;
    d[a] = 0;
    set<pair<int, int> > q;
    q.insert(make_pair(d[a], a));
    while (!q.empty())
    {
        int v = q.begin()->second;
        q.erase(make_pair(d[v], v));
        for (int i = 0; i < g[v].size(); ++i)
        {
            int to = g[v][i];
            int l = len[v][g[v][i]];
            if (d[v] + l < d[to])
            {
                q.erase(make_pair(d[to], to));
                used[p[to]][to] = used[to][p[to]] = false;
                d[to] = d[v] + l;
                p[to] = v;
                used[v][to] = used[to][v] = true;
                q.insert(make_pair(d[to], to));
            }
        }
    }
    for (int i = 0; i < roads.size(); ++i)
        if (!used[roads[i].s][roads[i].e] && d[roads[i].s] + d[roads[i].e] + len[roads[i].s][roads[i].e] < optSum)
        {
            optWay.clear();
            optSum = d[roads[i].s] + d[roads[i].e] + len[roads[i].s][roads[i].e];
            improveWay(a, roads[i].s);
            int b = roads[i].e;
            while (b != a)
            {
                optWay.push_back(b);
                b = p[b];
            }
        }
}

int main()
{
    char str[100];
    fgets(str, 100, stdin);
    while (str[0] != '-')
    {
        sscanf(str, "%i %i", &n, &m);
        for (int i = 0; i < n; ++i)
            g[i].clear();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                len[i][j] = INF;
        optSum = INF;
        roads.clear();
        for (int i = 0; i < m; ++i)
        {
            int a, b, l;
            scanf("%i %i %i", &a, &b, &l);
            --a;
            --b;
            if (len[a][b] == INF)
            {
                g[a].push_back(b);
                g[b].push_back(a);
                roads.push_back(Road(a, b));
            }
            if (len[a][b] > l)
                len[a][b] = len[b][a] = l;
        }

        for (int i = 0; i < n; ++i)
            getWay(i);

        if (optSum != INF)
        {
            for (int i = 0; i < optWay.size(); ++i)
                printf("%i ", optWay[i] + 1);
            printf("\n");
        }
        else
            printf("No solution.\n");
        scanf(" ");
        fgets(str, 100, stdin);
    }
    return 0;
}
