#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct
{
    double e[3][3];
} matr;

matr mult(matr a, matr b)
{
    matr r;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            r.e[i][j] = 0;
            for (int l = 0; l < 3; ++l)
                r.e[i][j] += a.e[i][l] * b.e[l][j];
        }
    }
    return r;
}

int main()
{
    double c[3000];
    double a0, an1;
    int n;
    scanf("%i", &n);
    scanf("%lf", &a0);
    scanf("%lf", &an1);
    for (int i = 0; i < n; ++i)
        scanf("%lf", c + i);
    matr b, p;
    b.e[0][0] = b.e[2][0] = b.e[0][2] = b.e[1][2] = 0;
    b.e[0][1] = -1;
    b.e[1][0] = b.e[2][2] = 1;
    b.e[1][1] = 2;
    b.e[2][1] = 2 * c[0];
    p = b;
    for (int i = 1; i < n; ++i)
    {
        p.e[2][1] = 2 * c[i];
        b = mult(b, p);
    }
    printf("%.2lf",(an1 - b.e[0][1] * a0 - b.e[2][1]) / b.e[1][1]);
    return 0;
}
