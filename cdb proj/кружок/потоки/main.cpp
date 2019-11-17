#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define X first
#define Y second
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase

typedef long long ll;
typedef double db;
typedef float fl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 53, INF = 1e9 + 7;

struct edge
{
    int flow, capacity, to;
    edge(int capacity, int to): capacity(capacity), to(to){flow = 0;};
};

int n, m;

vector<edge> edges;
vector<int> graph[N * N];
int used[N * N];
int timer = 0;
char inp[N][N];
int sink = N * N - 1;
int num[256];

int findPath(int v = 0, int minCap = INF)
{
    used[v] = timer;
    if (v == sink && minCap != INF)
        return minCap;
    for (int eid: graph[v])
    {
        if (used[edges[eid].to] != timer && edges[eid].capacity - edges[eid].flow > 0)
        {
            int res = findPath(edges[eid].to, min(minCap, edges[eid].capacity - edges[eid].flow));
            if (res)
            {
                edges[eid].flow += res;
                edges[eid ^ 1].flow -= res;
                return res;
            }
        }
    }

    return 0;
}

void fail()
{
    cout << "Invalid";
    exit(0);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    forn (i, n)
        cin >> inp[i];

    num['H'] = 1;
    num['O'] = 2;
    num['N'] = 3;
    num['C'] = 4;
    int outFlow = 0;
    int inFlow = 0;

    forn (x, n)
        forn (y, m)
        {
            int node = x * N + y + 1;

            if (!((x ^ y) & 1))
            {
                graph[0].pb(edges.size());
                edges.pb(edge(num[inp[x][y]], node));
                graph[node].pb(edges.size());
                edges.pb(edge(0, 0));
                outFlow += num[inp[x][y]];
            }
            else
            {
                graph[node].pb(edges.size());
                edges.pb(edge(num[inp[x][y]], sink));
                graph[sink].pb(edges.size());
                edges.pb(edge(0, node));
                inFlow += num[inp[x][y]];
            }

            graph[node].pb(edges.size());
            edges.pb(edge(1, node + 1));
            graph[node + 1].pb(edges.size());
            edges.pb(edge(1, node));

            graph[node].pb(edges.size());
            edges.pb(edge(1, node + N));
            graph[node + N].pb(edges.size());
            edges.pb(edge(1, node));
        }

    if (outFlow != inFlow || outFlow == 0)
        fail();

    do {
        ++timer;
    } while (findPath());

    for (int eid: graph[0])
        if (edges[eid].flow != edges[eid].capacity)
            fail();
    cout << "Valid";
    return 0;
}
