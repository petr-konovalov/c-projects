#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

unsigned long long binPow(unsigned long long a, int deg)
{
    unsigned long long res = 1;
    while (deg)
    {
        if (deg & 1)
            res *= a;
        a *= a;
        deg >>= 1;
    }
    return res;
}

int main()
{
    unsigned long long n;
    int res = 0;
    cin >> n;
    for (unsigned long long i = 2; res < 19 && binPow(i, 20 - res) <= n; ++i)
        while (n % i == 0)
        {
            ++res;
            n /= i;
        }
    if (res == 20)
    {
        if (n == 1)
            printf("Yes");
        else
            printf("No");
    }
    else if (res == 19)
    {
        for (unsigned long long i = 2; i * i <= n; ++i)
            if (n % i == 0)
            {
                printf("No");
                return 0;
            }
        printf("Yes");
    }
    else
        printf("No");
    return 0;
}
