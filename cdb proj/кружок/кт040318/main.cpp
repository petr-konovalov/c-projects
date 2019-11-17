#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define sqr(x) (x) * (x)
#define X first
#define Y second
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase

typedef long long ll;
typedef double db;
typedef float fl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e5 + 5, S = 1000, B = 105;

struct Fenv
{
    ll t[N];

    Fenv()
    {
        forn (i, N)
            t[i] = 0;
    }

    void add(int index, int val)
    {
        for (int i = index; i < N; i = i | (i + 1))
            t[i] += val;
    }

    ll get(int index)
    {
        ll sum = 0;
        for (int i = index; i >= 0; i = (i & (i + 1)) - 1)
            sum += t[i];
        return sum;
    }
};

vector<int> g[N];
vector<int> ord;
int pos[N];
int ccnt[N];
int rg[N];
int tmm[N];
Fenv blc[B];

void topSort(int v)
{
    ccnt[v] = 0;
    for (int to: g[v])
    {
        topSort(to);
        ccnt[v] += ccnt[to] + 1;
    }
    pos[v] = ord.size();
    ord.pb(v);
}

ll get(int l, int r, int rank)
{
    int bl = l / S, br = r / S;
    ll res = 0;
    if (bl == br)
    {
        for (int i = l; i <= r; ++i)
            if (rg[ord[i]] < rank)
                res += tmm[ord[i]];
    }
    else
    {
        for (int i = bl + 1; i < br; ++i)
            res += blc[i].get(rank - 1);
        for (int i = l, e = (bl + 1) * S; i < e; ++i)
            if (rg[ord[i]] < rank)
                res += tmm[ord[i]];
        for (int i = br * S; i <= r; ++i)
            if (rg[ord[i]] < rank)
                res += tmm[ord[i]];
    }
    return res;
}

int n;

void calc()
{
    for (int i = 0; i < n; ++i)
        blc[i / S].add(rg[ord[i]], tmm[ord[i]]);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    int v = 0;
    for (int i = 1; i <= n; ++i)
    {
        int p, r, t;
        cin >> p >> r >> t;
        rg[i] = r;
        tmm[i] = t;
        if (p != -1)
            g[p].pb(i);
        else
            v = i;
    }
    topSort(v);
    calc();
    for (int i = 1; i <= n; ++i)
    {
        if (ccnt[i] == 0)
            cout << 0 << '\n';
        else
            cout << get(pos[i] - ccnt[i], pos[i] - 1, rg[i]) << '\n';
    }
    return 0;
}
