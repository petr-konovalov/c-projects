#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
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

const int N = 13, INF = 100500;

vector<int> g[N * N];
int n, m, t;
int num;
int field[N][N];
int match[N * N];
int used[N * N];
bool isPermit[N][N];
int timer;
int usedMask;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

bool dfs(int v)
{
    if (used[v] == timer)
        return false;
    used[v] = timer;
    for (int to: g[v])
    {
        if (match[to] == -1 || dfs(match[to]))
        {
            match[to] = v;
            return true;
        }
    }

    return false;
}

bool getBit(int pos, int mask)
{
    if (pos >= 10)
        return false;
    return (mask >> pos) & 1;
}

int getBitCnt(int mask)
{
    int ans = 0;
    for(; mask > 0; mask >>= 1)
        ans += mask & 1;
    return ans;
}

void printMask(int mask)
{
    forn (bit, 10)
        if (getBit(bit, mask))
            debug("%i ", bit);
}

int buildGraph(int mask)
{
    for (int x = 1; x <= n; ++x)
    {
        isPermit[x][0] = isPermit[x][m + 1] = false;
        for (int y = 1; y <= m; ++y)
        {
            isPermit[0][y] = isPermit[n + 1][y] = false;
            isPermit[x][y] = true;
        }
    }

    for (int x = 1; x <= n; ++x)
    {
        for (int y = 1; y <= m; ++y)
        {
            if (field[x][y] < 10)
                isPermit[x][y] = false;
            if (getBit(field[x][y], mask))
            {
                forn (k, 4)
                {
                    if (getBit(field[x + dx[k]][y + dy[k]], mask) && field[x][y] != field[x + dx[k]][y + dy[k]])
                        return -1;
                    isPermit[x + dx[k]][y + dy[k]] = false;
                }
            }
        }
    }

    int res = 0;
    for (int x = 1; x <= n; ++x)
    {
        for (int y = 1; y <= m; ++y)
        {
            res += isPermit[x][y];
            forn (k, 4)
                if (isPermit[x][y] && isPermit[x + dx[k]][y + dy[k]])
                    g[field[x][y]].pb(field[x + dx[k]][y + dy[k]]);
        }
    }

    return res;
}

int solveMask(int mask)
{
    for (int i = 0; i < N * N; ++i)
    {
        g[i].clear();
        match[i] = -1;
    }
    int sz = buildGraph(mask);
    int cnt = 0;
    if (sz != -1)
    {
        sz += getBitCnt(mask);
        for (int x = 1; x <= n; ++x)
        {
            bool isBlack = x & 1;
            for (int y = 1; y <= m; ++y)
            {
                ++timer;
                if (isBlack && isPermit[x][y] && dfs(field[x][y]))
                    ++cnt;
                isBlack = !isBlack;
            }
        }
        return sz - cnt;
    }
    return -1;
}

void solve()
{
    usedMask = 0;
    cin >> n >> m;

    num = 10;

    for (int i = 1; i <= n; ++i)
    {
        field[i][m + 1] = INF;
        field[i][0] = INF;
        for (int j = 1; j <= m; ++j)
        {
            field[n + 1][j] = INF;
            field[0][j] = INF;
            char c;
            cin >> c;
            if (c == '.')
                field[i][j] = num++;
            else
            {
                field[i][j] = c - '0';
                usedMask |= 1 << (c - '0');
            }
        }
    }
    int ans = 0;
    for (int mask = usedMask; mask > 0; mask = (mask - 1) & usedMask)
    {
        ans = max(ans, solveMask(mask));
    }
    ans = max(ans, solveMask(0));
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
