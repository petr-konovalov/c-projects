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
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 2e5 + 7;

int n, m, k;
vector<pii> g[N];
vector<pii> z;
set<pii> takedNode;
bool takedEdge[N];
int deg[N];
int ans[N];

void dec(int v)
{
    takedNode.erase(mp(deg[v], v));
    --deg[v];
    takedNode.insert(mp(deg[v], v));
}

void normalizeSet()
{
    while (!takedNode.empty() && takedNode.begin()->X < k)
    {
        int v = takedNode.begin()->Y;
        takedNode.erase(takedNode.begin());
        for (pii to: g[v])
            if (takedEdge[to.Y])
            {
                dec(to.X);
                takedEdge[to.Y] = false;
            }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m >> k;
    forn (i, m)
    {
        int x, y;
        cin >> x >> y;
        z.pb(mp(x, y));
        g[x].pb(mp(y, i));
        g[y].pb(mp(x, i));
        ++deg[x];
        ++deg[y];
        takedEdge[i] = true;
    }

    for (int v = 1; v <= n; ++v)
        takedNode.insert(mp(deg[v], v));
    normalizeSet();

    for (int i = m - 1; i >= 0; --i)
    {
        ans[i] = takedNode.size();
        if (takedEdge[i])
        {
            dec(z[i].X);
            dec(z[i].Y);
            takedEdge[i] = false;
            normalizeSet();
        }
    }

    for (int i = 0; i < m; ++i)
        cout << ans[i] << '\n';

    return 0;
}
