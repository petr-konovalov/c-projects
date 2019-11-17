#include <bits/stdc++.h>

using namespace std;

int r[3000100];

int main()
{
    int n;
    cin >> n;
    r[1] = 1;
    int a = 1, b = 1, d = 0;
    for (int i = 2; i < n; ++i)
    {
        r[i] = ((n - n / i) * 1ll * r[n % i]) % n;
        if (d < abs(i - r[i]))
        {
            d = abs(i - r[i]);
            a = i;
            b = r[i];
        }
    }
    cout << a << ' ' << b;
    return 0;
}
