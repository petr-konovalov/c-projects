#include <stdio.h>
#include <stdlib.h>

typedef double (*func_type)(double);

double integral(double l, double r, int n, func_type f)
{
    if (r < l)
        return -integral(r, l, n, f);

    const eps = 1e-6;
    double step = (r - l) / n;
    double result = 0;

    while (l < r + eps)
    {
        result += f(l) * step;
        l += step;
    }

    return result;
}

double eps_integral(double l, double r, double eps, func_type f)
{
    int n = 2;
    double previous_integral = integral(l, r, n, f);
    double next_integral = integral(l, r, n *= 2, f);

    while (fabs(previous_integral - next_integral) > eps)
    {
        previous_integral = next_integral;
        next_integral = integral(l, r, n *= 2, f);
    }

    return next_integral;
}

double g(double x)
{
    return x*x;
}

int main()
{
    printf("%lf", eps_integral(-1, 1, 1e-10, &g));
    return 0;
}
