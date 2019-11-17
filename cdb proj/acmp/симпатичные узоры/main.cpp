#include <iostream>

using namespace std;

int t[16][128];

bool check(int n, int c1, int c2)
{
    for (int i = 1; i < n; c1 >>= 1, c2 >>= 1, ++i)
    {
        if ((c1 & 1) && (c2 & 1) && ((c1 >> 1) & 1) && ((c2 >> 1) & 1) ||
            !(c1 & 1)&& !(c2 & 1)&& !((c1 >> 1) & 1)&& !((c2 >> 1) & 1))
        return false;
    }
    return true;
}

int main()
{
    int m, n;
    cin >> m >> n;
    if (n > m)
        swap(m, n);
    if (n < 2)
    {
        cout << (1 << (m * n));
        return 0;
    }
    int maxc = 1 << n;
    for (int c = 0; c < maxc; ++c)
        t[0][c] = 1;
    for (int i = 1; i < m; ++i)
    {
        for (int c1 = 0; c1 < maxc; ++c1)
        {
            t[i][c1] = 0;
            for (int c2 = 0; c2 < maxc; ++c2)
                if (check(n, c1, c2))
                    t[i][c1] += t[i - 1][c2];
        }
    }
    int s = 0;
    for (int c = 0; c < maxc; ++c)
        s += t[m - 1][c];
    cout << s;
    return 0;
}
