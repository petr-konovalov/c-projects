#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)

typedef long long ll;

const int N = 1e5 + 3, P = 1e9 + 7;

int n;
vector<int> g[N];
int a[N];
int b[N];
int c[N];
int d[N];

int read()
{
    int val;
    cin >> val;
    return val;
}

int binPow(int a, int deg)
{
    int res = 1;
    while (deg)
    {
        if (deg & 1)
            res = ((ll)res * a) % P;
        a = ((ll)a * a) % P;
        deg >>= 1;
    }

    return res;
}

void calc(int v = 1, int parent = -1)
{
    b[v] = 1;
    for (int to: g[v])
        if (to != parent)
        {
            calc(to, v);
            b[v] = ((ll)b[v] * (b[to] + 1)) % P;
        }
    c[v] = b[v];
    for (int to: g[v])
        if (to != parent)
            c[v] = (c[v] + (((ll)b[v] * binPow(b[to] + 1, P - 2)) % P * c[to]) % P) % P;
    a[v] = b[v];
    d[v] = c[v];
    for (int to: g[v])
        if (to != parent)
        {
            a[v] = (a[v] + a[to]) % P;
            d[v] = (d[v] + d[to]) % P;
        }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    forn(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    calc();
    cout << a[1] << ' ' << d[1];

    return 0;
}
