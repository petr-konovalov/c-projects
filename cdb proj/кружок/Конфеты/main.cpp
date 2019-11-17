#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stdout, __VA_ARGS__); fflush(stdout);
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define ins insert
#define ers erase

typedef long long ll;
typedef double db;
typedef float fl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;
typedef pair<pii, pii> qii;

const int W = 1e6 + 5, M = 1e5 + 5, sW = 350;

int tb[M];
int bl[sW];
qii z[M];
int n, m;
int w[M];

void add(int value)
{
    ++bl[value / sW];
    ++tb[value];
}

void rem(int value)
{
    --bl[value / sW];
    --tb[value];
}

int get(int k)
{
    int block = 0;
    int sum = 0;

    while (sum + bl[block] < k)
        sum += bl[block++];

    int res = block * sW - 1;
    while (sum < k)
        sum += tb[++res];

    return res;
}

bool comp(qii a, qii b)
{
    int ab = a.F.F / sW, bb = b.F.F / sW;
    return ab != bb ? ab < bb: (ab & 1 ? a.F.S > b.F.S: a.F.S < b.F.S);
}

int cl = 1, cr = 0;
int res[M];
int f[W];
int rf[M];

int getAns(int l, int r, int k)
{
    while (cr < r) add(f[w[++cr]]);
    while (cl < l) rem(f[w[cl++]]);
    while (cr > r) rem(f[w[cr--]]);
    while (cl > l) add(f[w[--cl]]);

    return rf[get(k)];
}

void setF()
{
    set<int> s;
    for (int i = 1; i <= n; ++i)
        s.ins(w[i]);
    int i = 0;
    for (int v: s)
    {
        f[v] = i;
        rf[i] = v;
        ++i;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> w[i];
    setF();

    forn (i, m)
    {
        int l, r, k;
        cin >> l >> r >> k;
        z[i].F.F = l;
        z[i].F.S = r;
        z[i].S.F = k;
        z[i].S.S = i;
    }
    sort(z, z + m, comp);

    for (int i = 0; i < m; ++i)
        res[z[i].S.S] = getAns(z[i].F.F, z[i].F.S, z[i].S.F);
    for (int i = 0; i < m; ++i)
        cout << res[i] << '\n';
    return 0;
}
