#include <bits/stdc++.h>

using namespace std;

#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define forn(i, n) for(int i = 0; i < n; ++i)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define sqr(x) ((x) * (x))
#define sz(x) x.size()
#define all(x) x.begin(), x.end()

typedef unsigned long long ull;
typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<db, db> pdd;
typedef pair<ll, ll> pll;

const int INF = 1e9 + 7, N = 5e2 + 7, alf = 26;;

ull s, x;

int bitcnt(ull arg)
{
    int res = 0;
    while (arg)
    {
        res += arg & 1;
        arg >>= 1;
    }

    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> s >> x;
    ull q = (s - x) >> 1;
    if (s < x || (s - x) % 2 != 0 || (q & ~x) != q)
    {
        cout << 0;
    }
    else
    {
        cout << (1ll << bitcnt(x)) - (x == s) * 2;
    }

    return 0;
}
