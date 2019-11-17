#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e5 + 7;

int n, k;

struct Edge
{
    int to;
    int len;
    Edge(int to, int len): to(to), len(len){};
};

vector<Edge> g[N];
int mWay[N];
bool used[N];

int calcWay1(int v = 1, int parent = -1)
{
    mWay[v] = 0;
    for (Edge e: g[v])
    {
        if (e.to != parent)
            mWay[v] = max(mWay[v], calcWay1(e.to, v) + e.len);
    }
    return mWay[v];
}

void calcWay2(int v = 1, int parent = -1, int mm = 0)
{
    int m1 = 0;
    int m2 = mm;
    for (Edge e: g[v])
    {
        if (e.to == parent)
            continue;
        int way = mWay[e.to] + e.len;
        if (way > m2)
        {
            m1 = m2;
            m2 = way;
        }
        else if (way > m1)
            m1 = way;
    }

    for (Edge e: g[v])
    {
        if (e.to != parent)
        {
            int m = (mWay[e.to] + e.len == m2 ? m1: m2) + e.len;
            mWay[e.to] = max(m, mWay[e.to]);
            calcWay2(e.to, v, m);
        }
    }
}

int getNextNode(int v)
{
    int res = -1;
    int m = 0;
    for (int i = 0; i < g[v].size(); ++i)
    {
        Edge e = g[v][i];
        int way = mWay[e.to] + e.len;
        if (!used[e.to] && way > m)
        {
            m = way;
            res = i;
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k;
    forn (i, n - 1)
    {
        int u, v, d;
        cin >> u >> v >> d;
        g[u].pb(Edge(v, d));
        g[v].pb(Edge(u, d));
    }
    calcWay1();
    calcWay2();

    int n1 = 1;
    for (int i = 2; i <= n; ++i)
        if (mWay[i] < mWay[n1])
            n1 = i;

    calcWay1(n1);
    used[n1] = true;
    int n2 = getNextNode(n1);

    if (k == 1 || n2 == -1)
    {
        cout << mWay[n1];
        return 0;
    }

    n2 = g[n1][n2].to;
    used[n2] = true;

    int k1 = getNextNode(n1);
    int k2 = getNextNode(n2);
    for (int i = 2; i < k && (k1 != -1 || k2 != -1); ++i)
    {
        if (k1 == -1)
            n2 = g[n2][k2].to;
        else if (k2 == -1)
            n1 = g[n1][k1].to;
        else
        {
            if (mWay[g[n2][k2].to] + g[n2][k2].len > mWay[g[n1][k1].to] + g[n1][k1].len)
                n2 = g[n2][k2].to;
            else
                n1 = g[n1][k1].to;
        }
        used[n1] = true;
        used[n2] = true;
        k1 = getNextNode(n1);
        k2 = getNextNode(n2);
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (used[i])
        {
            for (Edge e: g[i])
                if (!used[e.to])
                    ans = max(ans, mWay[e.to] + e.len);
        }
    }

    cout << ans;

    return 0;
}
