#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase
#define X first
#define Y second

typedef long long ll;
typedef double db;
typedef unsigned int ui;
typedef float fl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e5 + 3, P = 1e9 + 7;
const ll INF64 = 1e+18 + 3;

int divv(int a, int b)
{
    return a / b + (a % b != 0 ? 1 : 0);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int hh, mm;
    int h, d, n;
    double c;
    cin >> hh >> mm >> h >> d >> c >> n;

    int t = hh * 60 + mm;
    if (t < 1200)
        printf("%.6f", min(divv(h, n) * c, divv(h + (1200 - t) * d, n) * c * 0.8));
    else
        printf("%.6f", divv(h, n) * c * 0.8);

    return 0;
}
