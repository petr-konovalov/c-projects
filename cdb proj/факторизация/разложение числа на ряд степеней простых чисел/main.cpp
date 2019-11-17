#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> primes;

bool isPrime(int number)
{
    int sq = (int)ceil(sqrt(number));
    for (vector<int>::iterator it = primes.begin(); it < primes.end() && *it <= sq; ++it)
    {
        if (number % *it == 0)
            return false;
    }

    return true;
}

void printDegrees(int number)
{
    int z = 0;
    for (vector<int>::iterator it = primes.begin(); it < primes.end() && *it <= number; ++it)
    {
        int a = 0;
        while (number % *it == 0)
        {
            number /= *it;
            ++a;
        }
        if (a == 0)
            ++z;
        else
        {
            for (int i = 0; i < z; ++i)
                cout << "0 ";
            z = 0;
            cout << a << ' ';
        }
    }
}

int main()
{
    for (int i = 2; i < 100; ++i)
    {
        if (isPrime(i))
            primes.push_back(i);
    }

    long long r = 1;
    for (int i = 0; i < 10; ++i)
    {
        r *= primes[i];
        cout << r << endl;
    }

    return 0;
}
