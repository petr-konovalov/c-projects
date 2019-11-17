#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define sz(x) x.size()
#define all(x) x.begin(), x.end()
#define sqr(x) ((x)*(x))

typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;
typedef pair<ld, ld> pnt;

const int N = 1e5 + 7;
const ld mAns = 1e16;
const ld LF = -1e7, RG = 1e7;
const ld eps = 1e-6;

int n;
pnt anim[N];

int f(ld R, ld x)
{
    int res = 0;
    forn (i, n)
        if (sqr(anim[i].X - x) + sqr(anim[i].Y - R) <= R * R)
            ++res;
    return res;
}

int cntLFPnt(ld R, ld x)
{
    int res = 0;
    forn (i, n)
        if (sqr(anim[i].X - x) + sqr(anim[i].Y - R) > R * R && anim[i].X < x)
            ++res;
    return res;
}

int getMaxPnt(ld R)
{
    ld l = LF, r = RG;
    while (r - l > eps)
    {
        ld m = (l + r) / 2;
        if (cntLFPnt(R, m) == 0)
            l = m;
        else
            r = m;
    }
    return f(R, l);
}

ld findAns()
{
    ld l = 0, r = mAns;
    while (r - l > eps)
    {
        ld m = (r + l) / 2;
        if (getMaxPnt(m) == n)
            r = m;
        else
            l = m;
    }
    return l;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    bool pol = false;
    bool otr = false;
    forn (i, n)
    {
        cin >> anim[i].X >> anim[i].Y;
        pol = pol || anim[i].Y > 0;
        otr = otr || anim[i].Y < 0;
    }

    if (pol && otr)
    {
        cout << -1;
        return 0;
    }

    if (otr)
        forn (i, n)
            anim[i].Y *= -1;

    cout << findAns();

    return 0;
}
