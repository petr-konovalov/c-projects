#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)

typedef long long ll;

int n;
ll ans;
bool defect[51][51];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int x = 0; x < 9; ++x)
        for (int y = 0; y < 50; ++y)
            for (int xx = 0; xx < 9; ++xx)
                for (int yy = 0; yy < 50; ++yy)
                {
                    int f = 4 * x + 9 * y, s = 4 * xx + 9 * yy;
                    if (s < f && (s - f) % 49 == 0)
                        defect[x][y] = true;
                }

    for (int x = 0; x < 9 && n >= x; ++x)
    {
        for (int y = 0; y < 49 && n >= x + y; ++y)
            if (!defect[x][y])
                ans += n - x - y + 1;
    }
    cout << ans;
    return 0;
}
