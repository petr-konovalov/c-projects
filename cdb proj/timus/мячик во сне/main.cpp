#include <iostream>
#include <cmath>
#include <stdio.h>

#define PI 3.1415926535

using namespace std;

int main()
{
    const double eps = 1e-10;
    double v, a, k;
    cin >> v >> a >> k;

    a = a / 90 * PI;
    double ds = v * v * sin(a) / 10, s = ds;

    while (ds > eps)
    {
        ds /= k;
        s += ds;
    }

    printf("%.2lf", s);
    return 0;
}
