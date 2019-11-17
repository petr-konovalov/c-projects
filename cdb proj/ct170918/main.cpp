#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define sqr(x) ((x) * (x))
#define all(x) x.begin(), x.end()
#define sz(x) x.size()

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

bool isEqual(double a, double b)
{
    const double eps = 1e-9;
    return abs(a - b) < eps;
}

bool isLess(double a, double b)
{
    return a < b && !isEqual(a, b);
}

bool isLessOrEqual(double a, double b)
{
    return a < b || isEqual(a, b);
}

bool isGreater(double a, double b)
{
    return a > b && !isEqual(a, b);
}

bool isLessOrGreater(double a, double b)
{
    return a > b || isEqual(a, b);
}

double mySqrt(double a)
{
    if (isLess(a, 0))
    {
        throw "sqrt(-1)";
    }
    if (a < 0)
        return 0;
    return sqrt(a);
}

struct Point
{
    double x;
    double y;

    Point(): x(0), y(0){};

    Point(double x, double y): x(x), y(y){};

    Point operator+(const Point &a) const
    {
        return Point(x + a.x, y + a.y);
    }

    Point operator-(const Point &a) const
    {
        return Point(x - a.x, y - a.y);
    }

    Point operator*(double k) const
    {
        return Point(x * k, y * k);
    }

    Point operator/(double k) const
    {
        return Point(x / k, y / k);
    }

    Point operator-() const
    {
        return Point(-x, -y);
    }

    double operator%(const Point &a) const
    {
        return x * a.x + y * a.y;
    }

    double operator*(const Point &a) const
    {
        return x * a.y - y * a.x;
    }

    bool operator==(const Point &a) const
    {
        return isEqual(x, a.x) && isEqual(y, a.y);
    }

    double operator!=(const Point &a)
    {
        return !isEqual(x, a.x) || !isEqual(y, a.y);
    }

    double length()
    {
        return mySqrt(*this % *this);
    }

    Point normalize(double k = 1)
    {
        double d = this->length();
        if (isEqual(d, 0))
        {
            if (isEqual(k, 0))
                return Point();
            throw "zero-size vector";
        }
        return *this * k / d;
    }

    Point rotate()
    {
        return Point(-y, x);
    }

    double distTo(const Point &A, const Point &B)
    {
        double d = (B - A).length();
        if (isEqual(d, 0))
        {
            throw "A = B";
        }
        return abs((*this - B) * (*this - A)) / d;
    }
};

const int N = 8;

int n;
double V;
Point pos;

Point p[N];
double mv[N];
Point v[N];
double a[N];

double moveTo(int id)
{
    if (p[id] == pos)
        return 0;
    Point dest = p[id] - pos;
    Point normal = dest.rotate().normalize();
    double a = v[id] % normal;
    double b = mySqrt(V * V - a * a);
    double time = dest.length() / (b - dest.normalize() % v[id]);

    pos = pos + (dest.normalize(b) + normal * a) * time;

    return time;
}

void moveAll(double time)
{
    forn (i, n)
        p[i] = p[i] + v[i] * time;
}

void solve()
{
    cin >> V;
    forn (i, n)
        cin >> p[i].x >> p[i].y >> mv[i] >> a[i];

    forn (i, n)
    {
        v[i].x = mv[i] * cos(a[i]);
        v[i].y = mv[i] * sin(a[i]);
    }

    int ord[N];
    forn (i, n)
        ord[i] = i;

    double ans = 1e10;

    Point pp[N];
    forn (i, n)
        pp[i] = p[i];

    do
    {
        forn (i, n)
            p[i] = pp[i];
        pos = Point();

        double curAns = 0;
        double time = 0;
        forn (i, n)
        {
            double t = moveTo(ord[i]);
            time += t;
            curAns = max(curAns, time + pos.length() / mv[ord[i]]);
            moveAll(t);
        }
        ans = min(ans, curAns);
    } while(next_permutation(ord, ord + n));
    cout << (ll)(ans + 0.5) << '\n';
}

int main()
{
    freopen("tourguide.in", "r", stdin);
    freopen("tourguide.out", "w", stdout);

    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    while (n)
    {
        solve();
        cin >> n;
    }

    return 0;
}
