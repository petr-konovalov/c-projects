#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define sqr(x) ((x) * (x))
#define sz(c) int((c).size())
#define all(c) c.begin(), c.end()

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;
//typedef ll T;

const ll N = 1e5 + 9, INF = 1e18 + 7;

struct segment_tree
{
    sum () {}
    ll add, mx;
};

segment_tree t[4 * N];
ll a[N];

void build_tree(int v, int tl, int tr)
{
    if (tl == tr)
    {
        t[v].mx = a[tl];
        return;
    }
    int tm = (tl + tr) / 2;
    build_tree(v * 2, tl, tm);
    build_tree(v * 2 + 1, tm + 1, tr);
    t[v].mx = max(t[v * 2].mx, t[v * 2 + 1].mx);
}

void push(int v, int tl, int tr)
{
    if (t[v].add != 0)
    {
        t[v].mx = t[v].mx + t[v].add * (tr - tl + 1);
        if (tl != tr)
        {
            t[v * 2].add += t[v].add;
            t[v * 2 + 1].add += t[v].add;
        }
        t[v].add = 0;
    }
}

void update(int v, int tl, int tr, int l, int r, int x)
{
    if (l > r)
        return;
    push(v, tl, tr);
    if (tl == l && tr == r)
    {
        t[v].add += x;
        return;
    }
    int tm = (tl + tr) / 2;
    update(v * 2, tl, tm, l, min(r, tm), x);
    update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x);
}

ll get(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return -INF;
    push(v, tl, tr);
    if (tl == l && tr == r)
        return t[v].mx;
    int tm = (tl + tr) / 2;
    return max(get(v * 2, tl, tm, l, min(r, tm)),
                get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

int main()
{
    int n, m, l, r, x;
    char c;
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    forn(i, n)
        cin >> a[i];
    build_tree(1, 0, n - 1);
    cin >> m;
    forn(i, m)
    {
        cin >> c >> l >> r;
        l--;
        r--;
        if (c == 'a')
        {
            cin >> x;
            update(1, 0, n - 1, l, r, x);
        }
        else
        {
            cout << get(1, 0, n - 1, l, r) << endl;
        }
    }
    return 0;
}
