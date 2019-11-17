#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < n; ++i)
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int INF = 1000000000;
const int N = 2000;

int a[N] = {0};

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(false);
    cout.tie(false);

    int n;
    cin >> n;
    int onec = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        if (a[i] == 1)
            ++onec;
    }
    if (onec > 0)
    {
        cout << n - onec;
        return 0;
    }
    int mlen = INF;
    for (int i = 0; i < n; ++i)
        for (int len = 1; i + len < n; ++len)
            if (len < mlen && gcd(a[i], a[i + len]) == 1)
                mlen = len;
    if (mlen == INF)
        cout << -1;
    else
        cout << n + mlen - 1;
    return 0;
}
