#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;
typedef double db;
typedef float fl;
typedef unsigned ui;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int INF = 1e9;
const int N = 1e5 + 10;
const int K = 18;

struct Req
{
    int t, v, d, c;
    Req(int v): v(v){t = 2; c = 0; };
    Req(int v, int d, int c): v(v), d(d), c(c){t = 1; };
};

set<pii> task[N];
int p[N];
int lv[N];
int rad[N];
vector<pii> g[N];

int dpth[N];
int timer;
int sp[K][2 * N];
int lg[2 * N];
int first[N];
vector<int> ord;

void calc(int v, int center, int depth = 0, int parent = -1)
{
    rad[center] = max(rad[center], depth);
    for (pii to: g[v])
        if (lv[to.F] == -1 && to.F != parent)
            calc(to.F, center, depth + to.S, v);
}

int dfs(int v, int size, int &center, int parent = -1)
{
    int sum = 1;
    for (pii to: g[v])
        if (lv[to.F] == -1 && to.F != parent)
            sum += dfs(to.F, size, center, v);
    if (center == -1 && (2 * sum >= size || parent == -1))
        center = v;
    return sum;
}

void build(int v, int depth, int size, int last = -1)
{
    int center = -1;
    dfs(v, size, center);
    calc(center, center);
    p[center] = last;
    lv[center] = depth;
    for (pii to: g[center])
        if (lv[to.F] == -1)
            build(to.F, depth + 1, size >> 1, center);
}

void dfsDpth(int v, int parent = -1)
{
    first[v] = ord.size();
    ord.pb(v);
    for (pii to: g[v])
        if (to.F != parent)
        {
            dpth[to.F] = dpth[v] + to.S;
            dfsDpth(to.F, v);
            ord.pb(v);
        }
}

int getDist(int a, int b)
{
    int ans = dpth[a] + dpth[b];
    a = first[a];
    b = first[b];
    if (a > b)
        swap(a, b);
    int len = b - a + 1;
    int sz = lg[len];
    int lca = sp[sz][b + 1 - (1 << sz)];
    if (dpth[lca] > dpth[sp[sz][a]])
        lca = sp[sz][a];
    return ans - 2 * dpth[lca];
}

void init()
{
    forn (i, N)
        lv[i] = -1;
    lg[1] = 0;
    for (int i = 2, e = 2 * N; i < e; ++i)
        lg[i] = lg[i >> 1] + 1;
}

vector<Req> z;
void addTask(int i)
{
    int cur = z[i].v;
    while (cur != -1)
    {
        task[cur].insert(mp(getDist(z[i].v, cur), i));
        cur = p[cur];
    }
}

void addColor(int i)
{
    int cur = z[i].v;
    while (cur != -1)
    {
        int dist = getDist(cur, z[i].v);
        while (!task[cur].empty() && task[cur].begin()->first + dist <= z[i].d)
        {
            if (z[task[cur].begin()->second].c == 0)
                z[task[cur].begin()->second].c = z[i].c;
            task[cur].erase(task[cur].begin());
        }
        cur = p[cur];
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;

    init();
    cin >> n;

    for (int i = 1; i < n; ++i)
    {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].pb(mp(b, w));
        g[b].pb(mp(a, w));
    }
    build(1, 0, n);
    dfsDpth(1);
    forn (i, ord.size())
        sp[0][i] = ord[i];
    for (int len = 1; len <= lg[ord.size()]; ++len)
        for (int i = 0; i + (1 << (len - 1)) < ord.size(); ++i)
        {
            sp[len][i] = sp[len - 1][i + (1 << (len - 1))];
            if (dpth[sp[len][i]] > dpth[sp[len - 1][i]])
                sp[len][i] = sp[len - 1][i];
        }
    int q;
    cin >> q;
    forn (i, q)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int v, d, c;
            cin >> v >> d >> c;
            z.pb(Req(v, d, c));
        }
        else
        {
            int v;
            cin >> v;
            z.pb(Req(v));
        }
    }
    for (int i = (int)z.size() - 1; i >= 0; --i)
        if (z[i].t == 2)
            addTask(i);
        else
            addColor(i);
    for (Req req: z)
        if (req.t == 2)
            cout << req.c << '\n';
    return 0;
}
