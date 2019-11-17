#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back
#define mp make_pair
#define X first
#define Y second

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 2e5 + 7;

int n, m, q;
vector<pii> inp;
int ver[N];
int hor[N];

int parent[N];
int sz[N];

int compCnt = 0;
bool vused[N];
bool hused[N];
int cnt;

int findPath(int v)
{
    return v == parent[v] ? v: findPath(parent[v]);
}

void unionSet(int a, int b)
{
    a = findPath(a);
    b = findPath(b);
    if (a == b)
        return;

    if (sz[a] < sz[b])
        swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    --compCnt;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m >> q;
    compCnt = q;
    for (int i = 0; i < q; ++i)
    {
        parent[i] = i;
        sz[i] = 1;
    }

    inp.resize(q);
    forn (i, q)
    {
        cin >> inp[i].X >> inp[i].Y;
        if (vused[inp[i].X])
            unionSet(i, ver[inp[i].X]);
        else
        {
            ver[inp[i].X] = i;
            ++cnt;
        }
        if (hused[inp[i].Y])
            unionSet(i, hor[inp[i].Y]);
        else
        {
            hor[inp[i].Y] = i;
            ++cnt;
        }
        vused[inp[i].X] = true;
        hused[inp[i].Y] = true;
    }

    cout << m + n - 1 + compCnt - cnt;

    return 0;
}
