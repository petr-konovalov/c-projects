#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define sqr(x) ((x) * (x))
#define mp make_pair
#define pb push_back
#define F first
#define S second

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e5 + 7, INF = 1e9 + 7;
const ll INF64 = 1e18;

const ll seed = 7908235212;

mt19937 gen(seed);
int n;
int arr[N];
int ans = 0;
int g;
int mx;

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

    cin >> n;
    forn (i, n)
    {
        cin >> arr[i];
        mx = max(mx, arr[i]);
    }
    g = arr[0];
    for (int i = 1; i < n; ++i)
        g = gcd(g, arr[i]);
    cout << (((n - mx / g) & 1) ? "Alice": "Bob");

    return 0;
}
