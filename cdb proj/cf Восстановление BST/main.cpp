#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define sqr(x) ((x) * (x))

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 705;

int inp[N];
pair<bool, bool> dp[N][N];
int pre[N][N];
vector<int> lf[N];
vector<int> rg[N];
int n;

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

    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> inp[i];
    inp[0] = inp[n + 1] = 0;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            pre[i][j] = gcd(inp[i], inp[j]);

    for (int i = 0; i <= n; ++i)
        dp[i + 1][i] = mp(true, true);

    for (int i = 1; i <= n; ++i)
    {
        dp[i][i].X = pre[i - 1][i] != 1;
        dp[i][i].Y = pre[i + 1][i] != 1;
    }

    for (int len = 2; len <= n; ++len)
    {
        for (int lf = 1, rg = 1; (rg = lf + len - 1) <= n; ++lf)
        {
            for (int k = lf; k <= rg; ++k)
            {
                if (dp[lf][k - 1].Y && dp[k + 1][rg].X)
                {
                    if (pre[lf - 1][k] != 1)
                        dp[lf][rg].X = true;
                    if (pre[rg + 1][k] != 1)
                        dp[lf][rg].Y = true;
                }
            }
        }
    }
    cout << (dp[1][n].X ? "Yes\n": "No\n");

    return 0;
}
