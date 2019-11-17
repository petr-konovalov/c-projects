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

typedef long long ll;
typedef double db;
typedef float fl;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<db, db> pdd;
typedef pair<ll, ll> pll;
typedef pair<pii, int> ti;

const int N = 2e5 + 5, P = 1e9 + 7;
int hp[N];
int dmg[N];
pii p[N];
int a, b;
ll ans = 0;
ll cur = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n >> a >> b;
    ll d = 1 << a;
    forn (i, n)
    {
        cin >> hp[i] >> dmg[i];
        p[i] = mp(hp[i] - dmg[i], i);
    }
    sort(p, p + n);
    if (b > 0)
    {
        int j = n;
        for (int i = n - 1; i >= n - b + 1 && i >= 0 && p[i].F > 0; --i)
        {
            cur += hp[p[i].S];
            j = i;
        }
        for (int i = 0; i < j; ++i)
        {
            cur += dmg[p[i].S];
        }
        ans = cur;
        for (int i = 0; i < j; ++i)
        {
            ll nans = cur - dmg[p[i].S] + d * hp[p[i].S];
            ans = max(ans, nans);
        }
        if (j > 0 && p[j - 1].F > 0)
            cur = cur + p[j - 1].F;
        ans = max(ans, cur);
        for (int i = j; i < n; ++i)
        {
            ll nans = cur + (d - 1) * hp[p[i].S];
            ans = max(ans, nans);
        }
        cout << ans;
    }
    else
    {
        forn (i, n)
            ans += dmg[i];
        cout << ans;
    }
    return 0;
}
