#include <bits/stdc++.h>

using namespace std;

char res[1000001];

void solve()
{
    int n;
    int s;
    scanf("%i %i", &n, &s);
    res[n] = '\0';
    for (int i = 0; i < n; ++i)
        res[i] = '0';
    if (s > 9 * n || (n & 1) == 0 && (s & 1) || (n > 1) && s == 1)
        printf("-1\n");
    else
    {
        int i = 0, e = n >> 1;
        for (;i < e && s >= 18; ++i)
        {
            s -= 18;
            res[i] = '9';
            res[n - 1 - i] = '9';
        }
        if (n & 1)
        {
            if (i < e)
                res[e] = (s & 1) ? '1': '0';
            else
                res[e] = '0' + s;
        }
        if (i < e)
        {
            res[i] = '0' + (s >> 1);
            res[n - 1 - i] = res[i];
        }
        printf("%s\n", res);
    }
}

int main()
{
    int t;
    scanf("%i", &t);
    while (t--)
        solve();
    return 0;
}
