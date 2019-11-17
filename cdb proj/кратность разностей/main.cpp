#include <bits/stdc++.h>

using namespace std;

vector<int> num[100001];


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int m, n, k;
    cin >> n >> k >> m;
    for (int i = 0; i < n; ++i)
    {
        int a;
        cin >> a;
        num[a % m].push_back(a);
    }

    for (int i = 0; i < 100001; ++i)
        if (num[i].size() >= k)
        {
            cout << "Yes\n";
            for (int j = 0; j < k; ++j)
                cout << num[i][j] << ' ';
            return 0;
        }
    cout << "No";
    return 0;
}
