#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define F first
#define S second

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int MOD = 1e9 + 7;
const int CNT_MASK = 1 << 20;

int n;
int sz;
int m;
int res[CNT_MASK];
int old[CNT_MASK];

bool checkMask(unsigned int mask)
{
    while (mask)
    {
        if ((mask & 1) && ((mask >> 1) & 1))
            mask &= ~(unsigned int)3;
        else if ((mask & 1) && !((mask >> 1) & 1))
            return false;
        mask >>= 1;
    }
    return true;
}

bool checkPairMask(unsigned int m1, unsigned int m2)
{
    if (!checkMask(m1 & m2))
        return false;
    for (int bit = 0; bit < n; ++bit)
        if ((m1 & (1 << bit)) == 0 && (m2 & (1 << bit)) == 0)
            return false;
    return true;
}

void getInitState(int n)
{
    for (int mask = 0; mask < sz; ++mask)
    {
        res[mask] = checkMask(mask);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    //cin >> n >> m;
    for (n = 1; n <= 20; ++n)
    {
        for (m = 1; m <= 20; ++m)
        {
            sz = 1 << n;
            getInitState(n);

            for (int i = 1; i < m; ++i)
            {
                for (int i = 0; i < sz; ++i)
                {
                    old[i] = res[i];
                    res[i] = 0;
                }
                for (int m1 = 0; m1 < sz; ++m1)
                    for (int m2 = 0; m2 < sz; ++m2)
                    {
                        if (checkPairMask(m1, m2))
                            res[m2] = (res[m2] + old[m1]) % MOD;
                    }
            }
            debug("%10i, ", res[sz - 1]);
            if ((n * 20 + m) % 6 == 0)
                debug("\n");
        }
    }

    return 0;
}
