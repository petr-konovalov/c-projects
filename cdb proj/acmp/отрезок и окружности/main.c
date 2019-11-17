#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define eps 1e-10

int main()
{
    double x1 = 0, y1 = 0,
           x2 = 0, y2 = 0,
           n = 1,
           A = 0, B = 0, C = 0,
           d = 0;
    int r = 0;
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
    for (n = 1; n <= 10000; n += 1)
    {
        A = y1 - y2;
        B = x2 - x1;
        C = -(A*x1 + B*y1);
        d = fabs(C) / sqrt(A * A + B * B);
        if (d < n + eps)
        {
            double x0 = -(A * C) / (A * A + B * B),
                   y0 = -(B * C) / (A * A + B * B);
            if (fabs(n-d) < eps)
            {
                if ((x1 < x0 + eps && x0 < x2 + eps || x2 < x0 + eps && x0 < x1 + eps) &&
                    (y1 < y0 + eps && y0 < y2 + eps || y2 < y0 + eps && y0 < y1 + eps))
                    ++r;
            }
            else
            {
                double v = sqrt((n - d)*(n + d)),
                       vx = (-B * v) / sqrt(A * A + B * B),
                       vy = (A * v) / sqrt(A * A + B * B),
                       ax = x0 + vx, ay = y0 + vy,
                       bx = x0 - vx, by = y0 - vy;
                if ((x1 < ax + eps && ax < x2 + eps || x2 < ax + eps && ax <= x1 + eps) &&
                    (y1 < ay + eps && ay < y2 + eps || y2 < ay + eps && ay <= y1 + eps))
                    ++r;
                if ((x1 < bx + eps && bx < x2 + eps || x2 < bx + eps && bx < x1 + eps) &&
                    (y1 < by + eps && by < y2 + eps || y2 < by + eps && by < y1 + eps))
                    ++r;
            }
        }
    }
    printf("%i", r);
    return 0;
}
