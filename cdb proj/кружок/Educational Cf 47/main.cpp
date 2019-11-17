#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase

typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e5 + 7, INF = 1e9 + 7;
const ll INF64 = 1e18;

int n, m;
ll s;
ll a, b;
ld ans;
vector<int> g[N];
int sz;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    if (m < n - 1)
    {
        cout << "Impossible\n";
        return 0;
    }
    else
    {
        for (int i = 2; i <= n; ++i)
            g[1].pb(i);
        sz = n - 1;

        for (int i = 2; i <= n && sz < m; ++i)
        {
            for (int j = 1; j < i && sz < m; ++j)
            {
                for (int k = 1; j + i * k < n && sz < m; ++k)
                {
                    if (gcd(i, j + i * k) == 1)
                    {
                        g[i].pb(j + i * k);
                        ++sz;
                    }
                }
            }
        }
        //debug("%i\n", sz);
        if (sz < m)
        {
            cout << "Impossible\n";
            return 0;
        }
        cout << "Possible\n";
        for (int i = 1; i <= n; ++i)
        {
            for (int to: g[i])
                cout << i << ' ' << to << '\n';
        }
    }

    return 0;
}
