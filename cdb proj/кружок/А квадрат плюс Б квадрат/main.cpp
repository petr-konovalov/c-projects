#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000000

bool isSqr(int b)
{
    int sq = (int)sqrt(b);
    return sq * sq == b;
}

void solve()
{
    int n;
    int res = 0;
    scanf("%i", &n);
    for (int i = 1; i * 2ll * i <= n; ++i)
    {
        int a = i * i;
        int b = n - a;
        if (isSqr(b))
        {
            if (a == b)
                res += 1;
            else
                res += 2;
        }
    }
    printf("%i\n", res);
}

int main()
{
    int t;
    scanf("%i", &t);
    while (t--)
        solve();
    return 0;
}
