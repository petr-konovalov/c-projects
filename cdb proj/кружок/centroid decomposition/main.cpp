#include <bits/stdc++.h >

using namespace std;

#define forn(i, n) for (int i = 0, e = n; i < e; ++i)
#define fsf(i, s, f) for (int i = s, e = f; i <= e; ++i)
#define pb push_back
#define mp make_pair
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define F first
#define S second

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 5e4 + 10;
const int K = 17;
const int INF = 1e9;

struct Edge
{
    int c;
    int v;
    Edge(int v, int c): v(v), c(c){};
};

int lv[N];
int p[N];
vector<Edge> g[N];
vector<int> path[N];
int f[K][N];

void calc(int v, int depth, int parent = -1, int minim = INF)
{
    f[depth][v] = minim;
    for (Edge to: g[v])
        if (lv[to.v] == -1 && to.v != parent)
            calc(to.v, depth, v, min(minim, to.c));
}

int dfs(int v, int size, int &center, int parent = -1)
{
    int sum = 1;
    for (Edge to: g[v])
        if (lv[to.v] == -1 && to.v != parent)
            sum += dfs(to.v, size, center, v);
    if (center == -1 && (2 * sum >= size || parent == -1))
        center = v;
    return sum;
}

void build(int v, int depth, int size, int last = -1)
{
    int center = -1;
    dfs(v, size, center);
    calc(center, depth);
    lv[center] = depth;
    p[center] = last;
    if (last != -1)
        path[center] = vector<int>(path[last].begin(), path[last].end());
    path[center].pb(center);
    for (Edge to: g[center])
        if (lv[to.v] == -1)
            build(to.v, depth + 1, size >> 1, center);
}

int getCenter(int a, int b)
{
    if (path[a].size() > path[b].size())
        swap(a, b);
    int l = 0, r = path[a].size();
    while (r - l > 1)
    {
        int m = (r + l) >> 1;
        if (path[a][m] == path[b][m])
            l = m;
        else
            r = m;
    }
    return p[path[b][r]];
}

int getMin(int a, int b)
{
    int c = getCenter(a, b);
    return min(f[lv[c]][a], f[lv[c]][b]);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    lv[1] = -1;
    fsf(i, 2, n)
    {
        lv[i] = -1;
        int x, y;
        cin >> x >> y;
        g[i].pb(Edge(x, y));
        g[x].pb(Edge(i, y));
    }
    build(1, 0, n);
    for (int i = 1; i <= n; ++i)
        debug("%i ", p[i]);
    debug("\n");
    int m;
    cin >> m;
    forn (i, m)
    {
        int a, b;
        cin >> a >> b;
        cout << getMin(a, b) << '\n';
    }
    return 0;
}
