#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define pb push_back
#define mp make_pair
#define f first
#define s second

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;

const int M = 200010;
const int K = 20;

int tin[M], tout[M];
int lifeLink[M];
int dpth[M];
int dp[K][M];
bool dead[M];
int timer;
vector<int> g[M];

vector<int> z;

void dfs(int v = 1, int parent = 1)
{
    tin[v] = timer++;
    dp[0][v] = parent;
    forn (i, K - 1)
        dp[i + 1][v] = dp[i][dp[i][v]];
    for (int to: g[v])
    {
        dpth[to] = dpth[v] + 1;
        dfs(to, v);
    }
    tout[v] = timer++;
}

bool isAncestor(int a, int b)
{
    return tin[a] < tin[b] && tout[b] < tout[a];
}

int findLife(int a)
{
    return dead[a] ? lifeLink[a] = findLife(lifeLink[a]): a;
}

int getAns(int a, int b)
{
    if (dpth[a] < dpth[b])
        swap(a, b);
    for (int i = K - 1; i >= 0; --i)
        if (!isAncestor(dp[i][a], b))
            a = dp[i][a];
    if (a == b)
        return a;
    a = findLife(dp[0][a]);
    return a;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(false);
    cout.tie(false);

    int m;
    cin >> m;
    int cur = 1;
    lifeLink[1] = 1;
    forn (i, m)
    {
        char c;
        int v;
        cin >> c;
        if (c == '+')
        {
            cin >> v;
            g[v].pb(++cur);
            lifeLink[cur] = cur;
        }
        else if (c == '-')
        {
            cin >> v;
            z.pb(-1);
            z.pb(v);
        }
        else
        {
            int a, b;
            cin >> a >> b;
            z.pb(1);
            z.pb(a);
            z.pb(b);
        }
    }
    dfs();
    cur = 0;
    while (cur < z.size())
    {
        if (z[cur++] == -1)
        {
            dead[z[cur]] = true;
            lifeLink[z[cur]] = dp[0][z[cur]];
        }
        else
        {
            cout << getAns(z[cur], z[cur + 1]) << '\n';
            ++cur;
        }
        ++cur;
    }
    return 0;
}
