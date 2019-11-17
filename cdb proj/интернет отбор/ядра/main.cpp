#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int a[256] = {0};
    int d = 1;
    int c = 1;
    a[0] = 0;
    for (c = 1; a[c - 1] <= 300000; ++c)
    {
        a[c] = a[c - 1] + d;
        d += c + 1;
    }
    int res[300001];
    res[0] = 0;
    for (int i = 1; i <= 300000; ++i)
    {
        res[i] = 1000000;
        for (int j = 1, t; j < c && (t = i - a[j]) >= 0; ++j)
            if (res[i] > res[t] + 1)
                res[i] = res[t] + 1;
    }
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
    {
        int m;
        scanf("%i", &m);
        printf("%i\n", res[m]);
    }
    return 0;
}
