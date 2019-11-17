#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define fif(i, p) for(int i = 0; (p); ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define pb push_back
#define mp make_pair
#define f first
#define s second

const int INF = 1000000000;
const int N = 50010;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;

int tin[N], tout[N];
int timer;
int p[N];
int c[N];
int dp[17][N];
int da[17][N];
int depth[N];
vector<int> g[N];

void dfs(int v = 1)
{
    tin[v] = timer++;
    dp[0][v] = p[v];
    da[0][v] = c[v];
    forn (i, 16)
    {
        dp[i + 1][v] = dp[i][dp[i][v]];
        da[i + 1][v] = min(da[i][v], da[i][dp[i][v]]);
    }
    for (int to: g[v])
    {
        depth[to] = depth[v] + 1;
        dfs(to);
    }
    tout[v] = timer++;
}

bool isAncestor(int a, int b)
{
    return tin[a] < tin[b] && tout[b] < tout[a];
}

int getAns(int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);
    int ans = INF;
    for (int i = 0, d = depth[a] - depth[b]; d; d >>= 1, ++i)
        if (d & 1)
        {
            ans = min(ans, da[i][a]);
            a = dp[i][a];
        }
    if (a != b)
    {
        for (int i = 16; i >= 0; --i)
            if (!isAncestor(dp[i][a], b))
            {
                ans = min(ans, min(da[i][a], da[i][b]));
                a = dp[i][a];
                b = dp[i][b];
            }
        ans = min(ans, min(c[a], c[b]));
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(false);
    cout.tie(false);
    p[1] = 1;
    c[1] = INF;
    int n;
    cin >> n;
    for (int i = 2; i <= n; ++i)
    {
        cin >> p[i] >> c[i];
        g[p[i]].pb(i);
    }
    dfs();

    int m;
    cin >> m;
    forn (i, m)
    {
        int a, b;
        cin >> a >> b;
        cout << getAns(a, b) << '\n';
    }
    return 0;
}
