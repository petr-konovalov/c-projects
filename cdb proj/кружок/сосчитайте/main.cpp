#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll C[61][61];

int main()
{
    C[0][0] = 1;
    for (int n = 1; n < 61; ++n)
    {
        C[n][0] = 1;
        for (int k = 1; k < 61; ++k)
            C[n][k] = C[n - 1][k] + C[n - 1][k - 1];
    }
    int m, n;
    cin >> m >> n;
    ll res = 0;
    for (int i = 0; i <= n; ++i)
        res += C[m + i - 1][i];
    cout << res;
    return 0;
}
