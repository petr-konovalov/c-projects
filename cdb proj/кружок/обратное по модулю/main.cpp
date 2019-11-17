#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    else
    {
        ll k = a / b, x1, y1;
        ll g = gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - k * y1;
        return g;
    }
}

int main()
{
    ll a, m, x, y;
    scanf("%I64d %I64d", &a, &m);
    if (gcd(a, m, x, y) == 1)
        printf("%I64d", (x % m + m) % m);
    else
        printf("-1");
    return 0;
}
