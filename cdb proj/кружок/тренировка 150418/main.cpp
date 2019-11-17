#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define F first
#define S second

const int N = 1e3 + 3, M = 1e6 + 1e5, INF = 1e9 + 7;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<pii, pii> ppii;

int field[N][N];

int p[M];
int rg[M];
int setCnt = 0;

vector<ppii> req;
int ans[N];

int n, m, q;

int read()
{
    int v;
    cin >> v;
    return v;
}

int getNum(int x, int y)
{
    return x * N + y;
}

void buildSet(int v)
{
    ++setCnt;
    p[v] = v;
    rg[v] = 1;
}

int getSet(int a)
{
    return a == p[a] ? a: p[a] = getSet(p[a]);
}

void unionSet(int a, int b)
{
    a = getSet(a);
    b = getSet(b);
    if (a == b)
        return;
    --setCnt;
    if (rg[a] < rg[b])
        swap(a, b);
    rg[a] += rg[b];
    p[b] = a;
}

void addOkr(int x, int y)
{
    forn (k, 4)
    {
        int tx = x + dx[k], ty = y + dy[k];
        if (field[tx][ty] == 0)
            unionSet(getNum(tx, ty), getNum(x, y));
    }
}

void remPnt(int x, int y)
{
    --field[x][y];
    if (field[x][y] == 0)
    {
        buildSet(getNum(x, y));
        addOkr(x, y);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m >> q;

    for (int x = 0; x <= n + 1; ++x)
        field[x][0] = field[x][m + 1] = 1;
    for (int y = 0; y <= m + 1; ++y)
        field[0][y] = field[n + 1][y] = 1;

    forn (i, q)
    {
        int x1 = read(), y1 = read(), x2 = read(), y2 = read();
        req.pb(mp(mp(x1, y1), mp(x2, y2)));
        for (int x = x1 + 1; x < x2; ++x)
        {
            ++field[x][y1];
            ++field[x][y2];
        }
        for (int y = y1 + 1; y < y2; ++y)
        {
            ++field[x1][y];
            ++field[x2][y];
        }
        ++field[x1][y1];
        if (y1 != y2)
            ++field[x1][y2];
        if (x1 != x2)
        {
            ++field[x2][y1];
            if (y1 != y2)
                ++field[x2][y2];
        }
    }

    for (int x = 1; x <= n; ++x)
        for (int y = 1; y <= m; ++y)
            if (field[x][y] == 0)
                buildSet(getNum(x, y));

    for (int x = 1; x <= n; ++x)
        for (int y = 1; y <= m; ++y)
            if (field[x][y] == 0)
                addOkr(x, y);

    for (int i = q - 1; i >= 0; --i)
    {
        int x1 = req[i].F.F, y1 = req[i].F.S, x2 = req[i].S.F, y2 = req[i].S.S;
        ans[i] = setCnt;
        for (int x = x1 + 1; x < x2; ++x)
        {
            remPnt(x, y1);
            remPnt(x, y2);
        }
        for (int y = y1 + 1; y < y2; ++y)
        {
            remPnt(x1, y);
            remPnt(x2, y);
        }
        remPnt(x1, y1);
        if (y1 != y2)
            remPnt(x1, y2);
        if (x1 != x2)
        {
            remPnt(x2, y1);
            if (y1 != y2)
                remPnt(x2, y2);
        }
    }

    forn (i, q)
        cout << ans[i] << '\n';

    return 0;
}
