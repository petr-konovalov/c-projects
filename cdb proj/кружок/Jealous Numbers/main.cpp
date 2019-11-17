#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll a, b, p, q;

ll cnt(ll a, ll b, ll x, ll y = 1)
{
    return b / y / x - (a - 1) / y / x;
}

ll cnt(ll dp, ll dq)
{
    ll cur = dp * dq;
    return cnt(a, b, cur) - cnt(a, b, cur, p) - cnt(a, b, cur, q) + cnt(a, b, cur, p * q);
}

/*
int alpha(int n, int x)
{
    int k = 0;
    while (n % x == 0)
    {
        ++k;
        n /= x;
    }
    return k;
}

ll getAns()
{
    ll res = 0;
    for (int i = a; i <= b; ++i)
        if (alpha(i, p) > alpha(i, q))
            ++res;
    return res;
}
*/

int main()
{
    cin >> a >> b >> p >> q;
    ll res = 0;
    ll dp = 1;
    for (int i = 0; ; ++i)
    {
        ll dq = 1;
        for (int j = 0; j < i; ++j)
        {
            res += cnt(dp, dq);
            if (dq * dp > b / q)
                break;
            dq *= q;
        }
        if (dp > b / p)
            break;
        dp *= p;
    }
    cout << res << endl;
    return 0;
}
