#include <bits/stdc++.h>

#define F first
#define S second
#define mp make_pair
#define sqr(x) ((x) * (x))
#define pb push_back
#define forn(i, n) for(int i = 0; i < n; ++i)
#define ins insert
#define ers erase
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);

using namespace std;

typedef long long ll;
typedef float fl;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const ll N = 5e5 + 9, M = 2e3 + 11, INF = 1e9 + 7, INF64 = 1e18 + 7;

set<int> arr[N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    int r, ar, br;
    int s, as, bs;
    cin >> r >> ar >> br;
    cin >> s >> as >> bs;
    for (int i = 0; i < k; ++i)
    {
        arr[r].ins(s);
        r = ((ll)r * ar + br) % n;
        s = ((ll)s * as + bs) % m;
    }
    for (int i = 0; i < n; ++i)
        arr[i].ins(m);
    long long res = 0;
    for (int i = 0; i < n; ++i)
    {
        int f = -1;
        for (set<int>::iterator it = arr[i].begin(); it != arr[i].end(); ++it)
        {
            ll nn = *it - f;
            res += nn * (nn - 1) / 2;
            f = *it;
        }
    }
    cout << res;
    return 0;
}
