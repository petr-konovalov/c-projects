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

const int N = 505, M = 998244353;

int n, k;
int dp[N][N];
int cnt[N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
    {
        dp[1][i] = 1;
    }

    for (int i = 2; i <= n; ++i)
    {
        dp[i][i] = 1;
        for (int pos = i + 1; pos <= n; ++pos)
        {
            for (int j = 1; j < i; ++j)
                dp[i][pos] = (dp[i][pos] + dp[i][pos - j]) % M;
            for (int j = 1; j <= i; ++j)
                dp[i][pos] = (dp[i][pos] + dp[j][pos - i]) % M;
        }
    }

    for (int i = 1; i <= n; ++i)
        cnt[i] = dp[i][n];

    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n && i * j < k; ++j)
        {
            ans = (ans + (ll)cnt[i] * cnt[j]) % M;
        }
    }
    cout << (ans + ans) % M;

    return 0;
}
