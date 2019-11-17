#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 0;
    int a = 0;
    int d = 0;
    int c = 0;
    int i = 0;

    scanf("%i %i %i %i", &a, &c, &d, &x);

    int b[d];

    for(i = 0; i < d; ++i)
        b[i] = 0;

    while(!b[x])
    {
        b[x] = 1;
        printf("%i ", x);
        x = (x * a + c) % d;
    }
    return 0;
}
