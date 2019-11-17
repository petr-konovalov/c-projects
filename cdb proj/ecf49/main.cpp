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
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e6 + 7, INF = 1e9 + 7;
const ll INF64 = (ll)1e18 + 3;

int n, t;
int a[N];
int c[N];
int timer;
int used[N];
int ans = 0;

void dfs(int v)
{
    //debug("%i\n", v);
    used[v] = timer;
    if (used[a[v]] == timer)
    {
        int cur = c[v];
        int node = a[v];
        while (node != v)
        {
            if (c[node] < cur)
                cur = c[node];
            node = a[node];
        }
        ans += cur;
    }
    else if (used[a[v]] == 0)
        dfs(a[v]);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    forn (i, n)
        cin >> c[i + 1];
    forn (i, n)
        cin >> a[i + 1];

    for (int i = 1; i <= n; ++i)
        if (used[i] == 0)
        {
            ++timer;
            //debug("------%i\n", timer);
            dfs(i);
        }
    cout << ans;
    return 0;
}
