

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define sqr(x) (x) * (x)
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase
#define X first
#define Y second

typedef unsigned long long ll;
typedef long double ld;
typedef double db;
typedef float fl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

ll dec(ll a, ll b)
{
    if (a > b)
        return a - b;
    else
        return b - a;
}

ll mulMod(ll a, ll b, ll mod)
{
    ll res = a * b - (ll)((ld) a / mod * b) * mod;
    return (res + mod) % mod;
}

ll binPow(ll a, ll deg, ll mod)
{
    ll res = 1;
    while (deg)
    {
        if (deg & 1)
            res = mulMod(res, a, mod);
        a = mulMod(a, a, mod);
        deg >>= 1;
    }

    return res;
}

ll gcd(ll a, ll b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

ll a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

bool primeTest(ll n)
{
    ll q = n - 1;
    int s = 0;
    while((q & 1) == 0)
    {
        ++s;
        q >>= 1;
    }
    forn (i, 10)
    {
        if (a[i] == n)
            return true;
        if (binPow(a[i], n - 1, n) != 1)
            return false;
        ll t = binPow(a[i], q, n);
        if (t != 1)
            for(int i = 0; i < s && t != n - 1; t = mulMod(t, t, n), ++i)
                if (t == 1)
                    return false;
    }
    return true;
}

ll n;

ll f(ll x)
{
    return (mulMod(x, x, n) + 3) % n;
}

ll getDev(ll n)
{
    ll c, d;
    ll M = 1;
    ll iter[100];
    c = d = rand() % n;
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            c = f(c);
            d = f(f(d));
            M = mulMod(M, dec(c, d), n);
            iter[j] = M;
        }
        ll g = gcd(M, n);
        if (g == n)
        {
            for (int j = 0; j < 100; ++j)
            {
                g = gcd(iter[j], n);
                if (g == n)
                    return 0;
                if (g != 1)
                    return g;
            }
            return 0;
        }
        if (g != 1)
            return g;
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    srand(21982);
    cin >> n;
    if (primeTest(n))
    {
        cout << "IMPOSSIBLE\n";
    }
    else
    {
        for (int i = 2; i < 10000; ++i)
            if (n % i == 0)
            {
                cout << i << ' ' << n / i;
                return 0;
            }
        ll ans = getDev(n);
        while (ans == 0)
            ans = getDev(n);
        cout << ans << ' ' << n / ans;
    }

    return 0;
}
