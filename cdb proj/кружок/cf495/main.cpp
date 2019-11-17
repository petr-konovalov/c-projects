#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e6 + 7, INF = 1e9 + 7;
const ll INF64 = 1e18;

int n, k, m;
int cnt[N];
int a, b, c, d;
int ncnt[N];

void check(int a, int b, int c, int d)
{
    if (a < 0 || b < 0 || c < 0 || d < 0)
        return;

    for (int i = 0; i < N; ++i)
        ncnt[i] = 0;

    for (int x = 0; x < a + c + 1; ++x)
        for (int y = 0; y < b + d + 1; ++y)
            ++ncnt[abs(x - a) + abs(y - b)];

    for (int i = 0; i < N; ++i)
        if (cnt[i] != ncnt[i])
            return;

    cout << a + c + 1 << ' ' << b + d + 1 << '\n' << a + 1 << ' ' << b + 1 << '\n';
    exit(0);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    forn (i, n)
    {
        int item;
        cin >> item;
        ++cnt[item];
        m = max(m, item);
    }

    for (int k = 1; k <= m; ++k)
    {
        if (cnt[k] < 4 * k)
        {
            a = k - 1;
            break;
        }
    }

    for (int k = a + 1; k <= m; ++k)
    {
        int h = k - a;
        if (cnt[k] < 4 * k - 2 * h + 1)
        {
            b = k - 1;
            break;
        }
    }

    if (n % (a + b + 1) == 0)
        check(a, m - b, b, n / (a + b + 1) - 1 - m + b);

    for (int n1 = 1; n1 <= n; ++n1)
    {
        if (n % n1 == 0)
            check(a, b, n1 - a - 1, n / n1 - b - 1);
    }

    cout << -1;
    return 0;
}
