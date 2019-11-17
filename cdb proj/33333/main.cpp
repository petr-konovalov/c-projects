#include <bits/stdc++.h>

using namespace std;

set<int> s;

int p;

int cube(int arg)
{
    return (long long)arg * arg * arg % p;
}

bool isPrime(int n)
{
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return false;
    return true;
}

int main()
{
    for (p = 2; p < 10000; ++p)
    {
        //if (isPrime(p))
        {
            bool res = true;
            for (int x = 1; x < p; ++x)
            {
                for (int y = 1; y < p; ++y)
                {
                    if ((cube(x) + cube(y)) % p == 1)
                    {
                        //cout << p << ": " << x << ' ' << y << '\n';
                        res = false;
                    }
                }
            }
            if (res)
                cout << p << '\n';
        }
    }


    return 0;
}
