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
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e5 + 7, M1 = 1e9 + 7, M2 = 1e9 + 9;

string str;
int n;
int a[N];
pii h[N];
pii q[N];

void buildHash()
{
    q[0] = mp(1, 1);
    //q[1].X = 100 + rand() % 10000;
    //q[1].Y = 100 + rand() % 10000;
    q[1].X = 100;
    q[1].Y = 100;

    for (int i = 2; i <= n; ++i)
        q[i] = mp(((ll)q[i - 1].X * q[1].X) % M1, ((ll)q[i - 1].Y * q[1].Y) % M2);

    for (int i = 1; i <= n; ++i)
        h[i] = mp(((ll)h[i - 1].X * q[1].X + str[i - 1]) % M1,((ll)h[i - 1].Y * q[1].Y + str[i - 1]) % M2);
}

pii getHash(int l, int r)
{
    return mp(((h[r].X - (ll)h[l - 1].X * q[r - l + 1].X) % M1 + M1) % M1,
              ((h[r].Y - (ll)h[l - 1].Y * q[r - l + 1].Y) % M2 + M2) % M2);
}

bool comp(int a, int b)
{
    int l = 0;
    int r = n - max(a, b) + 2;
    while (r - l > 1)
    {
        int m = (l + r) >> 1;
        if (getHash(a, a + m - 1) == getHash(b, b + m - 1))
            l = m;
        else
            r = m;
    }
    return str[a + r - 2] < str[b + r - 2];
}

void subPr(int l, int r)
{
    for (int i = l; i <= r; ++i)
        debug("%c", str[i]);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    srand(1823);
    getline(cin, str);
    n = str.size();
    str += '\0';
    buildHash();
    for (int i = 0; i < n; ++i)
        a[i] = i + 1;
    /*
    while (true)
    {
        int a, b;
        cin >> a >> b;
        debug(comp(a, b) ? "<\n": ">=\n");
    }
    */
    sort(a, a + n, comp);
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    return 0;
}
