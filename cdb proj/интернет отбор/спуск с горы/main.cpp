#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int n;
    int a[100][100];
    int t[100][100];
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= i; ++j)
            scanf("%i", &a[i][j]);
    }
    t[0][0] = a[0][0];
    for (int i = 1; i < n; ++i)
    {
        t[i][0] = t[i - 1][0] + a[i][0];
        t[i][i] = t[i - 1][i - 1] + a[i][i];
        for (int j = 1; j < i; ++j)
            t[i][j] = max(t[i - 1][j], t[i - 1][j - 1]) + a[i][j];
    }
    int res = -10000000;
    for (int i = 0, l = n - 1; i < n; ++i)
        if (t[l][i] > res)
            res = t[l][i];
    printf("%i", res);
    return 0;
}
