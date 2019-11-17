#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define ins insert
#define ers erase

const int N = 53;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

typedef long long ll;
typedef double db;
typedef float fl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

int n, m;

int read()
{
    int val;
    cin >> val;
    return val;
}

bool used[N * N];
int fup[N * N];
int tin[N * N];
vector<int> g[N * N];
int timer;
char field[N][N];

void ret()
{
    cout << "1";
    exit(0);
}

void dfs(int v, int parent = -1)
{
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;
    for (int to: g[v])
    {
        if (!used[to])
        {
            dfs(to, v);
            fup[v] = min(fup[v], fup[to]);
            if (tin[v] <= fup[to] && parent != -1)
                ret();
            ++children;
        }
        else
        {
            if (to != parent)
                fup[v] = min(fup[v], tin[to]);
        }
    }
    if (parent == -1 && children > 1)
        ret();
}

int getNum(int i, int j)
{
    return i * N + j;
}

int sx, sy;
int cnt = 0;

void addOkr(int x, int y)
{
    if (field[x][y] != '#')
        return;
    sx = x;
    sy = y;
    ++cnt;
    int num = getNum(x, y);
    for (int k = 0; k < 4; ++k)
    {
        int tx = x + dx[k];
        int ty = y + dy[k];
        if (tx >= 0 && tx < n && ty >= 0 && ty < m && field[tx][ty] == '#')
            g[num].pb(getNum(tx, ty));
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        cin >> field[i];

    for (int x = 0; x < n; ++x)
        for (int y = 0; y < m; ++y)
            addOkr(x, y);
    dfs(getNum(sx, sy));
    if (cnt > 2)
        cout << "2";
    else
        cout << "-1";
    return 0;
}
