#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n ; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define F first
#define S second

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 157;

int n, m, k;

bool gm[N][N];
vector<int> g[N];
int match[N];
int used[N];
bool label[N];
int timer;

bool dfs(int v)
{
    if (used[v] == timer)
        return false;
    used[v] = timer;
    for (int to: g[v])
        if (match[to] == -1 || dfs(match[to]))
        {
            match[to] = v;
            return true;
        }
    return false;
}

void getRes(int v)
{
    if (used[v] == timer)
        return;
    used[v] = timer;
    for (int to: g[v])
    {
        dfs(match[to]);
        label[to] = true;
    }
}

void solve()
{
    cin >> m >> n;

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            gm[i][j] = true;
    for (int i = 1; i <= m; ++i)
        used[i] = 0;
    for (int i = 1; i <= n; ++i)
    {
        match[i] = -1;
        label[i] = false;
    }
    timer = 0;

    for (int i = 1; i <= m; ++i)
    {
        int v;
        cin >> v;
        while (v != 0)
        {
            gm[i][v] = false;
            cin >> v;
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        g[i].clear();
        for (int j = 1; j <= n; ++j)
            if (gm[i][j])
                g[i].pb(j);
    }
    for (int i = 1; i <= m; ++i)
    {
        ++timer;
        dfs(i);
    }

    bool start[N];
    for (int i = 1; i <= m; ++i)
        start[i] = true;
    for (int i = 1; i <= n; ++i)
        if (match[i] != -1)
            start[match[i]] = false;
    ++timer;
    for (int i = 1; i <= m; ++i)
        if (start[i])
            getRes(i);

    int cnt1 = 0;
    int cnt2 = 0;
    for (int i = 1; i <= m; ++i)
        cnt1 += used[i] == timer;
    for (int i = 1; i <= n; ++i)
        cnt2 += !label[i];

    cout << cnt1 + cnt2 << '\n' << cnt1 << ' ' << cnt2 << '\n';
    for (int i = 1; i <= m; ++i)
        if (used[i] == timer)
            cout << i << ' ';
    cout << '\n';
    for (int i = 1; i <= n; ++i)
        if (!label[i])
            cout << i << ' ';
    cout << "\n\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> k;
    while (k--)
        solve();

    return 0;
}
