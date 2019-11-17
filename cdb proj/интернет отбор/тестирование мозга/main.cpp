#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

long long getAns(long long n)
{
    long long k = 1;
    long long res = 0;
    long long sk;
    while ((sk = k * k) <= n)
    {
        long long a = n / sk;
        long double ln = (long double) n;
        long long cnt = (long long)sqrt(ln / a) - (long long)sqrt(ln / (a + 1));
        k += cnt;
        res += cnt * a;
    }
    return res;
}

int main()
{
    long long n;
    scanf("%lli", &n);
    printf("%lli", getAns(n));
    return 0;
}
