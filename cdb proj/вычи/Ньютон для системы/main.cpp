#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>

using namespace std;

struct Point
{
    double x;
    double y;
    Point(double x, double y): x(x), y(y){};
    Point(){x = 0; y = 0;}
};

Point findFunc(double t, double k)
{
    return Point((tanh(t) / k + t) * 0.5, (tanh(t) / k - t) * 0.5);
}

double firstFunc(Point v, double k)
{
    return tanh(v.x - v.y) - k * (v.x + v.y);
}

double secondFunc(Point v, double a)
{
    return pow(v.x - 0.2, 2) - a * pow(v.y, 2) - 1.5;
}

Point derFirstFunc(Point v, double k)
{
    return Point(1 / pow(cosh(v.x - v.y), 2) - k, -1 / pow(cosh(v.x - v.y), 2) - k);
}

Point derSecondFunc(Point v, double a)
{
    return Point(2 * v.x - 0.4, -2 * a * v.y);
}

double det(double a11, double a12, double a21, double a22)
{
    return a11 * a22 - a12 * a21;
}

double dist(Point a, Point b)
{
    return pow(pow(a.x - b.x, 2) + pow(a.y - b.y, 2), 0.5);
}

Point getNextApproximate(Point v, double a, double k)
{
    Point df = derFirstFunc(v, k);
    Point dg = derSecondFunc(v, a);
    double f = firstFunc(v, k);
    double g = secondFunc(v, a);
    double d = det(df.x, df.y,
                   dg.x, dg.y);
    double dx = -det(f, df.y,
                     g, dg.y);
    double dy = -det(df.x, f,
                     dg.x, g);

    return Point(v.x + dx / d, v.y + dy / d);
}

Point findRoot(Point v0, double a, double k, double eps)
{
    Point prevApp = v0;
    Point curApp = getNextApproximate(v0, a, k);
    int iter = 0;

    while (dist(prevApp, curApp) >= eps)
    {
        printf("%2i %15.10f %15.10f %15.10f %15.10f\n", iter, curApp.x, curApp.y, firstFunc(curApp, k), secondFunc(curApp, a));
        prevApp = curApp;
        curApp = getNextApproximate(curApp, a, k);
        ++iter;
    }
    printf("%2i %15.10f %15.10f %15.10f %15.10f\n\n", iter, curApp.x, curApp.y, firstFunc(curApp, k), secondFunc(curApp, a));

    return curApp;
}

vector<Point> calcRoots(double leftBound, double rightBound, double step, double a, double k, double eps)
{
    double prev = 0;
    double cur = secondFunc(findFunc(leftBound, k), a);
    vector<Point> res;

    for (double t = leftBound; t < rightBound; t += step)
    {
        prev = cur;
        cur = secondFunc(findFunc(t + step, k), a);
        if (prev < eps && cur > -eps || prev > -eps && cur < eps)
            res.push_back(findRoot(findFunc(t + step / 2, k), a, k, eps));
    }

    return res;
}

int main()
{
    freopen("result.txt", "w", stdout);

    for (double a = 1; a <= 6; a += 1)
        for (double k = 0.44; k <= 0.52; k += 0.02)
        {
            printf("a = %f k = %f\n", a, k);
            printf("%2s %15s %15s %15s %15s\n", "k", "xk", "yk", "f(xk, yk)", "g(xk, yk)");
            calcRoots(-100, 100, 0.1, a, k, 1e-8);
            printf("\n");
        }
    return 0;
}
