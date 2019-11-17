#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define int long long

const int P = 1e9 + 9;

typedef long long ll;

int binPow(ll a, int deg)
{
    int res = 1;
    while (deg)
    {
        if (deg & 1)
            res = (a * res) % P;
        a = (a * a) % P;
        deg >>= 1;
    }
    return res;
}

int getAns(int p, ll k)
{
    int res = 1;
    for (int i = 2; i * i <= p; ++i)
        if (p % i == 0)
        {
            int s = 0;
            while (p % i == 0)
            {
                ++s;
                p /= i;
            }
            res = res * ((binPow(s + 1, k) + binPow(s - 1, k) - 2 * binPow(s, k)) % P + P) % P;
        }
    if (p != 1)
        res = ((ll)res * (binPow(2, k) - 2)) % P;
    return res;
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    ll k;
    int d, m;
    cin >> k >> d >> m;
    if (m % d != 0)
        cout << 0;
    else
        cout << getAns(m / d, k);
    return 0;
}
