#include <stdio.h>

using namespace std;

int len[10001];
int n, k;

int f(int l)
{
    if (l == 0)
        return 0;
    int s = 0;
    for (int i = 0; i < n; ++i)
        s += len[i] / l;
    return s;
}

int main()
{
    scanf("%i %i", &n, &k);
    for (int i = 0; i < n; ++i)
        scanf("%i", len + i);
    int l = 0, r = 10000001;
    while (r - l > 1)
    {
        int m = (r + l) >> 1;
        if (f(m) < k)
            r = m;
        else
            l = m;
    }
    printf("%i", l);
    return 0;
}
