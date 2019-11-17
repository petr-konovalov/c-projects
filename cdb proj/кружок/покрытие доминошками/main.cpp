#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)

typedef long long ll;

int w, h;
ll dp[101][11][1024];

void printMask(int sz, int mask)
{
    for (int i = 0; i < sz; ++i, mask >>= 1)
        debug("%i", mask & 1);
}

void calcZero(int sz, int pos = 0, int mask = 0)
{
    //printMask(sz, mask);
    dp[0][sz][mask] = 1;
    for (int d = pos + 2; d <= sz; ++d)
    {
        int nmask = mask + (3 << (d - 2));
        calcZero(sz, d, nmask);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> w >> h;
    if (h > w)
        swap(h, w);

    dp[0][h][0] = 1;

    for (int y = 1; y <= w; ++y)
    {
        for (int mask = 0, s = 1 << h; mask < s; ++mask)
        {
            dp[y][0][mask] = dp[y - 1][h][mask];
            if ((mask & 1) == 0)
                dp[y][1][mask + 1] = dp[y][0][mask];
            else
                dp[y][1][mask - 1] = dp[y][0][mask];
        }
        for (int x = 2; x <= h; ++x)
        {
            for (int mask = 0, s = 1 << h; mask < s; ++mask)
            {
                dp[y][x][mask ^ (1 << (x - 1))] += dp[y][x - 1][mask];
                if ((mask & (1 << (x - 1))) == 0 && (mask & (1 << (x - 2))) == 0)
                {
                    dp[y][x][mask] += dp[y][x - 2][mask];
                }
            }
        }
    }

    cout << dp[w][h][0];

    return 0;
}
