#include <bits/stdc++.h>

using namespace std;

const int maxInt = 1500000;
vector<int> primes;
vector<bool> isPrime(maxInt, true);

void getPrimes()
{
    for (int i = 2; i < maxInt; ++i)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
            if (i * 1ll * i < maxInt)
                for (int j = i * i; j < maxInt; j += i)
                    isPrime[j] = false;
        }
    }
}

int main()
{
    getPrimes();
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
    {
        int p;
        scanf("%i", &p);
        --p;
        printf("%i ", primes[p]);
    }
    return 0;
}
