#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int c = 0, primes[100000];
int d[1000001];

int main()
{
    int m, n;
    cin >> m >> n;
    for (int i = 2; i <= n; ++i)
    {
        if (d[i] == 0)
        {
            primes[c++] = i;
            d[i] = i;
        }
        for (int j = 0; j < c && primes[j] <= d[i] && primes[j] * i <= n; ++j)
            d[primes[j] * i] = primes[j];
    }
    bool b = true;
    for (int i = m; i <= n; ++i)
        if (d[i] == i)
            printf("%i\n", i), b = false;
    if (b)
        printf("Absent");
    return 0;
}
