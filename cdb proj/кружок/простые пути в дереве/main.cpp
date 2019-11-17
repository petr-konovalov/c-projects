#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define sqr(x) (x) * (x)
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase
#define X first
#define Y second

typedef long long ll;
typedef double db;
typedef float fl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 3e5 + 3;

vector<pii> g[N];
pll dp[N][2];

void calc1(int v, int edge = -1)
{
    if (edge == -1)
    {
        for (pii to: g[v])
            calc1(to.X, to.Y);
    }
    else
    {
        dp[edge][0].X = 1;
        dp[edge][0].Y = 1;
        for (pii to: g[v])
            if (to.Y != edge)
            {
                calc1(to.X, to.Y);
                dp[edge][0].X += dp[to.Y][0].X + dp[to.Y][0].Y;
                dp[edge][0].Y += dp[to.Y][0].Y;
            }
    }
}

void calc2(int v, int edge = -1)
{
    ll sumX = 0;
    ll sumY = 0;
    for (pii to: g[v])
        if (to.Y != edge)
        {
            sumX += dp[to.Y][0].X + dp[to.Y][0].Y;
            sumY += dp[to.Y][0].Y;
        }
    if (edge != -1)
    {
        sumX += dp[edge][1].X + dp[edge][1].Y;
        sumY += dp[edge][1].Y;
    }
    for (pii to: g[v])
        if (to.Y != edge)
        {
            dp[to.Y][1].X = 1 + sumX - dp[to.Y][0].X - dp[to.Y][0].Y;
            dp[to.Y][1].Y = 1 + sumY - dp[to.Y][0].Y;
            calc2(to.X, to.Y);
        }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        g[a].pb(mp(b, i));
        g[b].pb(mp(a, i));
    }
    calc1(1);
    calc2(1);
    for (int i = 1; i < n; ++i)
        cout << dp[i][0].X * dp[i][1].Y + dp[i][0].Y * (dp[i][1].X - dp[i][1].Y) << '\n';

    return 0;
}
