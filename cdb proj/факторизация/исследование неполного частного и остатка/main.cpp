#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

bool prime (int x)
{
    bool result = true;
    for (int i = 2; i <= sqrt(x) && result; ++i)
        if (x%i == 0) result = false;
    return result;
}

int gcd (int a, int b)
{
    while (b != 0) b^=a^=b^=a%=b;
    return a;
}

int main()
{

    int n = 0;
    scanf("%i", &n);

    for (int i = 1; i <= n; ++i)
    {
        int q = n/i, r = n%i;
        printf("%5i %5i %5i %5i\n", i, q, r, gcd(n, i));
    }

    return 0;
}
