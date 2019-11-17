#include <iostream>

using namespace std;

bool isPrime[1000];

void getPrimes()
{
    for (int i = 2; i < 1000; ++i)
        isPrime[i] = true;
    for (int i = 2; i < 1000; ++i)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j < 1000; j += i)
                isPrime[j] = false;
        }
    }
}

int main()
{
    getPrimes();
    int primes[143];
    int c = 0;
    int res = 0;
    for (int a1 = 1; a1 < 10; ++a1)
    for (int a2 = 0; a2 < 10; ++a2)
    for (int a3 = 0; a3 < 10; ++a3)
    for (int a4 = 0; a4 < 10; ++a4)
    for (int a5 = 0; a5 < 10; ++a5)
    for (int a6 = 0; a6 < 10; ++a6)
    for (int a7 = 0; a7 < 10; ++a7)
    for (int a8 = 0; a8 < 10; ++a8)
    for (int a9 = 0; a9 < 10; ++a9)
    {
        if (isPrime[a1 * 100 + a2 * 10 + a3] &&
            isPrime[a2 * 100 + a3 * 10 + a4] &&
            isPrime[a3 * 100 + a4 * 10 + a5] &&
            isPrime[a4 * 100 + a5 * 10 + a6] &&
            isPrime[a5 * 100 + a6 * 10 + a7] &&
            isPrime[a6 * 100 + a7 * 10 + a8] &&
            isPrime[a7 * 100 + a8 * 10 + a9])
            ++res;
    }
    cout << res;
    return 0;
}
