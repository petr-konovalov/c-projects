#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

int main()
{
    int n;
    double x[100], y[100];
    double r;
    cin >> n >> r;
    double result = 2 * M_PI * r;
    for (int i = 0; i < n; ++i)
        cin >> x[i] >> y[i];

    for (int i = 0; i < n; ++i)
        result += sqrt(pow(x[i] - x[(i + 1) % n], 2) + pow(y[i] - y[(i + 1) % n], 2));

    printf("%.2lf", result);
    return 0;
}
