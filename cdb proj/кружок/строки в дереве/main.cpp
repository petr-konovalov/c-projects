#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define fsf(i, s, f) for(int i = s, e = f; i <= e; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define ins insert
#define ers erase
#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef unsigned int ui;
typedef unsigned long long ull;
typedef long long ll;
typedef double db;
typedef float fl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int P = 1e9 + 7;
const int M = 3e6 + 17;
const int N = 3e5 + 10;

struct Edge
{
    int to;
    char v;
    Edge(int to, char v): to(to), v(v){};
};

typedef pii Hash;

Hash operator- (const Hash &a, const Hash &b)
{
    int f = a.F + P - b.F, s = a.S + P - b.S;
    return Hash(f >= P ? f - P: f, s >= P ? s - P: s);
}

int getId(Hash h)
{
    return ((ll)h.F * P ^ h.S) % M;
}

map<Hash, int> tb[2][M];

void push(Hash h, int v, int num)
{
    tb[num][getId(h)][h] = v;
}

map<Hash, int>::iterator get(Hash h, int num)
{
    return tb[num][getId(h)].find(h);
}

Hash hsh;
int len;
int qf, qs;
int qfl, qsl;
int rqf, rqs;

vector<Edge> g[N];
bool lv[N];

int dfs(int v, int size, int &center, int parent = -1)
{
    int sum = 1;
    for (Edge e: g[v])
        if (e.to != parent && !lv[e.to])
            sum += dfs(e.to, size, center, v);
    if (center == -1 && (parent == -1 || 2 * sum >= size))
        center = v;
    return sum;
}

int tim;
int used[N];
pair<pair<Hash, Hash>, int> buf[N];
int ind = 0;

void pushBuf(const pair<pair<Hash, Hash>, int> &ph)
{
    buf[ind++] = ph;
}

void calc(int v, int center, Hash cur, Hash bcur, int parent, int depth = 1)
{
    if (cur == hsh || bcur == hsh)
    {
        cout << "YES\n" << v << ' ' << center;
        exit(0);
    }
    Hash dec = hsh - cur;
    auto it = get(dec, 1);
    if (it != tb[1][getId(dec)].end() && used[it->second] == tim)
    {
        cout << "YES\n" << v << ' ' << it->second;
        exit(0);
    }
    dec = hsh - bcur;
    it = get(dec, 0);
    if (it != tb[0][getId(dec)].end() && used[it->second] == tim)
    {
        cout << "YES\n" << v << ' ' << it->second;
        exit(0);
    }
    pushBuf(mp(mp(cur, bcur), v));
    for (Edge e: g[v])
        if (e.to != parent && !lv[e.to])
            calc(e.to, center,
                 Hash(((ll)cur.F * rqf + (ll)qfl * e.v) % P,
                      ((ll)cur.S * rqs + (ll)qsl * e.v) % P),
                 Hash((e.v + (ll)qf * bcur.F) % P,
                      (e.v + (ll)qs * bcur.S) % P),
                 v,
                 depth + 1);
}

void build(int v, int size, int last = -1)
{
    int center = -1;
    dfs(v, size, center);
    lv[center] = true;
    ++tim;
    for (Edge e: g[center])
        if (!lv[e.to])
        {
            calc(e.to, center,
                 Hash(((ll)e.v * qfl) % P, ((ll)e.v * qsl) % P),
                 Hash(e.v, e.v),
                 center);
            for (int i = 0; i < ind; ++i)
            {
                push(buf[i].F.F, buf[i].S, 0);
                push(buf[i].F.S, buf[i].S, 1);
                used[buf[i].S] = tim;
            }
            ind = 0;
        }
    for (Edge e: g[center])
        if (!lv[e.to])
            build(e.to, size >> 1, center);
}

int binPow(int a, int deg)
{
    int res = 1;
    while (deg)
    {
        if (deg & 1)
            res = ((ll)res * a) % P;
        a = ((ll)a * a) % P;
        deg >>= 1;
    }
    return res;
}

void init()
{
    const int qM = 1e4;
    srand(time(0));
    qf = 256 + rand() % qM;
    qs = 256 + rand() % qM;
    rqf = binPow(qf, P - 2);
    rqs = binPow(qs, P - 2);
}

char str[N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    init();
    cin >> str;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        hsh.F = (((ll)hsh.F * qf) % P + str[i]) % P;
        hsh.S = (((ll)hsh.S * qs) % P + str[i]) % P;
        ++len;
    }
    qfl = binPow(qf, len - 1);
    qsl = binPow(qs, len - 1);
    int n;
    cin >> n;
    fsf (i, 2, n)
    {
        int a, b;
        char c;
        cin >> a >> b >> c;
        g[a].pb(Edge(b, c));
        g[b].pb(Edge(a, c));
    }
    build(1, n);
    cout << "NO";
    return 0;
}
