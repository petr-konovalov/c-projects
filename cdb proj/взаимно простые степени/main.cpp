#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define X first
#define Y second

typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int, int> pii;
typedef pair<db, db> pdd;
typedef pair<ll, ll> pll;

const int N = 1e5 + 7;

int pr[19] =
           {2, 3, 5, 7, 11,
            13, 17, 19, 23, 29,
            31, 37, 41, 43, 47,
            53, 59, 61, 67};

ll c[65];
ll n;
ll cnt;
set<ll> degs;

ll simpleAlg(ll n)
{
    for (int i = 2; (ll)i * i <= n; ++i)
    {
        ll cur = (ll)i * i;
        for (; cur <= n; cur *= i)
        {
            degs.insert(cur);
        }
    }

    return n - degs.size() - 1;
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int nok(int a, int b)
{
    return (ll)a * b / gcd(a, b);
}

void solve()
{
    cin >> n;
    cnt = 0;
    for (int i = 2; i < 60; ++i)
    {
        c[i] = (ll)(pow((ld)n, (ld)1 / i)) - 1;
        if (pow(c[i] + 1, i - 1) > n / (c[i] + 1))
            --c[i];
        else if (pow(c[i] + 2, i - 1) <= n / (c[i] + 2))
            ++c[i];
    }

    for (int i = 0; i < 18; ++i)
    {
        cnt += c[pr[i]];
        for (int j = i + 1; pr[i] * pr[j] < 60; ++j)
        {
            cnt -= c[pr[i] * pr[j]];
            for (int k = j + 1; pr[i] * pr[j] * pr[k] < 60; ++k)
                cnt += c[pr[i] * pr[j] * pr[k]];
        }
    }

    cout << n - 1 - cnt << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
