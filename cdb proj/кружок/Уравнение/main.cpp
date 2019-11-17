#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase
#define X first
#define Y second

typedef long long ll;
typedef float fl;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1000000;

int n, m;
int zd[N];
int an[N];
int cn[N];

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int binPow(ll arg, int deg)
{
    ll res = 1;
    while (deg)
    {
        if (deg & 1)
            res = (res * arg) % m;
        arg = (arg * arg) % m;
        deg >>= 1;
    }
    return res;
}

ll get(int d)
{
    ll res = 0;
    for (int i = 1; i < m; ++i)
        res += cn[((an[d] - an[i]) % m + m) % m];
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    for (int i = 1; i < m; ++i)
    {
        ++zd[gcd(i, m)];
        an[i] = binPow(i, n);
        ++cn[an[i]];
    }

    ll res = 0;
    for (int i = 1; i < m; ++i)
    {
        if (zd[i] != 0)
            res += zd[i] * get(i);
    }
    ll p = 0;
    for (int i = 1; i < m; ++i)
        p += cn[(2 * an[i]) % m];
    cout << ((res - p) >> 1) + p;
    return 0;
}
