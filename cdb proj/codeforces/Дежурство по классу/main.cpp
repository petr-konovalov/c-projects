#include <bits/stdc++.h>

using namespace std;

int sumDigit(int n)
{
    int res = 0;
    while (n)
    {
        res += n % 10;
        n /= 10;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> ans;
    for (int i = max(1, n - 100); i < n; ++i)
        if (i + sumDigit(i) == n)
            ans.push_back(i);
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i] << ' ';
    return 0;
}
