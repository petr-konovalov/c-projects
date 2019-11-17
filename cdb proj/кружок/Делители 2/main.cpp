#include <bits/stdc++.h>

using namespace std;

const long long primes[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
long long res;
long long num;
long long n;

void rec(int m, int mincnt, long long cnt, long long cur)
{
    if (m < 15)
    {
        if (cnt > res || cnt == res && cur < num)
        {
            num = cur;
            res = cnt;
        }
        for (int i = 1; i <= mincnt; ++i)
            if (n / primes[m] >= cur)
            {
                cur = cur * primes[m];
                rec(m + 1, i, cnt * (i + 1), cur);
            }
    }
}

int main()
{
    cin >> n;
    rec(0, 15, 1, 1);
    cout << res << " " << num;
    return 0;
}
