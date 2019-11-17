#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define ins insert
#define ers erase
#define F first
#define S second

typedef long long ll;
typedef double db;
typedef float fl;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 2e5+10, INF = 1e9 + 7;
const ll INF64 = 1e18;
const ll seed = time(0);
const ld eps = 1e-9;

mt19937 gen(seed);
int n, a, b;
int x[N];
pll v[N];
pair<ll, int> pr[N];

ld len(pdd v)
{
    return sqrt((ld)v.F * v.F + (ld)v.S * v.S);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    debug("%ld\n", seed);
    cin >> n >> a >> b;
    forn (i, n)
    {
        cin >> x[i] >> v[i].F >> v[i].S;
    }
    sort(v, v + n);
    pr[0].F = -a * v[0].F + v[0].S;
    pr[0].S = 1;
    int j = 0;
    for (int i = 1; i < n; ++i)
    {
        if (v[i] == v[i - 1])
            ++pr[j].S;
        else
        {
            ++j;
            pr[j].F = -a * v[i].F + v[i].S;
            pr[j].S = 1;
        }
    }
    sort(pr, pr + j + 1);
    ll ans = 0;
    ll sum = pr[0].S;
    int jj = 0;
    for (int i = 1; i <= j; ++i)
    {
        if (pr[i].F == pr[i - 1].F)
        {
            ans += sum * pr[i].S;
            sum += pr[i].S;
        }
        else
        {
            sum = pr[i].S;
            jj = i;
        }
    }
    cout << 2 * ans;
    return 0;
}
