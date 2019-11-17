#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll f[21];

int main()
{
    f[0] = 1;
    for (ll i = 1; i < 21; ++i)
        f[i] = f[i - 1] * i;
    int c1, c2, c3;
    cin >> c1 >> c2 >> c3;
    cout << f[c1 + c2 + c3] / f[c1] / f[c2] / f[c3];
    return 0;
}
