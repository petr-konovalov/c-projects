#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define sqr(x) ((x) * (x))
#define all(a) a.begin(), a.end()

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;
typedef ll T;

const int N = 1e5 + 9;
vector<pair<int, pii> > a;
int cnt_clr[N];

bool cmp(pair<int, pii> a, pair<int, pii> b)
{
    return a.x < b.x;
}

int main()
{
    int c, l, r, n, k, m;
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> k >> m;
    forn(i, m)
    {
        cin >> c >> l >> r;
        a.pb(mp(l, mp(c, 0)));
        a.pb(mp(r, mp(c, 1)));
    }
    sort(all(a), cmp);
    for(int i = 1; i < a.size(); i++)
    {
        if (a[i].y.y == 0 && a[i - 1].y.y == 0)
            cnt_clr[a[i - 1].y.x] += a[i].x - a[i - 1].x;
        if (a[i].y.y == 1 && a[i - 1].y.y == 1)
            cnt_clr[a[i].y.x] += a[i].x - a[i - 1].x;
        if (a[i].y.y == 1 && a[i - 1].y.y == 0)
            cnt_clr[a[i - 1].y.x] += a[i].x - a[i - 1].x;
    }
    for(int i = 1; i <= k; i++)
        cout << cnt_clr[i] << " ";
    return 0;
}
