#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back

const int N = 2e4 + 10;

struct Edge
{
    int a, b;
    bool isAdd;
    Edge(int a, int b, bool isAdd): a(a), b(b), isAdd(isAdd){};
    int getEnd(int start)
    {
        if (a == start)
            return b;
        else
            return a;
    }
};

int m, n;

bool used[2 * N];
int pos[N];
vector<Edge> edges;
vector<int> g[N];

void dfs(int v)
{
    while (pos[v] < g[v].size())
    {
        int eid = g[v][pos[v]++];
        if (!used[eid])
        {
            used[eid] = true;
            dfs(edges[eid].getEnd(v));
            cout << edges[eid].getEnd(v) << ' ';
            if (edges[eid].isAdd)
                cout << '\n';
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    forn (i, m)
    {
        int a, b;
        cin >> a >> b;
        g[a].pb(edges.size());
        g[b].pb(edges.size());
        edges.pb(Edge(a, b, false));
    }

    int prev = -1;
    int sNode = -1;
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (g[i].size() & 1)
        {
            if (sNode == -1)
                sNode = i;
            if (prev == -1)
                prev = i;
            else
            {
                ++cnt;
                g[prev].pb(edges.size());
                g[i].pb(edges.size());
                edges.pb(Edge(prev, i, true));
                prev = -1;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        reverse(g[i].begin(), g[i].end());
    if (sNode != -1)
    {
        cout << cnt << '\n';
        dfs(sNode);
    }
    else
    {
        cout << 1 << '\n';
        dfs(1);
        cout << "1";
    }
    return 0;
}
