#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0, e = n; i < n; ++i)
#define pb push_back
#define mp make_pair
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define F first
#define S second

using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<db, db> pdd;
typedef pair<ll, ll> pll;

const int N = 100100;
const int INF = 1e9;

bool br[N];
bool used[N];
int fup[N];
int tin[N];
int timer;
vector<pii> g[N];
vector<int> gcmp[N];
int col[N];

void dfs(int v, int p = -1)
{
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (pii to: g[v])
        if (to.S != p)
        {
            if (used[to.S])
                fup[v] = min(fup[v], tin[to.S]);
            else
            {
                dfs(to.S, v);
                fup[v] = min(fup[v], fup[to.S]);
                if (tin[v] < fup[to.S])
                    br[to.F] = true;
            }
        }
}

void clrComp(int v)
{
    used[v] = true;
    col[v] = timer;
    for (pii to: g[v])
        if (!br[to.F] && !used[to.S])
            clrComp(to.S);
}

void init()
{
    for (int i = 0; i < N; ++i)
    {
        used[i] = false;
        col[i] = 0;
        br[i] = false;
        g[i].clear();
    }
    timer = 0;
}

int deep[N];
int res;
int pnt;

void getMax(int v, int p = -1)
{
    if (deep[v] > res)
    {
        res = deep[v];
        pnt = v;
    }
    for (int to: gcmp[v])
        if (to != p)
        {
            deep[to] = deep[v] + 1;
            getMax(to, v);
        }
}

int getMaxRoad()
{
    for (int i = 0; i < N; ++i)
        deep[i] = 0;
    res = 0;
    pnt = 0;

    getMax(0);

    for (int i = 0; i < N; ++i)
        deep[i] = 0;
    res = 0;

    getMax(pnt);
    return res;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    init();
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        if (a == b)
            continue;
        g[a].pb(mp(i, b));
        g[b].pb(mp(i, a));
    }
    dfs(1);
    for (int i = 1; i <= n; ++i)
        used[i] = false;
    timer = 0;
    for (int i = 1; i <= n; ++i)
        if (!used[i])
        {
            clrComp(i);
            ++timer;
        }
    for (int i = 1; i <= n; ++i)
        for (pii edge: g[i])
            if (br[edge.F])
            {
                gcmp[col[i]].pb(col[edge.S]);
                gcmp[col[edge.S]].pb(col[i]);
            }
    cout << timer - 1 - getMaxRoad() << '\n';
    for (int i = 0; i < timer; ++i)
        gcmp[i].clear();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(false);
    cout.tie(false);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
