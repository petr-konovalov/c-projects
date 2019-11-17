#include <bits/stdc++.h>

using namespace std;

void solve(int n)
{
    for (int i = 2; i * 1ll * i <= n; ++i)
    {
        while (n % i == 0)
        {
            printf("%i ", i);
            n /= i;
        }
    }
    if (n > 1)
        printf("%i", n);
}

int main()
{
    int n;
    scanf("%i", &n);
    solve(n);
    return 0;
}
