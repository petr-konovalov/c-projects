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
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 3e5 + 7, A = 15000000 + 100, INF = 1e9 + 7;

int n;
int ans = 0;
int a[N];
map<int, int> cnt;
int md[A];
vector<int> pr;

void sieve()
{
    for (int i = 1; i < A; ++i)
        md[i] = i;
    pr.reserve(907709);
    for (int i = 2; i < A; ++i)
    {
        if (md[i] == i)
            pr.pb(md[i]);

        for (int j = 0; j < pr.size() && i * pr[j] < A && pr[j] <= md[i]; ++j)
            md[i * pr[j]] = pr[j];
    }
}

void fact(int n)
{
    while (n != md[n])
    {
        int d = md[n];
        ++cnt[d];
        while (n % d == 0)
            n /= d;
    }
    if (n > 1)
    {
        ++cnt[n];
    }
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    sieve();
    cin >> n;
    ans = n;

    int d = 0;
    forn (i, n)
    {
        cin >> a[i];
        d = gcd(a[i], d);
    }

    forn (i, n)
        a[i] /= d;

    forn (i, n)
        fact(a[i]);

    for (pii k: cnt)
    {
        ans = min(n - k.Y, ans);
    }

    if (ans == n)
        cout << -1;
    else
        cout << ans;

    return 0;
}
