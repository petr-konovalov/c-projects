#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

int main()
{
    long long int a[41][41];
    int m, n;
    scanf("%i:%i", &m, &n);
    if (m < n)
        swap(m, n);
    for (int i = 0; i <= m; ++i)
        a[i][0] = 1;
    for (int i = 0; i <= n; ++i)
        a[0][i] = 1;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (i < 25 && j < 25 || i == j)
                a[i][j] = a[i - 1][j] + a[i][j - 1];
            else if (i > j)
                a[i][j] = a[i - 1][j];
            else
                a[i][j] = a[i][j - 1];
    printf("%lli", a[m][n]);
    return 0;
}
