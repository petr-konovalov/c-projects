#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define L first
#define R second
#define ins insert
#define ers erase
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef float fl;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e5 + 5, B = 1300, INF = 1e9 + 3;

int tb[N];
pii tbl[N / B + 3][B];
int tch[N / B + 3];
int n, m;

void pre()
{
    tbl[0][0] = mp(INF, 0);
    for (int i = 1; i <= n; ++i)
        tbl[i / B][i % B] = mp(tb[i], i);
    for (int i = n % B + 1, b = n / B; i < B; ++i)
        tbl[b][i] = mp(INF, b + i);
    for (int i = 0, e = n / B; i <= e; ++i)
        sort(tbl[i], tbl[i] + B);
}

bool comp(pii a, pii b)
{
    return a.L < b.L;
}

void push(int block)
{
    for (int i = 0; i < B; ++i)
    {
        tbl[block][i].L += tch[block];
        tb[block * B + i] += tch[block];
    }
    tch[block] = 0;
}

bool check(int l, int r, int x)
{
    int bl = l / B, br = r / B;
    if (bl == br)
    {
        push(bl);
        for (int i = l; i <= r; ++i)
            if (tb[i] == x)
                return true;
    }
    else
    {
        push(bl);
        push(br);
        for (int i = l, e = B * (bl + 1); i < e; ++i)
            if (tb[i] == x)
                return true;
        for (int i = B * br; i <= r; ++i)
            if (tb[i] == x)
                return true;
        for (int i = bl + 1; i < br; ++i)
            if (lower_bound(tbl[i], tbl[i] + B, mp(x - tch[i], 0), comp)->L == x - tch[i])
                return true;

    }
    return false;
}

void change(int l, int r, int x)
{
    int bl = l / B, br = r / B;
    if (bl == br)
    {
        pii af[B], as[B];
        int cf = 0, cs = 0;
        push(bl);
        for (int i = l; i <= r; ++i)
            tb[i] += x;
        for (int i = 0; i < B; ++i)
            if (l <= tbl[bl][i].R && tbl[bl][i].R <= r)
                af[cf++] = mp(tbl[bl][i].L + x, tbl[bl][i].R);
            else
                as[cs++] = mp(tbl[bl][i].L, tbl[bl][i].R);
        merge(af, af + cf, as, as + cs, tbl[bl]);
    }
    else
    {
        change(l, (bl + 1) * B - 1, x);
        change(br * B, r, x);
        for (int i = bl + 1; i < br; ++i)
            tch[i] += x;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> tb[i];
    pre();
    forn (i, m)
    {
        char c;
        int l, r, x;
        cin >> c >> l >> r >> x;
        if (c == '+')
            change(l, r, x);
        else
            cout << (check(l, r, x) ? "YES": "NO") << '\n';
    }
    return 0;
}
