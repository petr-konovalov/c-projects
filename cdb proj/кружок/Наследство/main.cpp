#include <bits/stdc++.h>

using namespace std;

#define MAXSIZE 100001

const long long INF = 1e+17;

struct Edge
{
    int to;
    int cost;
    Edge(int to, int cost): to(to), cost(cost){};
};

typedef vector<Edge> Node;
Node t[MAXSIZE * 8 + 100];
int n;
int dn;
int pos[MAXSIZE];
long long d[MAXSIZE * 8 + 100];

void buildDown(int v, int tl, int tr)
{
    if (tl == tr)
        pos[tl] = v;
    else
    {
        int m = (tl + tr) >> 1;
        buildDown(v * 2, tl, m);
        buildDown(v * 2 + 1, m + 1, tr);
        t[v].push_back(Edge(v * 2, 0));
        t[v].push_back(Edge(v * 2 + 1, 0));
    }
}

void buildUp(int v, int tl, int tr)
{
    if (tl == tr)
        t[pos[tl]].push_back(Edge(v / 2 + dn, 0));
    else
    {
        int m = (tl + tr) >> 1;
        t[v + dn].push_back(Edge(v / 2 + dn, 0));
        buildUp(v * 2, tl, m);
        buildUp(v * 2 + 1, m + 1, tr);
    }
}

void firstPlane(int a, int b, int cost)
{
    t[pos[a]].push_back(Edge(pos[b], cost));
}

void secondPlane(int v, int id, int cost, int l, int r, int tl, int tr)
{
    if (tl == l && tr == r)
        t[pos[id]].push_back(Edge(v, cost));
    else
    {
        int m = (tl + tr) >> 1;
        if (r <= m)
            secondPlane(v * 2, id, cost, l, r, tl, m);
        else if (l > m)
            secondPlane(v * 2 + 1, id, cost, l, r, m + 1, tr);
        else
        {
            secondPlane(v * 2, id, cost, l, m, tl, m);
            secondPlane(v * 2 + 1, id, cost, m + 1, r, m + 1, tr);
        }
    }
}

void thirdPlane(int v, int id, int cost, int l, int r, int tl, int tr)
{
    if (tl == l && tr == r)
    {
        if (tl == tr)
            t[pos[tl]].push_back(Edge(pos[id], cost));
        else
            t[v + dn].push_back(Edge(pos[id], cost));
    }
    else
    {
        int m = (tl + tr) >> 1;
        if (r <= m)
            thirdPlane(v * 2, id, cost, l, r, tl, m);
        else if (l > m)
            thirdPlane(v * 2 + 1, id, cost, l, r, m + 1, tr);
        else
        {
            thirdPlane(v * 2, id, cost, l, m, tl, m);
            thirdPlane(v * 2 + 1, id, cost, m + 1, r, m + 1, tr);
        }
    }
}

struct cmp
{
    bool operator() (const int &a, const int &b)
    {
        return d[a] < d[b] || d[a] == d[b] && a < b;
    }
};

void findPath(int s)
{
    set<int, cmp> q;
    for (int i = 0; i < MAXSIZE; ++i)
        d[i] = INF;
    d[pos[s]] = 0;
    q.insert(pos[s]);
    while (!q.empty())
    {
        int to = *q.begin();
        long long way = d[to];
        q.erase(to);
        for (int i = 0; i < t[to].size(); ++i)
            if (way + t[to][i].cost < d[t[to][i].to])
            {
                q.erase(t[to][i].to);
                d[t[to][i].to] = way + t[to][i].cost;
                q.insert(t[to][i].to);
            }
    }
    q.clear();
}

int main()
{
    int q, s;
    scanf("%i %i %i", &n, &q, &s);
    dn = n * 4 + 10;
    buildDown(1, 1, n);
    buildUp(1, 1, n);
    for (int i = 0; i < q; ++i)
    {
        int t, a, b, l, r, cost;
        scanf("%i", &t);
        switch (t)
        {
            case 1:
                scanf("%i %i %i", &a, &b, &cost);
                firstPlane(a, b, cost);
                break;
            case 2:
                scanf("%i %i %i %i", &a, &l, &r, &cost);
                secondPlane(1, a, cost, l, r, 1, n);
                break;
            case 3:
                scanf("%i %i %i %i", &a, &l, &r, &cost);
                thirdPlane(1, a, cost, l, r, 1, n);
                break;
            default:
                break;
        }
    }
    findPath(s);
    for (int i = 1; i <= n; ++i)
        if (d[pos[i]] != INF)
            printf("%I64d ", d[pos[i]]);
        else
            printf("-1 ");
    return 0;
}
