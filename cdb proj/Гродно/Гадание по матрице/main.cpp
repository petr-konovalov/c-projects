#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define F first
#define S second

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;
typedef int Hash;

const int N = 3e2 + 10;
const int MOD = 1e9 + 7;
const ll seed = 3590823;

int n, m;
int inp[N][N];
int q[N];
int rq[N];
Hash hh[N][N];
Hash hv[N][N];
Hash rhh[N][N];
Hash rhv[N][N];

int binPow(int a, int deg)
{
    int res = 1;

    while (deg)
    {
        if (deg & 1)
            res = ((ll)res * a) % MOD;
        a = ((ll)a * a) % MOD;
        deg >>= 1;
    }

    return res;
}

void calcPrefHash()
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            hh[i][j] = (hh[i][j - 1] + inp[i][j] * q[j - 1]) % MOD;
            hv[i][j] = (hv[i - 1][j] + inp[i][j] * q[i - 1]) % MOD;
        }
    }

    for (int i = n; i >= 1; --i)
    {
        for (int j = m; j >= 1; --j)
        {
            rhh[i][j] = (rhh[i][j + 1] + inp[i][j] * q[m - j]) % MOD;
            rhv[i][j] = (rhv[i + 1][j] + inp[i][j] * q[n - i]) % MOD;
        }
    }
}

bool check(int x1, int y1, int x2, int y2)
{
    int horH = (ll)(((hh[x1][y2] - hh[x1][y1 - 1]) % MOD + MOD) % MOD) * rq[y1 - 1] % MOD;
    int verH = (ll)(((hv[x2][y1] - hv[x1 - 1][y1]) % MOD + MOD) % MOD) * rq[x1 - 1] % MOD;
    int rhorH = (ll)(((rhh[x2][y1] - rhh[x2][y2 + 1]) % MOD + MOD) % MOD) * rq[m - y2] % MOD;
    int rverH = (ll)(((rhv[x1][y2] - rhv[x2 + 1][y2]) % MOD + MOD) % MOD) * rq[n - x2] % MOD;

    return horH == rhorH && verH == rverH;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    q[0] = 1;
    q[1] = rand() % 10000;
    rq[0] = 1;
    rq[1] = binPow(q[1], MOD - 2);

    for (int i = 2; i < N; ++i)
    {
        q[i] = ((ll)q[i - 1] * q[1]) % MOD;
        rq[i] = ((ll)rq[i - 1] * rq[1]) % MOD;
    }

    cin >> n >> m;

    forn (i, n)
        forn (j, m)
        {
            char c;
            cin >> c;
            inp[i + 1][j + 1] = c - '0';
        }

    calcPrefHash();

    int ans = 1;
    for (int x = 1; x <= n; ++x)
    {
        for (int y = 1; y <= m; ++y)
        {
            for (int d = 1; (x - d) >= 1 && (x + d) <= n && (y - d) >= 1 && (y + d) <= m && check(x - d, y - d, x + d, y + d); ++d)
            {
                ans = max(ans, 2 * d + 1);
            }
            for (int d = 1; (x - d + 1) >= 1 && (x + d) <= n && (y - d + 1) >= 1 && (y + d) <= m && check(x - d + 1, y - d + 1, x + d, y + d); ++d)
            {
                ans = max(ans, 2 * d);
            }
        }
    }

    cout << ans;

    return 0;
}
