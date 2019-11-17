#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    long long n = 1;
    long long i = 1;
    double pi = 0;
    scanf("%i", &n);
    for (i = 1; i < 4 * n + 1; i += 4)
    {
        pi += (double)2 / (i * (i + 2));
    }
    printf("%.20lf\n", pi * 4);
    printf("%.20lf", M_PI);
    return 0;
}
