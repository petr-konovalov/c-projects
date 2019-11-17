#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define pb push_back

const int N = 100010;
const int INF = 1000000000;

typedef long long ll;

vector<int> g[N];
vector<int> ord;
int d[N];
int first[N];

int sp[20][2 * N];
int lg[2 * N];

void dfs(int v)
{
    first[v] = ord.size();
    ord.pb(v);
    for (int to: g[v])
    {
        d[to] = d[v] + 1;
        dfs(to);
        ord.pb(v);
    }
}

int getMin(int a, int b)
{
    if (a > b)
        swap(a, b);
    int k = lg[b - a + 1];
    int ans = sp[k][b - (1 << k) + 1];
    if (d[ans] > d[sp[k][a]])
        ans = sp[k][a];
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(false);
    cout.tie(false);
    lg[1] = 0;
    for (int i = 2, e = 2 * N; i < e; ++i)
        lg[i] = lg[i >> 1] + 1;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; ++i)
    {
        int p;
        cin >> p;
        g[p].pb(i);
    }
    dfs(0);
    forn (i, ord.size())
        sp[0][i] = ord[i];
    for (int i = 1; i <= lg[ord.size()]; ++i)
        for (int j = 0, f; (f = j + (1 << (i - 1))) < ord.size(); ++j)
        {
            sp[i][j] = sp[i - 1][f];
            if (d[sp[i][j]] > d[sp[i - 1][j]])
                sp[i][j] = sp[i - 1][j];
        }
    int a, b, x, y, z;
    cin >> a >> b >> x >> y >> z;
    ll res = 0;
    int v = 0;
    forn (i, m)
    {
        v = getMin(first[(a + v) % n], first[b]);
        res += v;
        a = ((ll)x * a + (ll)y * b + z) % n;
        b = ((ll)x * b + (ll)y * a + z) % n;
    }
    cout << res;
    return 0;
}
