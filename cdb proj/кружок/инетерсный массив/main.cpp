#include <bits/stdc++.h>

using namespace std;

int n, m;
int seg[30][100010];
int sum[30][100010];
int l[100000];
int r[100000];
bool z[100000][30];
bool bit[30][100010];

int main()
{
    scanf("%i %i", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        int q;
        scanf("%i %i %i", l + i, r + i, &q);
        for (int j = 0; j < 30; ++j, q >>= 1)
            if (q & 1)
            {
                z[i][j] = true;
                seg[j][l[i]] += 1;
                seg[j][r[i] + 1] -= 1;
            }
            else
                z[i][j] = false;
    }
    for (int i = 0; i < 30; ++i)
    {
        int state = 0;
        int s = 0;
        sum[i][0] = 0;
        for (int j = 1; j <= n; ++j)
        {
            state += seg[i][j];
            if (state == 0)
                bit[i][j] = false;
            else
            {
                bit[i][j] = true;
                ++s;
            }
            sum[i][j] = s;
        }
    }
    bool res = true;
    for (int i = 0; i < m && res; ++i)
    {
        for (int j = 0; j < 30 && res; ++j)
            if (!z[i][j] && sum[j][r[i]] - sum[j][l[i] - 1] == r[i] - l[i] + 1)
                res = false;
    }
    if (res)
    {
        printf("YES\n");
        for (int i = 1; i <= n; ++i)
        {
            int t = 0;
            for (int j = 0; j < 30; ++j)
                if (bit[j][i])
                    t += 1 << j;
            printf("%i ", t);
        }
    }
    else
        printf("NO");
    return 0;
}
