#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define A first
#define B second

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll INF = 2000000000000000;
const int N = 200000;

int n;
vector<pii > g[N];

int used[N];
pair<int, int> p[N];

int getCycle(int v = 0, int parent = -1)
{
    used[v] = 1;
    for (pii to: g[v])
    {
        if (to.A == parent)
            continue;
        p[to.A] = mp(v, to.B);
        if (used[to.A] == 1)
            return to.A;
        else if (used[to.A] != 2)
        {
            int res = getCycle(to.A, v);
            if (res != -1)
                return res;
        }
    }
    used[v] = 2;
    return -1;
}

ll depth[N];
ll maxWay = 0;

void calcDepth(int v)
{
    used[v] = 1;
    for (pii to: g[v])
        if (!used[to.A])
        {
            calcDepth(to.A);
            ll curd = depth[to.A] + to.B;
            if (curd > depth[v])
            {
                maxWay = max(maxWay, curd + depth[v]);
                depth[v] = curd;
            }
        }
}

int main()
{
    scanf("%i", &n);
    forn (i, n)
    {
        int l, r, c;
        scanf("%i %i %i", &l, &r, &c);
        --l;
        --r;
        g[l].pb(mp(r, c));
        g[r].pb(mp(l, c));
    }
    int v = getCycle();
    for (int &item: used)
        item = 0;
    ll cycleLen = 0;
    for (int c = v; used[c] = 1, cycleLen += p[c].B, p[c].A != v; c = p[c].A);
    for (int c = v; calcDepth(c), p[c].A != v; c = p[c].A);
    forn (i, n)
        printf("%i ", depth[i]);
    printf("\n");
    printf("%i", cycleLen);
    return 0;
}

