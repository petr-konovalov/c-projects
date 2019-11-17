
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

const int N = 1e5 + 5, B = 5000, MS = 2 * N + 1;

struct Req
{
    char type;
    int p[4];
};

struct Fenv
{
    int t[MS];
    Fenv()
    {
        forn (i, MS)
            t[i] = 0;
    }

    void add(int item)
    {
        for (int i = item; i < MS; i = i | (i + 1))
            ++t[i];
    }

    void rem(int item)
    {
        for (int i = item; i < MS; i = i | (i + 1))
            --t[i];
    }

    int pref(int item)
    {
        int res = 0;
        for (int i = item; i >= 0; i = (i & (i + 1)) - 1)
            res += t[i];
        return res;
    }
};

int n, m;
Req req[N];

int arr[N];
list<int> tb[MS / B + 1];
Fenv tbl[MS / B + 1];

int read()
{
    int value;
    cin >> value;
    return value;
}

list<int>::iterator getIt(list<int> &l, int pos)
{
    list<int>::iterator it;
    if (2 * pos < l.size())
    {
        it = l.begin();
        while (--pos >= 0)
            ++it;
    }
    else
    {
        it = l.end();
        while (++pos <= l.size())
            --it;
    }
    return it;
}

void add(int index, int value)
{
    int bl = index / B, pos = index % B;
    list<int>::iterator it = getIt(tb[bl], pos);

    tb[bl].insert(it, value);
    tbl[bl].add(value);
    for (int i = bl; tb[i].size() > B; ++i)
    {
        tb[i + 1].push_front(tb[i].back());
        tbl[i + 1].add(tb[i].back());
        tbl[i].rem(tb[i].back());
        tb[i].pop_back();
    }
}

void rem(int index)
{
    int bl = index / B, pos = index % B;
    list<int>::iterator it = getIt(tb[bl], pos);

    tbl[bl].rem(*it);
    tb[bl].erase(it);
    for (int i = bl + 1; tb[i].size() > 0; ++i)
    {
        tb[i - 1].pb(tb[i].front());
        tbl[i].rem(tb[i].front());
        tbl[i - 1].add(tb[i].front());
        tb[i].erase(tb[i].begin());
    }
}

int get(int b, int l, int r, int x)
{
    int res = 0;
    int pl = l % B, pr = r % B;
    if (pr - pl + 1 < pl + (int)tb[b].size() - pr)
    {
        auto it = getIt(tb[b], pl);
        for (int i = 0, e = r - l + 1; i < e; ++i, ++it)
            if (*it <= x)
                ++res;
    }
    else
    {
        res = tbl[b].pref(x);
        auto it = tb[b].begin();
        for (int i = 0; i < pl; ++i, ++it)
            if (*it <= x)
                --res;
        it = tb[b].end();
        --it;
        for (int i = (int)tb[b].size() - 1; i > pr; --i, --it)
            if (*it <= x)
                --res;
    }

    return res;
}

int get(int l, int r, int x)
{
    int bl = l / B, br = r / B, res = 0;
    if (bl == br)
        res = get(bl, l, r, x);
    else
    {
        res += get(bl, l, (bl + 1) * B - 1, x);
        res += get(br, br * B, r, x);
        for (int i = bl + 1; i < br; ++i)
            res += tbl[i].pref(x);
    }

    return res;
}

map<int, int> vals;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    forn (i, n)
        vals[arr[i] = read()] = 0;

    while (cin >> req[m].type)
    {
        switch(req[m].type)
        {
        case '+':
            cin >> req[m].p[0] >> req[m].p[1];
            vals[req[m].p[1]] = 0;
            break;
        case '-':
            cin >> *req[m].p;
            break;
        case '?':
            cin >> req[m].p[0] >> req[m].p[1] >> req[m].p[2];
            vals[req[m].p[2]] = 0;
            break;
        default:
            break;
        }
        ++m;
    }

    int cnt = 0;
    for (auto &it: vals)
        it.second = cnt++;

    forn (i, n)
    {
        int item = vals[arr[i]];
        int bl = i / B;
        tb[bl].pb(item);
        tbl[bl].add(item);
    }

    forn (i, m)
    {
        switch (req[i].type)
        {
        case '+':
            add(req[i].p[0], vals[req[i].p[1]]);
            break;
        case '?':
            cout << get(req[i].p[0], req[i].p[1], vals[req[i].p[2]]) << '\n';
            break;
        case '-':
            rem(*req[i].p);
            break;
        default:
            break;
        }
    }

    return 0;
}
