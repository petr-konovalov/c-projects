#include <iostream>
#include <cmath>

using namespace std;

const double eps = 10e-5;

struct Vect
{
    double x, y, z;
    Vect(){};
    Vect(double x, double y, double z): x(x), y(y), z(z){};
};

double det(double a, double b, double c, double d)
{
    return a * d - c * b;
}

double det3(double a[3][3])
{
    return (a[0][0] * a[1][1] * a[2][2] + a[1][0] * a[2][1] * a[0][2] + a[0][1] * a[1][2] * a[2][0]) -
           (a[2][0] * a[1][1] * a[0][2] + a[1][0] * a[0][1] * a[2][2] + a[0][0] * a[1][2] * a[2][1]);
}

double vLen(Vect v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vect operator* (Vect a, Vect b)
{
    return Vect(det(a.y, a.z, b.y, b.z), det(a.z, a.x, b.z, b.x), det(a.x, a.y, b.x, b.y));
}

Vect operator- (Vect a, Vect b)
{
    return Vect(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vect operator/ (Vect a, double b)
{
    return Vect(a.x / b, a.y / b, a.z / b);
}

bool operator== (Vect a, Vect b)
{
    return abs(a.x - b.x) < eps && abs(a.y - b.y) < eps && abs(a.z - b.z) < eps;
}

void moveCoord(Vect v1, Vect v2, Vect v3, Vect &v)
{
    double a[3][3], m1[3][3], m2[3][3], m3[3][3];
    a[0][0] = v1.x;
    a[0][1] = v2.x;
    a[0][2] = v3.x;
    a[1][0] = v1.y;
    a[1][1] = v2.y;
    a[1][2] = v3.y;
    a[2][0] = v1.z;
    a[2][1] = v2.z;
    a[2][2] = v3.z;
    double d = det3(a);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m1[i][j] = m2[i][j] = m3[i][j] = a[i][j];
    m1[0][0] = v.x;
    m1[1][0] = v.y;
    m1[2][0] = v.z;
    m2[0][1] = v.x;
    m2[1][1] = v.y;
    m2[2][1] = v.z;
    m3[0][2] = v.x;
    m3[1][2] = v.y;
    m3[2][2] = v.z;
    double d1 = det3(m1), d2 = det3(m2), d3 = det3(m3);
    v.x = d1 / d;
    v.y = d2 / d;
    v.z = d3 / d;
}

struct Vect2
{
    double x, y;
    Vect2(){};
    Vect2(double x, double y): x(x), y(y){};
};

Vect2 findPoint1(double x, double y, double r)
{
    double t = y * y + x * x;
    double D = sqrt(t - r * r);
    double a = (-r * x - y * D) / t;
    double b = (-r * y + x * D) / t;
    double len = D / sqrt(a * a + b * b);
    double vx = -b * len;
    double vy = a * len;
    double cx = x + vx;
    double cy = y + vy;
    if (abs(cx * cx + cy * cy - r * r) > eps)
    {
        cx = x - vx;
        cy = y - vy;
    }
    return Vect2(cx, cy);
}

Vect2 findPoint2(double x, double y, double r)
{
    double t = y * y + x * x;
    double D = sqrt(t - r * r);
    double a = (r * x - y * D) / t;
    double b = (r * y + x * D) / t;
    double len = D / sqrt(a * a + b * b);
    double vx = -b * len;
    double vy = a * len;
    double cx = x + vx;
    double cy = y + vy;
    if (abs(cx * cx + cy * cy - r * r) > eps)
    {
        cx = x - vx;
        cy = y - vy;
    }
    return Vect2(cx, cy);
}

Vect2 findPointA(double x, double y, double r, bool zn)
{
    Vect2 c = findPoint1(x, y, r);
    if ((c.y > -eps) == zn)
        return Vect2(c.x, c.y);
    c = findPoint2(x, y, r);
    return Vect2(c.x, c.y);
}

double findAng(double x, double y, double r, Vect2 E)
{
    Vect2 c1 = findPoint1(x, y, r);
    Vect2 c2 = findPoint2(x, y, r);
    double cos1 = (E.x * c1.x + E.y * c1.y) / sqrt((E.x * E.x + E.y * E.y) * (c1.x * c1.x + c1.y * c1.y));
    double cos2 = (E.x * c2.x + E.y * c2.y) / sqrt((E.x * E.x + E.y * E.y) * (c2.x * c2.x + c2.y * c2.y));
    double ang = min(acos(cos1), acos(cos2));
    return ang;
}

double oS(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double vx1 = x2 - x1;
    double vy1 = y2 - y1;
    double vx2 = x3 - x1;
    double vy2 = y3 - y1;
    return vx1 * vy2 - vx2 * vy1;
}

bool checkIntersect(double x1, double y1, double x2, double y2, double r)
{
    double nx = y1 - y2;
    double ny = x2 - x1;
    return oS(nx, ny, x1, y1, -nx, -ny) * oS(nx, ny, x2, y2, -nx, -ny) < 0;
}

int main()
{
    Vect A, B, C;
    double R;
    cin >> A.x >> A.y >> A.z;
    cin >> B.x >> B.y >> B.z;
    cin >> C.x >> C.y >> C.z;
    cin >> R;
    A = A - C;
    B = B - C;
    Vect v1, v2, v3;
    v1 = A;
    v2 = A * B;
    if (A == B || vLen(v2) >= R * vLen(A - B))
    {
        cout << vLen(A - B);
        return 0;
    }
    if (vLen(v2) < eps)
    {
        v2.x = -A.y;
        v2.y = A.x;
        v2.z = 0;
    }
    v3 = A * v2;
    v1 = v1 / vLen(v1);
    v2 = v2 / vLen(v2);
    v3 = v3 / vLen(v3);
    moveCoord(v1, v2, v3, A);
    moveCoord(v1, v2, v3, B);
    if (checkIntersect(A.x, A.z, B.x, B.z, R))
    {
        Vect2 E = findPointA(A.x, A.z, R, B.z > -eps);
        double ang = findAng(B.x, B.z, R, E);
        double sect = ang * R;
        cout << round((sqrt(A.x * A.x + A.z * A.z - R * R) + sqrt(B.x * B.x + B.z * B.z - R * R) + sect) * 100) / 100;
    }
    else
        cout << vLen(A - B);
    return 0;
}
