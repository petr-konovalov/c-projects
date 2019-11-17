#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define all(c) c.begin(), c.end()
#define sqr(x) ((x) * (x))
#define sz(c) int((c).size())
#define pb push_back
#define endl '\n'
#define X first
#define Y second

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<db, db> pdd;
typedef ll T;

const int N = 100000 + 7, INF = 1e9 + 7, M = 21;
const int M1 = 1e9 + 7, M2 = 1e9 + 9;
const ll INF64 = 1e18 + 3;

int n, k;
int dp[M][N];
int h[N];
vector<int> g[N];
int p[N];
int sz[N];
vector<int> roots;

int getSet(int v)
{
    return v == p[v] ? v: p[v] = getSet(p[v]);
}

bool check(int a, int b)
{
    return getSet(a) == getSet(b);
}

void unionSet(int a, int b)
{
    a = getSet(a);
    b = getSet(b);
    if (a == b)
        return;
    if (sz[a] < sz[b])
        swap(a, b);
    sz[a] += sz[b];
    p[b] = a;
}

void calc(int v, int parent)
{
    h[v] = h[parent] + 1;
    dp[0][v] = parent;
    for (int i = 1; i < M; ++i)
        dp[i][v] = dp[i - 1][dp[i - 1][v]];

    for (int to: g[v])
        calc(to, v);
}

int getLca(int a, int b)
{
    if (h[a] < h[b])
        swap(a, b);
    int d = h[a] - h[b];
    for (int i = 0; d > 0; ++i, d >>= 1)
        if (d & 1)
            a = dp[i][a];
    if (a == b)
        return a;
    for (int i = M - 1; i >= 0; --i)
        if (dp[i][a] != dp[i][b])
        {
            a = dp[i][a];
            b = dp[i][b];
        }
    return dp[0][a];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    forn (i, N)
    {
        p[i] = i;
        sz[i] = 1;
    }

    cin >> n;
    for (int v = 1; v <= n; ++v)
    {
        int par;
        cin >> par;
        if (par)
        {
            g[par].pb(v);
            unionSet(par, v);
        }
        else
            roots.pb(v);
    }

    for (int v: roots)
        calc(v, v);

    cin >> k;
    int ans = 0;
    forn (i, k)
    {
        int type, x, y;
        cin >> type >> x >> y;
        x = (x - 1 + ans) % n + 1;
        y = (y - 1 + ans) % n + 1;
        if (type)
        {
            g[y].pb(x);
            calc(x, y);
            unionSet(x, y);
        }
        else
        {
            if (check(x, y))
                ans = getLca(x, y);
            else
                ans = 0;
            cout << ans << '\n';
        }
    }

    return 0;
}
