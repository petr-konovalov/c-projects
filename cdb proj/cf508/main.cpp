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

const int N = 5e5 + 7;
const int INF = 1e9 + 7;

int n, k;
int inp[N];
bool otr = false;
bool pol = false;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    forn (i, n)
    {
        cin >> inp[i];
        otr = otr || inp[i] < 0;
        pol = pol || inp[i] >= 0;
    }

    if (n == 1)
    {
        cout << inp[0];
        return 0;
    }

    if (otr && pol)
    {
        ll ans = 0;
        forn (i, n)
            ans += abs(inp[i]);
        cout << ans;
        return 0;
    }
    else
    {
        ll ans = 0;
        int m = INF;
        forn (i, n)
        {
            ans += abs(inp[i]);
            m = min(m, abs(inp[i]));
        }
        cout << ans - 2 * m;
        return 0;
    }

    return 0;
}
