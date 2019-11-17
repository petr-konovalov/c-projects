#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll fact[20];

int main()
{
    int a[20];
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
        fact[i] = fact[i - 1] * i;
    ll res = 0;
    for (int i = 0; i < n; ++i)
    {
        int cnt = 0;
        for (int j = i + 1; j < n; ++j)
            if (a[i] > a[j])
                ++cnt;
        res += fact[n - i - 1] * cnt;
    }
    cout << res + 1;

    return 0;
}
