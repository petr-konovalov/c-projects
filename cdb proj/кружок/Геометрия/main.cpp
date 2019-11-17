

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define pb push_back
#define mp make_pair
#define sqr(x) (x) * (x)
#define X first
#define Y second
#define ins insert
#define ers erase

typedef long long ll;
typedef float fl;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 3e+2 + 5, INF = 1e9+7;

int read()
{
    int val;
    cin >> val;
    return val;
}

pdd operator-(pdd a, pdd b)
{
    return mp(a.X - b.X, a.Y - b.Y);
}

pdd operator+(pdd a, pdd b)
{
    return mp(a.X + b.X, a.Y + b.Y);
}

db operator*(pdd a, pdd b)
{
    return a.X * b.X + a.Y * b.Y;
}

db operator^(pdd a, pdd b)
{
    return a.X * b.Y - a.Y * b.X;
}

pdd operator*(double a, pdd b)
{
    return mp(a * b.X, a * b.Y);
}

pdd operator/(pdd a, double b)
{
    return mp(a.X / b, a.Y / b);
}

void solve()
{
    pdd a1, b1, c1;
    pdd a2, b2, c2;
    cin >> a1.X >> a1.Y >> b1.X >> b1.Y >> c1.X >> c1.Y;
    cin >> a2.X >> a2.Y >> b2.X >> b2.Y >> c2.X >> c2.Y;
    pdd A1 = a1 - b1, B1 = a1 - c1, C1 = b1 - c1;
    pdd A2 = a2 - b2, B2 = a2 - c2, C2 = b2 - c2;
    db dA1 = sqr(A1.X) + sqr(A1.Y);
    db dB1 = sqr(B1.X) + sqr(B1.Y);
    db dC1 = sqr(C1.X) + sqr(C1.Y);

    db dA2 = sqr(A2.X) + sqr(A2.Y);
    db dB2 = sqr(B2.X) + sqr(B2.Y);
    db dC2 = sqr(C2.X) + sqr(C2.Y);
    if (dA1 * dB2 == dB1 * dA2 &&
        dA1 * dC2 == dC1 * dA2 &&
        dC1 * dB2 == dB1 * dC2)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    freopen("similar.in", "r", stdin);
    freopen("similar.out", "w", stdout);

    int t;
    cin >> t;
    while(t--)
        solve();

    return 0;
}
