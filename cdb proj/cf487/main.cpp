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

const int N = 50 + 7;

int a, b, c, d;
char ans[N][N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    forn (x, N)
        forn (y, N)
            ans[x][y] = '.';

    cin >> a >> b >> c >> d;

    --a;
    --b;
    --c;
    --d;
    for (int x = 0; x < 24; x += 2)
    {
        for (int y = 0; y < 24; y += 2)
        {
            if (d-- > 0)
                ans[x][y] = 'D';
            if (a-- > 0)
                ans[x + 26][y] = 'A';
            if (c-- > 0)
                ans[x][y + 26] = 'C';
            if (b-- > 0)
                ans[x + 26][y + 26] = 'B';
        }
    }

    for (int x = 0; x < 50; ++x)
    {
        for (int y = 0; y < 50; ++y)
        {
            if (ans[x][y] == '.')
            {
                if (x < 25 && y < 25)
                    ans[x][y] = 'A';
                else if (x >= 25 && y < 25)
                    ans[x][y] = 'B';
                else if (x >= 25 && y >= 25)
                    ans[x][y] = 'C';
                else
                    ans[x][y] = 'D';
            }
        }
    }

    cout << 50 << ' ' << 50 << '\n';
    for (int x = 0; x < 50; ++x)
    {
        for (int y = 0; y < 50; ++y)
            cout << ans[x][y];
        cout << '\n';
    }

    return 0;
}
