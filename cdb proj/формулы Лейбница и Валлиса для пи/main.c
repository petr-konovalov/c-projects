#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
    int n = 1;
    long long i = 1;
    double piL = 0;
    double piV = 1;
    scanf("%i", &n);
    for (i = 1; i < 2 * n + 1; i += 4)
    {
        piL += (double)2 / (i * (i + 2));
    }

    for (i = 2; i <= 2 * n; i += 2)
    {
        piV *= i;
        piV /= i - 1;
    }
    piV *= 2 * piV;
    piV /= 2 * n + 1;

    printf("Vallis  : %.20lf\n", piV);
    printf("Leibnic : %.20lf\n", piL * 4);
    printf("Standart: %.20lf", M_PI);
    return 0;
}
