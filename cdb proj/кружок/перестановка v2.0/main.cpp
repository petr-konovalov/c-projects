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
typedef pair<double, double> pdd;

const int N = 1e5 + 5, B = 1300;

struct Fenv
{
    int t[N];

    fenv()
    {
        for (int i = 0; i < N; ++i)
            t[i] = 0;
    }

    void add(int value)
    {
        for (int i = value; i < N; i = i | (i + 1))
            ++t[i];
    }

    void rem(int value)
    {
        for (int i = value; i < N; i = i | (i + 1))
            --t[i];
    }

    int pref(int value)
    {
        int res = 0;
        for (int i = value; i >= 0; i = (i & (i + 1)) - 1)
            res += t[i];
        return res;
    }

    int sum(int l, int r)
    {
        return pref(r) - pref(l - 1);
    }
};

int tb[N];
Fenv tbl[N / B + 1];

void change(int index, int value)
{
    int block = index / B;
    tbl[block].rem(tb[index]);
    tbl[block].add(value);
    tb[index] = value;
}

int n, m;

int get(int x, int y, int k, int l)
{
    int bx = x / B, by = y / B, res = 0;
    if (bx == by)
    {
        for (int i = x; i <= y; ++i)
            if (k <= tb[i] && tb[i] <= l)
                ++res;
    }
    else
    {
        for (int i = x, e = B * (bx + 1); i < e; ++i)
            if (k <= tb[i] && tb[i] <= l)
                ++res;
        for (int i = B * by; i <= y; ++i)
            if (k <= tb[i] && tb[i] <= l)
                ++res;
        for (int i = bx + 1; i < by; ++i)
            res += tbl[i].sum(k, l);
    }
    return res;
}

int read()
{
    int value;
    cin >> value;
    return value;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        int value = read();
        tb[i] = value;
        tbl[i / B].add(value);
    }
    forn (i, m)
    {
        char inp[8];
        cin >> inp;
        if (inp[0] == 'S')
        {
            int a, b;
            cin >> a >> b;
            change(a, b);
        }
        else
        {
            int x, y, k, l;
            cin >> x >> y >> k >> l;
            cout << get(x, y, k, l) << '\n';
        }
    }

    return 0;
}
