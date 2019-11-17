#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define mp make_pair
#define pb push_back
#define ins insert
#define ers erase
#define F first
#define S second

typedef long long ll;
typedef double db;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<db, db> pdd;

const int INT_INF = 2e9;
const db eps = 10e-7;
const int N = 2000;

int n, r;
int x[N];
db y[N];

db getCoord(int x1, db y, int x2)
{
    db R = INT_INF;
    db L = y;
    db sqx = (db)(x1 - x2) * (x1 - x2);
    db dist = 0;
    db rr = 4 * r * r;
    while (abs(rr - dist) > eps)
    {
        db m = (L + R) / 2;
        db mdist = (y - m) * (y - m) + sqx;
        if (mdist > rr)
            R = m;
        else
        {
            L = m;
            dist = mdist;
        }
    }
    return L;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> r;
    forn (i, n)
    {
        cin >> x[i];
        y[i] = r;
        forn (j, i)
            if (abs(x[i] - x[j]) <= 2 * r)
                y[i] = max(y[i], getCoord(x[i], y[j], x[j]));
    }
    forn (i, n)
        printf("%.7f ", y[i]);
    return 0;
}
