#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define L first
#define R second
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase

typedef long long ll;
typedef long double ld;
typedef double db;
typedef float fl;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 2e5 + 3, P = 1e9 + 7, M = 5e6 + 3;
const ll INF64 = 1e18 + 3;

int n;
vector<int> primes;
bool comp[M + 10];
bool used[M + 10];

bool fact(int n)
{
    bool res = false;
    for (int i = 0; (ll)primes[i] * primes[i] <= n; ++i)
        if (n % primes[i] == 0)
        {
            if (used[primes[i]])
                res = true;
            used[primes[i]] = true;
            while (n % primes[i] == 0)
                n /= primes[i];
        }
    if (n != 1)
    {
        if (used[n])
            res = true;
        used[n] = true;
    }

    return res;
}

bool fact2(int n)
{
    bool res = false;
    for (int i = 0; (ll)primes[i] * primes[i] <= n; ++i)
        if (n % primes[i] == 0)
        {
            if (used[primes[i]])
                res = true;
            while (n % primes[i] == 0)
                n /= primes[i];
        }
    if (n != 1)
    {
        if (used[n])
            res = true;
    }

    return res;
}

int arr[N];

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int i = 2; i <= M; ++i)
        if (!comp[i])
        {
            primes.pb(i);
            if ((ll)i * i <= M)
                for (int j = i * i; j <= M; j += i)
                    comp[j] = true;
        }
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    for (int i = 0; i < n; ++i)
        if (fact(arr[i]))
        {
            int j = arr[i] + 1;
            while (fact2(j))
                ++j;
            fact(j);
            cout << j << ' ';
            j = 0;
            for (int k = i + 1; k < n; ++k)
            {
                while (used[primes[j]])
                    ++j;
                cout << primes[j] << ' ';
                ++j;
            }
            return 0;
        }
        else
            cout << arr[i] << ' ';

    return 0;
}
