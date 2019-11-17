#include <bits/stdc++.h>

using namespace std;

#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define forn(i, n) for (int i = 0; i < n; ++i)
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase
#define L first
#define R second

typedef long long ll;
typedef float fl;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 5e4 + 2, B = 3000, M = 1e5 + 2, MS = M + N;

int f[MS];

struct Sumset
{
    int t[MS];
    long long sum = 0;

    Sumset()
    {
        for (int i = 0; i < MS; ++i)
            t[i] = 0;
    }

    void add(int v)
    {
        if (t[v] == 0)
            sum += f[v];
        ++t[v];
    }

    void rem(int v)
    {
        if (t[v] == 1)
            sum -= f[v];
        --t[v];
    }
};

struct Req
{
    char type;
    int f;
    int s;
};

int a[N + B + 3] = {0};
int temp[N + B + 3] = {0};
int n, m;
Req req[M];
Sumset t[N / B + 1][N / B + 1];

int read()
{
    int val;
    cin >> val;
    return val;
}

void change(int pos, int v)
{
    int b = pos / B;
    for (int i = 0; i <= b; ++i)
        for (int j = b, e = N / B; j <= e; ++j)
        {
            t[i][j].rem(a[pos]);
            t[i][j].add(v);
        }
    a[pos] = v;
}

Sumset buf;

long long getAns(int l, int r)
{
    int bl = l / B, br = r / B;
    bool ff = 2 * (l % B) < B, ss = 2 * (r % B) < B;
    int bf = bl + 1 - (ff ? 1: 0), bs = br - (ss ? 1 : 0);

    if (bf <= bs)
    {
        if (ff)
            for (int i = bl * B; i < l; ++i)
                t[bf][bs].rem(a[i]);
        else
            for (int i = (bl + 1) * B - 1; i >= l; --i)
                t[bf][bs].add(a[i]);
        if (ss)
            for (int i = br * B; i <= r; ++i)
                t[bf][bs].add(a[i]);
        else
            for (int i = (br + 1) * B - 1; i > r; --i)
                t[bf][bs].rem(a[i]);

        long long res = t[bf][bs].sum;

        if (ff)
            for (int i = bl * B; i < l; ++i)
                t[bf][bs].add(a[i]);
        else
            for (int i = (bl + 1) * B - 1; i >= l; --i)
                t[bf][bs].rem(a[i]);
        if (ss)
            for (int i = br * B; i <= r; ++i)
                t[bf][bs].rem(a[i]);
        else
            for (int i = (br + 1) * B - 1; i > r; --i)
                t[bf][bs].add(a[i]);

        return res;
    }
    else
    {
        for (int i = l; i <= r; ++i)
            buf.add(a[i]);
        long long res = buf.sum;
        for (int i = l; i <= r; ++i)
            buf.rem(a[i]);
        return res;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    set<int> vals;
    for (int i = 1; i <= n; ++i)
        vals.ins(temp[i] = read());

    cin >> m;
    forn(i, m)
    {
        cin >> req[i].type >> req[i].f >> req[i].s;
        if (req[i].type == 'U')
            vals.ins(req[i].s);
    }

    int cnt = 1;
    f[0] = 0;
    for (auto item: vals)
        f[cnt++] = item;

    for (int i = 1; i <= n; ++i)
        a[i] = lower_bound(f, f + cnt, temp[i]) - f;

    for (int i = 0, e = N / B + 1; i < e; ++i)
        for (int j = i; j < e; ++j)
            for (int k = i * B, ek = (j + 1) * B; k < ek; ++k)
                t[i][j].add(a[k]);

    forn (i, m)
    {
        if (req[i].type == 'Q')
            cout << getAns(req[i].f, req[i].s) << '\n';
        else
            change(req[i].f, lower_bound(f, f + cnt, req[i].s) - f);
    }

    return 0;
}
