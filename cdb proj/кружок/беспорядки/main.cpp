#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    if (n == 1)
        cout << 0;
    else
    {
        long long res = 0;
        long long fact = 1;
        for (int i = 2; i <= n; ++i)
            fact *= i;
        for (int i = 2, z = 1; i <= n; ++i)
        {
            fact /= i;
            res += fact * z;
            z *= -1;
        }
        cout << res;
    }
    return 0;
}
