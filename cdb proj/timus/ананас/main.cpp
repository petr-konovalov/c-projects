#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

double a, b;

double getS(double l, double r)
{
    return M_PI * a * a * ((r - l) / 4 + (l * l * l - r * r * r) / (3 * b * b));
}

int main()
{
    double d;
    int n;
    scanf("%lf %lf %i", &a, &b, &n);
    d = b / n;
    double l = -b/2;
    for (int i = 0; i < n; ++i)
    {
        printf("%.6lf\n", getS(l, l + d));
        l += d;
    }
    return 0;
}
