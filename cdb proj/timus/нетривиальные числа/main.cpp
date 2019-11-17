#include <iostream>
#include <cmath>

using namespace std;

int primes[500] = {0};
int primesCount = 0;
int sumsd[1000001] = {0};

int sumd(int x)
{
    int sq = (int)ceil(sqrt(x));
    int result = 1;
    bool b = true;
    for (int i = 0; primes[i] <= sq; ++i)
    {
        if (x % primes[i] == 0)
        {
            int d = primes[i];
            while (x % d == 0)
                d *= primes[i];
            result *= sumsd[x * primes[i] / d] * (d - 1)/(primes[i] - 1);
            b = false;
            break;
        }
    }
    if (b)
        result = x + 1;
    sumsd[x] = result;
    return result - x;
}

bool isPrime(int x)
{
    double sq = ceil(sqrt(x));
    for (int i = 2; i <= sq; ++i)
        if (x % i == 0)
            return false;
    return true;
}

int main()
{
    sumsd[0] = 0;
    sumsd[1] = 1;
    sumsd[2] = 3;
    sumsd[3] = 4;
    sumsd[4] = 7;
    primes[primesCount++] = 2;
    for (int i = 3; primes[primesCount - 1] < 1000; ++i)
    {
        if (isPrime(i))
            primes[primesCount++] = i;
    }
    int I, J;
    cin >> I >> J;
    if (I == 1)
    {
        cout << I;
        return 0;
    }
    for (int i = 5; i <= J; ++i)
        sumd(i);
    long long sum = sumsd[I] - I, r = I;
    for (int i = I + 1; i <= J; ++i)
    {
        long long newSum = sumsd[i] - i;
        if (newSum * r < sum * i)
        {
            sum = newSum;
            r = i;
        }
    }
    cout << r;
    return 0;
}
