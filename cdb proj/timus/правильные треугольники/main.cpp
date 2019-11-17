#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    double x[9], y[9];
    for (int i = 0; i < 3; ++i)
        cin >> x[i] >> y[i];

    x[3] = x[0] + (x[1]+x[2]-2*x[0]) / 3;
    y[3] = y[0] + (y[1]+y[2]-2*y[0]) / 3;
    x[4] = x[3] + (x[2] - x[0]) / 6;
    y[4] = y[3] + (y[2] - y[0]) / 6;
    x[5] = x[3] + (x[1] - x[0]) / 6;
    y[5] = y[3] + (y[1] - y[0]) / 6;
    for (int i = 0; i < 3; ++i)
    {
        x[i+6] = x[i] + (x[(i+1)%3]+x[(i+2)%3]-2*x[i]) / 3 * 2;
        y[i+6] = y[i] + (y[(i+1)%3]+y[(i+2)%3]-2*y[i]) / 3 * 2;
    }

    for (int i = 3; i < 9; ++i)
        printf("%.10lf %.10lf\n", x[i], y[i]);
    return 0;
}
