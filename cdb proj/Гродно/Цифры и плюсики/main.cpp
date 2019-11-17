#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define next next12932

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 1e3 + 7, P = 1e9 + 7;
const int M = 5100;

int n, b;
int dp[N][M];
pii pos[N][M];
int inp[N];
int next[N];

void printAns(pii p)
{
    if (p.F == -1)
        return;
    pii pr = pos[p.F][p.S];
    printAns(pr);
    if (pr.F != -1)
        cout << '+';
    for (int i = pr.F + 1; i <= p.F; ++i)
        cout << inp[i];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    char c;
    cin >> c;
    do
    {
        if ('0' <= c && c <= '9')
             inp[n++] = c - '0';
        cin >> c;
    } while (c != '=');
    cin >> b;

    next[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; --i)
        if (inp[i + 1] == 0)
            next[i] = next[i + 1];
        else
            next[i] = i + 1;
    next[n - 1] = n;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            dp[i][j] = -1;
    for (int i = 0, d = 0; (d = d * 10 + inp[i]) <= b; ++i)
    {
        dp[i][d] = 0;
        pos[i][d] = mp(-1, 0);
    }

    for (int p = 0; p < n - 1; ++p)
    {
        for (int k = 0; k <= b; ++k)
        {
            int d = 0;
            if (dp[p][k] == -1)
                continue;
            for (int i = p + 1; i < n && (d = d * 10 + inp[i]) <= b && k + d <= b; i = d == 0 ? next[i]: i + 1)
            {
                if (dp[i][k + d] == -1 || dp[p][k] + 1 < dp[i][k + d])
                {
                    dp[i][k + d] = dp[p][k] + 1;
                    pos[i][k + d] = mp(p, k);
                }
            }
        }
    }
    printAns(mp(n - 1, b));
    cout << '=' << b;
    return 0;
}
