#include <stdio.h>

using namespace std;

long long fact[50];
int deg[50];
int c;

void getFact(long long n)
{
    for (long long i = 2; i * i <= n; ++i)
        if (n % i == 0)
        {
            while (n % i == 0)
            {
                ++deg[c];
                n /= i;
            }
            fact[c++] = i;
        }
    if (n > 1)
    {
        deg[c] = 1;
        fact[c++] = n;
    }
}

long long result = 1000000000000000000;
long long ra, rb, rc;
long long n;

void findAns(const int m, const long long first, long long res)
{
    if (m == c)
    {
        long long t = first * res;
        long long third = n / t;
        long long cur = 2 * (t + third * first + third * res);
        if (cur < result)
        {
            ra = first;
            rb = res;
            rc = third;
            result = cur;
        }
        return;
    }
    int p = deg[m];
    while (deg[m] >= 0)
    {
        findAns(m + 1, first, res);
        res *= fact[m];
        --deg[m];
    }
    deg[m] = p;
}

void findAns(const int m, long long res)
{
    if (m == c)
    {
        findAns(0, res, 1);
        return;
    }
    int p = deg[m];
    while (deg[m] >= 0)
    {
        findAns(m + 1, res);
        res *= fact[m];
        --deg[m];
    }
    deg[m] = p;
}

int main()
{
    scanf("%lli", &n);
    getFact(n);
    findAns(0, 1);
    printf("%lli %lli %lli %lli", result, ra, rb, rc);
    return 0;
}
