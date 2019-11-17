#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back
#define mp make_pair
#define F first
#define S second

const int K = 2e5 + 10;

typedef long long ll;
typedef double db;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<db, db> pdd;

int n;
ll cnt[K];
ll l[K];
ll r[K];

vector<pair<ll, int> > bounds;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    forn (i, n)
    {
        cin >> l[i] >> r[i];
        bounds.pb(mp(l[i], 0));
        bounds.pb(mp(r[i], 1));
    }
    sort(bounds.begin(), bounds.end());

    ll prev = 0;
    int k = 0;
    int i = 0;
    while (i < bounds.size())
    {
        ll bound = bounds[i].F;
        if (bounds[i].S == 0)
        {
            cnt[k] += bound - prev;
            prev = bound;
            while (bounds[i].S == 0 && bounds[i].F == bound)
            {
                ++k;
                ++i;
            }
        }
        else
        {
            cnt[k] += bound - prev + 1;
            prev = bound + 1;
            while (i < bounds.size() && bounds[i].S == 1 && bounds[i].F == bound)
            {
                --k;
                ++i;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        cout << cnt[i] << ' ';
    return 0;
}
