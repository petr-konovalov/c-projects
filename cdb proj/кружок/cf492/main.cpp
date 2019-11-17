#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define ins insert
#define ers erase

typedef unsigned long long ull;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const ll seed = 98712398742;

const int N = 1e5 + 7;
const ll radius = 1000000;
const ll r = radius * radius;
const ll R = 1.5 * 1.5 * radius * radius;

mt19937 gen(seed);
int n;

vector<pair<pii, int> > inp;

pii operator* (pii v, int c)
{
    return mp(v.F * c, v.S * c);
}

pii operator+ (pii v1, pii v2)
{
    return mp(v1.F + v2.F, v1.S + v2.S);
}

pii operator- (pii v1, pii v2)
{
    return mp(v1.F - v2.F, v1.S - v2.S);
}

bool cmp(pair<pii, int> v1, pair<pii, int> v2)
{
    auto a1 = atan2(v1.F.S, v1.F.F);
    auto a2 = atan2(v2.F.S, v2.F.F);
    return a1 < a2;
}

ll len2(pii v)
{
    return (ll)v.F * v.F + (ll)v.S * v.S;
}

vector<int> findAns(const vector<pair<pii, int> > &v)
{
    int sz = 1 << v.size();
    for (int mask = 0; mask < sz; ++mask)
    {
        int w = mask;
        pii cur = mp(0, 0);
        for (int i = 0; i < v.size(); ++i, w >>= 1)
            cur = cur + v[i].F * (2 * (w & 1) - 1);
        if (len2(cur) <= R)
        {
            w = mask;
            vector<int> res(v.size());
            for (int i = 0; i < v.size(); ++i, w >>= 1)
                res[i] = 2 * (w & 1) - 1;
            return res;
        }
    }
}

vector<int> getAns(vector<pair<pii, int> > &v)
{
    if (v.size() <= 15)
        return findAns(v);
    vector<int> res(v.size());
    sort(v.begin(), v.end(), cmp);
    vector<pair<pii, int> > nv;

    for (int i = 0; i < v.size(); )
    {
        if (i + 1 < v.size() && len2(v[i + 1].F - v[i].F) <= r)
        {
            res[i] = -1;
            res[i + 1] = 1;
            nv.pb(mp(v[i + 1].F - v[i].F, (int)nv.size()));
            i += 2;
        }
        else
        {
            res[i] = 1;
            nv.pb(mp(v[i].F, (int)nv.size()));
            ++i;
        }
    }
    vector<int> nres = getAns(nv);
    for (int i = 0, j = 0; i < nres.size(); ++i)
    {
        if (res[j] == -1)
            res[j++] *= nres[i];
        res[j] *= nres[i];
        ++j;
    }
    vector<int> ans(res.size());
    for (int i = 0; i < res.size(); ++i)
        ans[v[i].S] = res[i];
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    //debug("%i64d\n", seed);
    cin >> n;

    forn (i, n)
    {
        int x, y;
        /*
        int x = (gen() + radius / 4) % radius, y = (gen() + radius / 4) % radius;
        while (len2(mp(x, y)) > r)
            x = (gen() + radius / 4) % radius, y = (gen() + radius / 4) % radius;
        x *= 2 * (int)(gen() % 2) - 1;
        y *= 2 * (int)(gen() % 2) - 1;
        //debug("%lli %lli\n", x, y);
        */
        cin >> x >> y;
        inp.pb(mp(mp(x, y), i));
    }

    vector<int> ans = getAns(inp);

    for (int i = 0; i < n; ++i)
        cout << ans[i] << ' ';
    /*
    debug("\n----------\n");
    pll cur = mp(0, 0);
    for (int i = 0; i < n; ++i)
        cur = cur + inp[i].F * ans[inp[i].S];
    debug("%i\n", len2(cur) <= R ? 1 : 0);
    */

    return 0;
}
