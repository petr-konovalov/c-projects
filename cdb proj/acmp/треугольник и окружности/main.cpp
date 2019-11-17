#include <iostream>
#include <cmath>

using namespace std;

struct Pt
{
    double x, y;
    Pt(){}
    Pt(double x, double y): x(x), y(y) {}
};

Pt operator+ (Pt a, Pt b)
{
    return Pt(a.x + b.x, a.y + b.y);
}

Pt operator- (Pt a, Pt b)
{
    return Pt(a.x - b.x, a.y - b.y);
}

Pt operator/ (Pt a, double b)
{
    return Pt(a.x / b, a.y / b);
}

double len(Pt a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}

Pt norma(Pt a)
{
    return a / len(a);
}

Pt getBiss(Pt a, Pt b)
{
    return norma(a) + norma(b);
}

Pt getNormal(Pt a)
{
    return Pt(a.y, -a.x);
}

double dist(Pt a, Pt b)
{
    return len(a - b);
}

double getS(Pt a, Pt b)
{
    return abs(a.x * b.y - a.y * b.x);
}

Pt getInPoint(Pt trn[3], double &r)
{
    Pt pnt;
    Pt v1 = getBiss(trn[1] - trn[0], trn[2] - trn[0]);
    Pt v2 = getBiss(trn[0] - trn[1], trn[2] - trn[1]);
    double A1 = v1.y, B1 = -v1.x, C1 = trn[0].y*v1.x - trn[0].x * v1.y;
    double A2 = v2.y, B2 = -v2.x, C2 = trn[1].y*v2.x - trn[1].x * v2.y;
    double det = A1 * B2 - A2 * B1;
    pnt.x = -(C1 * B2 - C2 * B1) / det;
    pnt.y = -(A1 * C2 - A2 * C1) / det;
    r = getS(pnt - trn[0], trn[1] - trn[0]) / dist(trn[0], trn[1]);
    return pnt;
}

Pt getOutPoint(Pt trn[3], double &r)
{
    Pt pnt;
    Pt p1 = (trn[0] + trn[1]) / 2;
    Pt p2 = (trn[0] + trn[2]) / 2;
    Pt v1 = getNormal(trn[1] - trn[0]);
    Pt v2 = getNormal(trn[2] - trn[0]);
    double A1 = v1.y, B1 = -v1.x, C1 = p1.y*v1.x - p1.x * v1.y;
    double A2 = v2.y, B2 = -v2.x, C2 = p2.y*v2.x - p2.x * v2.y;
    double det = A1 * B2 - A2 * B1;
    pnt.x = -(C1 * B2 - C2 * B1) / det;
    pnt.y = -(A1 * C2 - A2 * C1) / det;
    r = dist(pnt, trn[0]);
    return pnt;
}

int main()
{
    struct Pt trn[3];
    cin >> trn[0].x >> trn[0].y
        >> trn[1].x >> trn[1].y
        >> trn[2].x >> trn[2].y;
    char str[8];
    cin >> str;
    if (str[0] == 'I')
    {
        double r;
        Pt pnt = getInPoint(trn, r);
        cout << pnt.x << ' ' << pnt.y << ' ' << r;
    }
    else
    {
        double r;
        Pt pnt = getOutPoint(trn, r);
        cout << pnt.x << ' ' << pnt.y << ' ' << r;
    }
    return 0;
}
