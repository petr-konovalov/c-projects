#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define X first
#define Y second

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 3e3 + 7, INF = 1e9 + 7;
const ll INF64 = (ll)1e18 + 3;

int n, m;
int p[N], c[N];
int cnt[N];
ll ans = INF64;
vector<pii> costOrd;
vector<pii> pcost[N];
bool block[N];

int getMax()
{
    int res = 2;

    for (int i = 3; i <= m; ++i)
    {
        if (cnt[i] > cnt[res] || cnt[i] == cnt[res] && cnt[i] > 0 && pcost[i].back().X < pcost[res].back().X)
            res = i;
    }

    return res;
}

ll check(int mx)
{
    int t = 0;
    ll cost = 0;

    for (int i = 0; cnt[1] + t <= mx && i < costOrd.size(); ++i)
    {
        if (!block[costOrd[i].Y])
        {
            ++t;
            cost += costOrd[i].X;
        }
    }

    return cost;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    forn (i, n)
    {
        cin >> p[i];
        cin >> c[i];
        ++cnt[p[i]];
        if (p[i] != 1)
        {
            costOrd.pb(mp(c[i], i));
            pcost[p[i]].pb(mp(-c[i], i));
        }
    }
    sort(costOrd.begin(), costOrd.end());
    for (int i = 1; i <= m; ++i)
        sort(pcost[i].begin(), pcost[i].end());
    for (int i = 1; i <= m; ++i)
        for (int j = 0; j < pcost[i].size(); ++j)
            pcost[i][j].X *= -1;

    ll cur = 0;
    //debug("\n--------------\n");
    for (int i = 0; i < n; ++i)
    {
        int mx = getMax();
        ans = min(ans, check(cnt[mx]) + cur);
        if (cnt[mx] == 0)
            break;
        //debug("%lli\n", ans);
        //debug("%i %i\n", mx, pcost[mx].back().X);

        block[pcost[mx].back().Y] = true;
        cur += pcost[mx].back().X;
        ++cnt[1];
        --cnt[mx];
        pcost[mx].pop_back();
    }

    cout << ans;

    return 0;
}
