#include <bits/stdc++.h>

using namespace std;

int phi(int n)
{
    int res = n;

    for (int i = 2; i * 1ll * i <= n; ++i)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            res /= i;
            res *= i - 1;
        }
    }
    if (n > 1)
        res = res / n * (n - 1);

    return res;
}

int main()
{
    int n;
    while (scanf("%i", &n) == 1)
        printf("%i\n", phi(n));
    return 0;
}
