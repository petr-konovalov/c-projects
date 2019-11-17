#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define div div12342

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 2e5 + 7, INF = 2e9 + 7;
const ll INF64 = (ll)1e18 + 3;

int n, m;
pii inp[N];
vector<pii> div;

void fact(int n)
{
    for (int i = 2; (ll)i * i <= n; ++i)
        if (n % i == 0)
        {
            div.pb(mp(i, 1));
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        div.pb(mp(n, 1));
}

void check(pii a)
{
    for (pii &it: div)
    {
        if (a.X % it.X == 0 || a.Y % it.X == 0)
            ++it.Y;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    forn (i, n)
        cin >> inp[i].X >> inp[i].Y;

    fact(inp[0].X);
    fact(inp[0].Y);
    for (int i = 1; i < n; ++i)
        check(inp[i]);

    for (int i = 0; i < div.size(); ++i)
        if (div[i].Y == n)
        {
            cout << div[i].X;
            return 0;
        }
    cout << -1;
    return 0;
}
