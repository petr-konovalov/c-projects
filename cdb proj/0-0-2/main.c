#include <stdio.h>
#include <stdlib.h>
#include "unit1.h"

int main()
{
    struct vect a, b, c;
    scanf("%lf %lf %lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
    printf("%lf %lf", summ3(a, b, c));
    return 0;
}
