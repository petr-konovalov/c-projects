#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 1000

int main()
{
    int n = 0;
    int i = 0;
    int j = 0;
    int count = 0;
    double eps = 0;
    double a[N] = {0};
    scanf("%i", &n);
    scanf("%lf", &eps);
    for (i = 0; i < n; ++i)
        scanf("%lf", &a[i]);
    for (i = 0; i < n; ++i)
    {
        for (j = i + 1; j < n; ++j)
            if (fabs(a[i]-a[j]) < eps)
                ++count;
    }
    printf("%i", count);
    return 0;
}
