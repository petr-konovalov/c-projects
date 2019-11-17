#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define F first
#define S second
#define mp make_pair
#define pb push_back

const int N = 1e3 + 7, MOD = 998244353;

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

int n;
int dp[N];
int C[N][N];
int a[N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    forn (i, N)
        C[0][i] = 1;
    for (int i = 1; i < N; ++i)
    for (int j = i; j < N; ++j)
        C[i][j] = (C[i - 1][j - 1] + C[i][j - 1]) % MOD;
    cin >> n;
    forn (i, n)
        cin >> a[i];

    for (int i = n - 2; i >= 0; --i)
    {
        dp[i] = dp[i + 1];
        if (a[i] > 0 && i + a[i] < n)
        {
            for (int k = 1; i + a[i] + k <= n; ++k)
                dp[i] = (dp[i] + ((ll)C[a[i] - 1][a[i] + k - 2] * (dp[i + a[i] + k] + 1)) % MOD) % MOD;
        }
    }
    cout << dp[0];
    return 0;
}
