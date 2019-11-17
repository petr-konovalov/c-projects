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
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e5 + 3, INF = 1e9 + 7, M1 = 1e9 + 7, M2 = 1e9 + 9;
const ll INF64 = (ll)1e18 + 3;
const ll seed = 98723421;

struct IPoint
{
    int x;
    int y;

    IPoint(int x, int y): x(x), y(y){};
    IPoint()
    {
        x = y = 0;
    }
};

ostream& operator<< (ostream& os, const IPoint &p)
{
    os << p.x << ' ' << p.y;
    return os;
}

istream& operator>> (istream& os, IPoint &p)
{
    os >> p.x >> p.y;
    return os;
}

IPoint operator- (IPoint a, IPoint b)
{
    return IPoint(a.x - b.x, a.y - b.y);
}

IPoint operator+ (IPoint a, IPoint b)
{
    return IPoint(a.x + b.x, a.y + b.y);
}

ll operator% (IPoint a, IPoint b)
{
    return (ll)a.x * b.x + (ll)a.y * b.y;
}

ll operator* (IPoint a, IPoint b)
{
    return (ll)a.x * b.y - (ll)a.y * b.x;
}

bool operator< (IPoint a, IPoint b)
{
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

typedef vector<IPoint> IPoints;

void add(IPoints &pnt, IPoint p, bool isUp = true)
{
    if (isUp)
    {
        while (pnt.size() > 1 && ((p - pnt[pnt.size() - 1]) * (pnt[pnt.size() - 2] - pnt[pnt.size() - 1])) >= 0)
            pnt.pop_back();
        pnt.pb(p);
    }
    else
    {
        while (pnt.size() > 1 && ((p - pnt[pnt.size() - 1]) * (pnt[pnt.size() - 2] - pnt[pnt.size() - 1])) <= 0)
            pnt.pop_back();
        pnt.pb(p);
    }
}

IPoints getConvex(IPoints &s)
{
    IPoints up;
    IPoints down;

    sort(s.begin(), s.end());
    IPoint v = s.back() - s.front();

    up.pb(s.front());
    for (IPoint p: s)
    {
        if ((v * (p - s.front())) > 0)
        {
            add(up, p);
        }
        else
        {
            add(down, p, false);
        }
    }
    add(up, s.back());

    for (int i = up.size() - 2; i > 0; --i)
        down.pb(up[i]);

    return down;
}

int getNextId(int id, int sz)
{
    if (id + 1 == sz)
        return 0;
    else
        return id + 1;
}

int getPrevId(int id, int sz)
{
    if (id == 0)
        return sz - 1;
    else
        return id - 1;
}

vector<pll> pointsToPlls(IPoints pnt)
{
    vector<pll> res(pnt.size());

    for (int i = 0; i < pnt.size(); ++i)
    {
        IPoint cur = pnt[i], nx = pnt[getNextId(i, pnt.size())], pr = pnt[getPrevId(i, pnt.size())];
        IPoint vv = nx - cur;
        res[i] = mp(vv % vv, vv % (pr - cur));
    }

    return res;
}

mt19937 gen(seed);
int n, m;
IPoints p1, p2;
map<pll, int> num;
int numc = 0;
vector<pll> c1, c2;
vector<pii> h1, h2;
vector<int> s1, s2;
vector<int> sufArr;
int q1[N], q2[N];

void makeNum(vector<pll> s)
{
    for (pll cur: s)
    {
        if (num.find(cur) == num.end())
            num[cur] = numc++;
    }
}

void makeStr()
{
    int sz = c1.size();
    s1.resize(sz << 1);
    s2.resize(sz);
    for (int i = 0; i < sz; ++i)
    {
        s1[i] = num[c1[i]];
        s2[i] = num[c2[i]];
        s1[i + sz] = num[c1[i]];
    }
}

void makeNum()
{
    makeNum(c1 = pointsToPlls(getConvex(p1)));
    makeNum(c2 = pointsToPlls(getConvex(p2)));
    if (c1.size() != c2.size())
    {
        cout << "NO";
        exit(0);
    }
}

void readInp()
{
    cin >> n >> m;
    p1.resize(n);
    p2.resize(m);
    forn (i, n)
        cin >> p1[i];
    forn (i, m)
        cin >> p2[i];
}

void makeHash(vector<pii> &h, const vector<int> &s)
{
    h[0] = mp(0, 0);
    for (int i = 0; i < s.size(); ++i)
    {
        int c = s[i] + 1;
        h[i + 1] = mp(((ll)h[i].X * q1[1] + c) % M1, ((ll)h[i].Y * q2[1] + c) % M2);
    }
}

void makeHash()
{
    const int qRange = 10000;
    const int qMin = N;
    q1[0] = 1;
    q2[0] = 1;
    q1[1] = gen() % qRange + qMin;
    q2[1] = gen() % qRange + qMin;
    for (int i = 2; i < N; ++i)
    {
        q1[i] = ((ll)q1[i - 1] * q1[1]) % M1;
        q2[i] = ((ll)q2[i - 1] * q2[1]) % M2;
    }
    h1.resize(2 * c1.size() + 1);
    h2.resize(c2.size() + 1);

    makeHash(h1, s1);
    makeHash(h2, s2);
}

bool modEqual(ll a, ll b, int mod)
{
    return (a - b) % mod == 0;
}

bool hashEqual(pll h1, pll h2)
{
    return modEqual(h1.X, h2.X, M1) && modEqual(h1.Y, h2.Y, M2);
}

pll getHash(const vector<pii> &h, int l, int r)
{
    return mp(h[r].X - (ll)h[l].X * q1[r - l], h[r].Y - (ll)h[l].Y * q2[r - l]);
}

int comp(const vector<pii> &h1, const vector<int> &s1,
         const vector<pii> &h2, const vector<int> &s2,
         int f, int s, int len)
{
    int l = 0, r = len;

    while (r - l > 1)
    {
        int mid = (r + l) >> 1;
        if (hashEqual(getHash(h1, f, f + mid), getHash(h2, s, s + mid)))
            l = mid;
        else
            r = mid;
    }

    return s1[f + r - 1] - s2[s + r - 1];
}

bool compCycleStr(int a, int b)
{
    return comp(h1, s1, h1, s1, a, b, s2.size()) < 0;
}

void generateSufArr()
{
    sufArr.resize(s2.size());
    for (int i = 0; i < sufArr.size(); ++i)
        sufArr[i] = i;
    sort(sufArr.begin(), sufArr.end(), compCycleStr);
}

int findStr()
{
    int l = 0, r = s2.size();

    while (r - l > 1)
    {
        int mid = (r + l) >> 1;
        if (comp(h1, s1, h2, s2, sufArr[mid], 0, s2.size()) <= 0)
            l = mid;
        else
            r = mid;
    }

    return sufArr[l];
}

void checkRes(int res)
{
    if (hashEqual(getHash(h1, res, res + s2.size()), getHash(h2, 0, s2.size())))
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    readInp();
    makeNum();
    makeStr();
    makeHash();
    generateSufArr();
    checkRes(findStr());

    return 0;
}
