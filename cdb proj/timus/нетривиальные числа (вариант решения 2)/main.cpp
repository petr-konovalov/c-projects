#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int x)
{
    if (x == 2)
        return true;
    int sq = (int)ceil(sqrt(x));
    for (int i = 2; i < sq; ++i)
        if (x % i == 0)
            return false;
    return true;
}

int sumd(int x)
{
    int sq = (int)ceil(sqrt(x));
    int result = 1;
    for (int i = 2; i < sq; ++i)
    {
        if (x % i == 0)
            result += i + x / i;
    }
    if (x == sq * sq)
        x += sq;
    return result;
}

int main()
{
    int I, J;
    cin >> I >> J;
    if (I == 1)
    {
        cout << 1;
        return 0;
    }
    long long r = I, sum = sumd(I);
    for (int i = J; i > I; --i)
    {
        if (isPrime(i))
        {
            cout << i;
            return 0;
        }
        long long newSum = sumd(i);
        if (newSum * r < sum * i)
        {
            sum = newSum;
            r = i;
        }
    }
    cout << r;
    return 0;
}
