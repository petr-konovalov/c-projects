#include <iostream>
#include <cmath>

using namespace std;

void getOddEven(long long l, long long r, long long &odd, long long &even)
{
    long long d = r - l;
    if (d & 1)
        odd = even = ((d + 1) >> 1);
    else
    {
        long long k = (d >> 1);
        if (l & 1)
        {
            odd = k + 1;
            even = k;
        }
        else
        {
            odd = k;
            even = k + 1;
        }
    }
}

void getlr(double xl, double xr, long long y, long long &l, long long &r)
{
    l = max((long long)ceil(xl), -y);
    r = min((long long)floor(xr), y);
}

void normir(double &vx, double &vy)
{
    double len = sqrt(vx * vx + vy * vy);
    vx /= len;
    vy /= len;
}

double A, B, Cl, Cr;

long long getCount(double xl, double xr, long long y, double rad)
{
    long long odd, even, l, r, res = 0;
    getlr(xl, xr, y, l, r);
    if (l > r)
        return 0;
    getOddEven(l, r, odd, even);
    if (y & 1)
        res = odd;
    else
        res = even;
    return res;
}

int main()
{
    long long n, xc, yc;
    double r, q, vx, vy;
    cin >> r >> n >> q >> xc >> yc >> vx >> vy;
    double dx = vx / abs(vy);
    normir(vx, vy);
    A = vy;
    B = -vx;
    r /= 1000;
    q /= 1000;
    double t = vx * yc - vy * xc;
    Cl = t + q + r;
    Cr = t - q - r;
    double xl = -Cl / A, xr = -Cr / A;
    long long res = 0;
    for (long long y = 0; y < n; ++y, xl += dx, xr += dx)
        res += getCount(xl, xr, y, r);
    cout << res << endl;
    return 0;
}
