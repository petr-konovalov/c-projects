#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;

const int P = 1e9 + 7;
int prm[19] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
               37, 41, 43, 47, 53, 59, 61, 67};

int binPow(int a, int deg)
{
    int res = 1;
    while (deg)
    {
        if (deg & 1)
            res = (a * 1ll * res) % P;
        a = (a * 1ll * a) % P;
        deg >>= 1;
    }
    return res;
}

int dp[2048];
int ndp[2048];
bool exist[2048];
bool nexist[2048];
int cnt[8];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    vector<int> fGroop;
    cin >> n;
    forn (i, n)
    {
        int cur;
        cin >> cur;
        bool f = true;
        for (int i = 11; f && i < 19; ++i)
            if (cur == prm[i])
                ++cnt[i - 11], f = false;
        if (f)
        {
            int num = 0;
            forn (i, 11)
                while (cur % prm[i] == 0)
                {
                    num ^= (1 << i);
                    cur /= prm[i];
                }
            fGroop.pb(num);
        }
    }
    exist[0] = true;
    nexist[0] = true;
    ndp[0] = 1;
    dp[0] = 1;
    for (int cur: fGroop)
    {
        forn (i, 2048)
            if (exist[i])
            {
                int next = cur ^ i;
                ndp[next] = (ndp[next] + dp[i]) % P;
                nexist[next] = true;
            }
        forn (i, 2048)
        {
            dp[i] = ndp[i];
            exist[i] = nexist[i];
        }
    }
    int ans = dp[0];
    forn (i, 8)
        if (cnt[i] > 1)
            ans = (ans * 1ll * binPow(2, cnt[i] - 1)) % P;
    cout << ans - 1;
    return 0;
}
