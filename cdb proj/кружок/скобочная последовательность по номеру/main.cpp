#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll d[61][61];
char res[50];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    d[0][0] = 1;
    for (int i = 1; i < 61; ++i)
        d[0][i] = 0;
    for (int n = 1; n < 61; ++n)
    {
        d[n][0] = d[n - 1][1];
        for (int b = 1; b < 61; ++b)
            d[n][b] = d[n - 1][b - 1] + d[n - 1][b + 1];
    }
    int n;
    ll x;
    cin >> n >> x;
    ++x;
    int depth = 0;
    for (int i = 0, e = 2 * n; i < e; ++i)
    {
        if (d[e - (i + 1)][depth + 1] >= x)
        {
            res[i] = '(';
            ++depth;
        }
        else
        {
            x -= d[e - (i + 1)][depth + 1];
            res[i] = ')';
            --depth;
        }
    }
    cout << res;
    return 0;
}
