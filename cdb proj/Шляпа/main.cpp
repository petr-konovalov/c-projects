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
typedef pair<db, db> pdd;
typedef pair<ll, ll> pll;

int n;

int getF(int arg)
{
    int a, b;
    cout << "? " << arg << '\n';
    fflush(stdout);
    cin >> a;
    cout << "? " << (arg - 1 + (n >> 1)) % n + 1 << '\n';
    fflush(stdout);
    cin >> b;
    return a - b;
}

int sign(int arg)
{
    return arg == 0 ? 0: arg < 0 ? -1: 1;
}

int findAns()
{
    int l = 1, r = (n >> 1) + 1;
    int lval = getF(l);
    if (lval % 2 != 0)
        return -1;
    if (lval == 0)
        return l;
    while (r - l > 1)
    {
        int m = (l + r) >> 1;
        int val = getF(m);
        if (val == 0)
            return m;
        if (sign(lval) == sign(val))
        {
            l = m;
            lval = val;
        }
        else
            r = m;
    }
    return -1;
}

int main()
{
    /*
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    */

    cin >> n;
    cout << "! " << findAns();
    fflush(stdout);

    return 0;
}
