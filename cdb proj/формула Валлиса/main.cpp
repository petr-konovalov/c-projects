#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

int main()
{
    int n = 0;
    double pi = 1;

    cin >> n;

    for (int i = 2, e = 2 * n; i <= e; i += 2)
    {
        pi *= i;
        pi /= i - 1;
    }
    pi *= 2 * pi;
    pi /= 2 * n + 1;

    printf("%.20lf\n", pi);
    printf("%.20lf", M_PI);
    return 0;
}
