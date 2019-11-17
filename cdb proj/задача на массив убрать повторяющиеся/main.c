#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    int i = 0;
    int c = 0;

    scanf("%i", &n);

    int a[n];

    int b[10000] = {0};

    for (i = 0; i < n; ++i)
        scanf("%i", &a[i]);

    for (i = 0; i < n; ++i)
    {
        if (!b[a[i]])
        {
            b[a[i]] = 1;
        }
        else
        {
            a[i] = 0;
            ++c;
        }
    }

    for (i = 0; i < n; ++i)
        if (a[i])
            printf("%i ", a[i]);

    for (i = 0; i < c; ++i)
        printf("0 ");

    return 0;
}
