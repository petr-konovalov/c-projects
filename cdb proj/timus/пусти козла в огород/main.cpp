#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

int main()
{
    double d, r;
    double result;
    cin >> d >> r;
    d /= 2;
    if (r <= d)
        result = M_PI * r * r;
    else if (r >= d * sqrt(2))
        result = 4 * d * d;
    else
    {
        double s = d * sqrt(r * r - d * d);
        result = 2 * r * r * acos(2 * s / (r * r)) + 4 * s;
    }

    printf("%.3lf", result);
    return 0;
}
