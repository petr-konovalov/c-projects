#include <bits/stdc++.h>

using namespace std;

void solve()
{
    long long c;
    cin >> c;
    long long k = (-1 + sqrt(1 + 8 * c)) / 2;
    k = k * (k + 1) / 2;
    if (k <= 3)
        cout << 0 << '\n';
    else
        cout << k << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
