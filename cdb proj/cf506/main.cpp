#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define sqr(x) ((x) * (x))

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 2e5 + 7, INF = 1e9 + 7;
const ll INF64 = (ll)1e18 + 3;

int n, k;
int inp[N];
int a[N][11];
ll ans = 0;
unordered_map<int, int> cnt[11];
int d10[11];

int calc(int num)
{
    int ost = (k - num) % k;
    if (ost < 0)
        ost += k;

    int ncnt = 1;
    while (ncnt < 10 && d10[ncnt] <= num)
        ++ncnt;

    auto it = cnt[ncnt].find(ost);

    return it == cnt[ncnt].end() ? 0: it->Y;
}

void add(int id)
{
    for (int i = 1; i <= 10; ++i)
        ++cnt[i][a[id][i]];
}

void rem(int id)
{
    for (int i = 1; i <= 10; ++i)
        --cnt[i][a[id][i]];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k;

    d10[0] = 1;
    for (int i = 1; i < 10; ++i)
        d10[i] = d10[i - 1] * 10;

    forn (i, n)
    {
        cin >> inp[i];
        a[i][0] = inp[i];
    }

    forn (i, n)
    {
        for (int deg = 1; deg <= 10; ++deg)
            a[i][deg] = ((ll)a[i][deg - 1] * 10) % k;
    }

    forn (i, n)
        add(i);

    forn (i, n)
    {
        rem(i);
        ans += calc(inp[i]);
        add(i);
    }

    cout << ans;

    return 0;
}
