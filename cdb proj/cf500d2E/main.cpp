#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
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

const int N = 5000 + 10, INF = 1e9 + 7;

int n;
int inp[N];

/**
 * 0 - take
 * 1 - decrease
 * 2 - ignore
 */
int dp[3][N][N / 2];

int div2Up(int a)
{
    return (a >> 1) + (a & 1);
}

int min3(int a, int b, int c)
{
    return min(a, min(b, c));
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    forn (i, n)
        cin >> inp[i + 1];
    inp[0] = -INF;

    for (int i = 0; i < N; ++i)
        for (int k = 1; k < N / 2; ++k)
            for (int j = 0; j < 3; ++j)
                dp[j][i][k] = INF;

    dp[0][1][1] = 0;
    for (int i = 2; i <= n; ++i)
    {
        for (int k = 1; k <= div2Up(i); ++k)
        {
            dp[0][i][k] = dp[0][i - 2][k - 1] + inp[i - 1] - min3(inp[i - 1], inp[i] - 1, inp[i - 2] - 1);
            dp[0][i][k] = min(dp[0][i][k],
                min(dp[1][i - 2][k - 1], dp[2][i - 2][k - 1]) + inp[i - 1] - min(inp[i - 1], inp[i] - 1));
            dp[1][i][k] = dp[0][i - 1][k] + inp[i] - min(inp[i], inp[i - 1] - 1);
            dp[2][i][k] = min(dp[1][i - 1][k], dp[2][i - 1][k]);
        }
    }
    for (int k = 1; k <= div2Up(n); ++k)
        cout << min3(dp[0][n][k], dp[1][n][k], dp[2][n][k]) << ' ';
    return 0;
}
