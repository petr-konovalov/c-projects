#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define forn(i, n) for(int i = 0; i < (n); ++i)

typedef pair<int, int> pii;
typedef long long ll;
const int N = 256;

int used[N];
int usedr[N];
int timer;
bool take[N];
int match[N];
vector<int> g[N];
bool t[N][N];
int ans = 0;

bool dfs(const int v)
{
    if (used[v] == timer) return false;
    ++ans;
    used[v] = timer;
    for (int to: g[v])
        if (match[to] == -1)
        {
            match[to] = v;
            return take[v] = true;
        }
    for (int to: g[v])
    {
        usedr[to] = timer;
        if (dfs(match[to]))
        {
            match[to] = v;
            return take[v] = true;
        }
    }
    return false;
}

void solve()
{
    timer = 0;
    forn (i, N)
    {
        take[i] = false;
        used[i] = 0;
        usedr[i] = 0;
        match[i] = -1;
        forn (j, N)
            t[i][j] = true;
        g[i].clear();
    }
    int n, m;
    cin >> m >> n;
    forn (i, m)
    {
        int to;
        cin >> to;
        while (to)
        {
            t[i][to - 1] = false;
            cin >> to;
        }
    }
    forn (i, m)
        forn (j, n)
            if (t[i][j])
                g[i].pb(j);
    int cnt = 0;
    for (int run = 1; run;)
    {
        run = 0;
        ++timer;
        ans = 0;
        forn (i, m)
            if (!take[i] && dfs(i))
                ++cnt, run = 1;
    }
    cout << m + n - cnt << '\n';
    cout << ans << ' ' << m + n - cnt - ans << '\n';
    forn (i, m)
        if (used[i] == timer)
            cout << i + 1 << ' ';
    cout << '\n';
    forn (i, n)
        if (usedr[i] != timer)
            cout << i + 1 << ' ';
    cout << "\n\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(false);
    cout.tie(false);

    int k;
    cin >> k;
    while (k--)
        solve();
    return 0;
}
