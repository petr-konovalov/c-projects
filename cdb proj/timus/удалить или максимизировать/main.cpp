#include <iostream>
#include <stdio.h>

using namespace std;

unsigned int a[101];
int n, k;
unsigned int s;

int getMaxId()
{
    unsigned int res = s | a[0];
    int id = 0;
    for (int i = 1; i < k; ++i)
    {
        unsigned int t = s | a[i];
        if (res < t)
        {
            res = t;
            id = i;
        }
    }
    return id;
}

int main()
{
    scanf("%i %i", &n, &k);
    for (int i = 0; i <= k; ++i)
    {
        scanf("%u", a + i);
        if (a[i] > a[s])
            s = i;
    }
    swap(a[s], a[k]);
    s = a[k];
    for (int i = k + 1; i < n; ++i)
    {
        unsigned int t;
        scanf("%u", &t);
        int id = getMaxId();
        if ((s | t) < (s | a[id]))
        {
            s = s | a[id];
            a[id] = t;
        }
        else
            s = s | t;
    }
    printf("%u", s);
    return 0;
}
