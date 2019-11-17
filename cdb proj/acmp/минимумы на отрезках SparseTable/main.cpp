#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

int n;
int a[100000];
int st[100000][20];
int log2[100001];

int main()
{
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
        scanf("%i", a + i);
    for (int i = 0; i < n; ++i)
        st[i][0] = a[i];
    log2[1] = 0;
    for (int i = 2, j = 0; i <= n; ++i)
    {
        if (i >= 1 << (j + 1))
            ++j;
        log2[i] = j;
    }
    for (int j = 0; j <= log2[n]; ++j)
        for (int i = 0; i < n; ++i)
        {
            int ni = i + (1 << j);
            if (ni >= n)
                st[i][j + 1] = st[i][j];
            else
                st[i][j + 1] = min(st[i][j], st[ni][j]);
        }
    int m;
    scanf("%i", &m);
    for (int i = 0; i < m; ++i)
    {
        int l, r;
        scanf("%i %i", &l, &r);
        --l;
        --r;
        int sz = log2[r - l + 1];
        printf("%i\n", min(st[l][sz], st[r - (1 << sz) + 1][sz]));
    }
    return 0;
}
