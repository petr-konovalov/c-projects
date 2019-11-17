#include <iostream>

using namespace std;

bool binSearch(long long *a, int n, int value)
{
    int l = 0;
    int r = n - 1;

    while (r - l > 1)
    {
        int m = (r + l) / 2;
        if (a[m] > value)
            r = m;
        else
            l = m;
    }
    return a[l] == value;
}

int main()
{
    long long a[65550 * 2];
    long long c = 0;
    long long k = 0;
    long long dk = 1;
    while (k <= (1ll << 32))
    {
        a[c] = k + 1;
        k += ++c;
    }

    int n = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int ki;
        cin >> ki;
        cout << (binSearch(a, c, ki) ? '1': '0') << ' ';
    }
    return 0;
}
