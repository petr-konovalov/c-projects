#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define X first
#define Y second

typedef unsigned int uii;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<db, db> pdd;
typedef pair<ll, ll> pll;

int m, a;
int fn_1 = 1, fn = 1;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> m >> a;
    if (a == 1)
    {
        cout << 1 << '\n';
        return 0;
    }
    for (int d = 3; d < 100000000; ++d)
    {
        fn   = fn_1 + fn;
        fn_1 = fn - fn_1;
        fn   %= m;
        fn_1 %= m;
        if (fn == a)
        {
            cout << d;
            return 0;
        }
    }
    cout << -1;

    return 0;
}
