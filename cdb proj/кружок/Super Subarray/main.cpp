#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back
#define mp make_pair

typedef long long ll;

const int N = 2000 + 5;
const ll INF = 1e15 + 5;

ll arr[N];

ll gcd(ll a, ll b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

void solve()
{
    int n;
    cin >> n;
    forn (i, n)
        cin >> arr[i];

    ll res = 0;
    forn (i, n)
    {
        ll nok = 1;
        ll sum = 0;

        for (int j = i; j < n; ++j)
        {
            ll g = gcd(nok, arr[j]);

            sum += arr[j];
            if (nok / g < INF / arr[j])
                nok = nok / g * arr[j];
            else
                break;

            if (sum % nok == 0)
                ++res;
        }
    }

    cout << res << '\n';
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
