#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    const int mod = 1000000009;
    int a1 = 1, a2 = 2, a;
    int n;
    scanf("%i", &n);
    --n;
    if (n <= 2)
        printf("%i", n);
    else
    {
        for (int i = 3; i <= n; ++i)
        {
            a = (i * 1ll * (a1 + a2)) % mod;
            a1 = a2;
            a2 = a;
        }
        printf("%i", a);
    }
    return 0;
}
