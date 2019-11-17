#include <iostream>

using namespace std;

int main()
{
    long long infinity = 1;
    infinity <<= 62;
    long long a[101] = {0};
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int t = 0;
        cin >> a[i];
        cin >> t;
        a[i + 1] = t;
    }
    long long M[101][101] = {0};
    for (int len = 2; len <= n; ++len)
    {
        for (int l = 0; l + len <= n; ++l)
        {
            int r = l + len;
            M[l][r] = infinity;
            for (int m = l + 1; m < r; ++m)
            {
                long long v = M[l][m] + a[l] * a[r] + M[m][r];
                if (v < M[l][r])
                    M[l][r] = v;
            }
        }
    }
    cout << M[0][n];
    return 0;
}
