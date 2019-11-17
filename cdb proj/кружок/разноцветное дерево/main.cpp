#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;
typedef float fl;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e5 + 10;
const int K = 18;

vector<int> g[N];
int lv[N];
int p[N];
map<int, int> near[N];
int dist[K][N];
int col[N];
int n;

void calc(int v, int center, int depth = 0, int parent = -1)
{
    auto it = near[center].find(col[v]);
    if (it == near[center].end() || dist[lv[center]][it->S] > depth)
        near[center][col[v]] = v;
    dist[lv[center]][v] = depth;
    for (int to: g[v])
        if (lv[to] == -1 && to != parent)
            calc(to, center, depth + 1, v);
}

int dfs(int v, int size, int &center, int depth = 1, int parent = -1)
{
    int sum = 1;
    for (int to: g[v])
        if (lv[to] == -1 && to != parent)
            sum += dfs(to, size, center, depth + 1, v);
    if (center == -1 && (2 * sum >= size || parent == -1))
        center = v;
    return sum;
}

void build(int v, int size, int depth, int last = -1)
{
    int center = -1;
    dfs(v, size, center);
    p[center] = last;
    lv[center] = depth;
    calc(center, center);

    for (int to: g[center])
        if (lv[to] == -1)
            build(to, size >> 1, depth + 1, center);
}

int getAns(int v, int color)
{
    int cur = v;
    while (cur != -1 && near[cur].find(color) == near[cur].end())
        cur = p[cur];
    if (cur == -1)
        return -1;
    int ans = dist[lv[cur]][v] + dist[lv[cur]][near[cur][color]];
    cur = p[cur];
    while (cur != -1)
    {
        ans = min(ans, dist[lv[cur]][v] + dist[lv[cur]][near[cur][color]]);
        cur = p[cur];
    }
    return ans;
}

void init()
{
    forn (i, N)
        lv[i] = -1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    init();

    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int parent;
        cin >> parent;
        g[parent].pb(i);
        g[i].pb(parent);
    }
    forn (i, n)
        cin >> col[i];
    build(0, n, 0);
    int q;
    cin >> q;
    forn (i, q)
    {
        int v, color;
        cin >> v >> color;
        cout << getAns(v, color) << ' ';
    }
    return 0;
}
