#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(double *first, double *second)
{
    double temp = *first;
    *first = *second;
    *second = temp;
}

void makeOppositePolynomial(double *polynomial, int deg)
{
    int i = 0;
    for (i = 1; i <= deg; i += 2)
        polynomial[i] = -polynomial[i];
}

void makeBackPolynomial(double *polynomial, int deg)
{
    int i = 0;
    for (i = 0; (i << 1) < deg; ++i)
        swap(polynomial + i, polynomial + deg - i);
}

double getUpBoardPositiveRoot(double *polynomial, int deg)
{
    double a = 0;
    int m = 0;
    int i = 0;

    for (i = 1; i <= deg; ++i)
    {
        if (polynomial[i] < 0)
        {
            if (m == 0)
                m = i;
            if (a < -polynomial[i])
                a = -polynomial[i];
        }
    }

    return 1 + pow(a / *polynomial, 1.0 / m);
}

double getDownBoardPositiveRoot(double *polynomial, int deg)
{
    makeBackPolynomial(polynomial, deg);
    double result = 1 / getUpBoardPositiveRoot(polynomial, deg);
    makeBackPolynomial(polynomial, deg);

    return result;
}

double getDownBoardNegativeRoot(double *polynomial, int deg)
{
    makeOppositePolynomial(polynomial, deg);
    double result = -getUpBoardPositiveRoot(polynomial, deg);
    makeOppositePolynomial(polynomial, deg);

    return result;
}

double getUpBoardNegativeRoot(double *polynomial, int deg)
{
    makeBackPolynomial(polynomial, deg);
    double result = 1 / getDownBoardNegativeRoot(polynomial, deg);
    makeBackPolynomial(polynomial, deg);

    return result;
}

double calcPolynomial(double *polynomial, int deg, double value)
{
    double result = 0;
    int i = 0;
    for (i = 0; i <= deg; ++i)
        result = result * value + polynomial[i];

    return result;
}

double calcDerivatePolynomial(double *polynomial, int deg, double value)
{
    double result = 0;
    int i = 0;
    for (i = 0; i < deg; ++i)
        result = result * value + polynomial[i] * (deg - i);

    return result;
}

double getRootPolynomialOnSegment(double *polynomial, int deg, double left, double right, double eps)
{
    double x = (right + left) / 2;
    double newX = x - calcPolynomial(polynomial, deg, x) / calcDerivatePolynomial(polynomial, deg, x);
    int iter = 0;

    while (fabs(newX - x) >= eps)
    {
        x = newX;
        newX = x - calcPolynomial(polynomial, deg, x) / calcDerivatePolynomial(polynomial, deg, x);
        ++iter;
    }

    return newX;
}

double *getRootsPolynomialOnSegment(double *polynomial, int deg, int *count, double left, double right,
                                    int splitDeg, double eps)
{
    *count = 0;
    if (left > right)
        return NULL;

    double step = (right - left) / splitDeg;
    double previous = calcPolynomial(polynomial, deg, left);
    double current = left + step;
    double *result = malloc(sizeof(double) * deg);

    while (current <= right)
    {
        double value = calcPolynomial(polynomial, deg, current);
        if ((value < eps && previous > -eps) || (value > -eps && previous < eps))
        {
            result[*count] = getRootPolynomialOnSegment(polynomial, deg, current - step, current, eps);
            ++*count;
        }
        previous = value;
        current += step;
    }

    return result;
}

double *getRootsPolynomial(double *polynomial, int deg, int *count, int splitDeg, double eps)
{
    int negativeRootsCount = 0;
    double *negativeRoots = getRootsPolynomialOnSegment(polynomial, deg, &negativeRootsCount,
        getDownBoardNegativeRoot(polynomial, deg), getUpBoardNegativeRoot(polynomial, deg), splitDeg, eps);
    int positiveRootsCount = 0;
    double *positiveRoots = getRootsPolynomialOnSegment(polynomial, deg, &positiveRootsCount,
        getDownBoardPositiveRoot(polynomial, deg), getUpBoardPositiveRoot(polynomial, deg), splitDeg, eps);
    *count = negativeRootsCount + positiveRootsCount;
    double *result = malloc((negativeRootsCount + positiveRootsCount) * sizeof(double));
    int i = 0;

    for (i = 0; i < negativeRootsCount; ++i)
        result[i] = negativeRoots[i];
    for (i = 0; i < positiveRootsCount; ++i)
        result[negativeRootsCount + i] = positiveRoots[i];
    free(negativeRoots);
    free(positiveRoots);

    return result;
}

double *getSinApproximate(int precision)
{
    int n = precision * 2 + 1;
    double *approximate = calloc(n + 1, sizeof(double));
    int i = 0;
    approximate[n - 1] = 1.0;
    for (i = 3; i <= n; i += 2)
        approximate[n - i] = approximate[n - i + 2] / ((-i + 1) * i);

    return approximate;
}

int main()
{
    double *polynomial = NULL;
    int deg = 0;
    int i = 0;

    scanf("%i", &deg);
    /*
    deg = deg & 1 ? deg: deg - 1;
    polynomial = getSinApproximate(deg >> 1);
    polynomial[deg - 2] = 0.25;
    if (*polynomial < 0)
        for (i = 0; i <= deg; ++i)
            polynomial[i] *= -1;
        */
    polynomial = malloc(sizeof(double) * (deg + 1));
    for (i = 0; i <= deg; ++i)
        scanf("%lf", polynomial + i);

    for (i = 0; i <= deg; ++i)
        printf("%.20lf\n", polynomial[i]);
    printf("\n");

    int rootsCount = 0;
    double *roots = getRootsPolynomial(polynomial, deg, &rootsCount, 100, 1e-10);

    for (i = 0; i < rootsCount; ++i)
        printf("%.15lf\n", roots[i]);

    printf("\n");
    for (i = 0; i < rootsCount; ++i)
        printf("%.15lf\n", calcPolynomial(polynomial, deg, roots[i]));

    free(polynomial);
    return 0;
}
