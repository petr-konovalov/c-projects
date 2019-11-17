#include <iostream>
#include <stdio.h>

using namespace std;

int data[5001];
int s[5001];

int get(int i)
{
    int l = 0, r = 5000;
    while ((r - l) > 1)
    {
        int m = (l + r) / 2;
        if (s[m] < i)
            l = m;
        else
            r = m;
    }
    return r;
}

int main()
{
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
    {
        int inp;
        scanf("%i", &inp);
        ++data[inp];
    }

    s[0] = 0;
    for (int i = 1; i < 5000; ++i)
        s[i] = s[i - 1] + data[i];

    char str[5];
    scanf("%s", str);
    int k;
    scanf("%i", &k);
    for (int i = 0; i < k; ++i)
    {
        int z = 0;
        scanf("%i", &z);
        printf("%i\n", get(z));
    }
    return 0;
}
