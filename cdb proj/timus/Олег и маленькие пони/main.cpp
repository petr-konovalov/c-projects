#include <iostream>
#include <stdio.h>

using namespace std;

unsigned long long wish[4000][2][16];
bool used[4000];
unsigned long long have[16];
int n, m;

bool subset(unsigned long long a[16], unsigned long long b[16])
{
    for (int i = 0; i < 16; ++i)
        if ((b[i] & a[i]) != b[i])
            return false;
    return true;
}

void update(unsigned long long a[16], unsigned long long b[16])
{
    for (int i = 0; i < 16; ++i)
        a[i] = a[i] | b[i];
}

int main()
{
    char c;
    scanf("%i %i", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        for (int k = 0; k < 2; ++k)
        {
            scanf(" ");
            for (int j = 0; j < n; ++j)
            {
                scanf("%c", &c);
                wish[i][k][j >> 6] |= ((1ll * (c == '1')) << (j & 63));
            }
        }
    }
    scanf(" ");
    for (int j = 0; j < n; ++j)
    {
        scanf("%c", &c);
        have[j >> 6] |= ((1ll * (c == '1')) << (j & 63));
    }
    bool b = true;
    for (int j = 0; j < n && b; ++j)
    {
        b = false;
        for (int i = 0; i < m; ++i)
            if (!used[i] && subset(have, wish[i][0]))
            {
                update(have, wish[i][1]);
                used[i] = true;
                b = true;
            }
    }
    for (int i = 0; i < n; ++i)
        printf(((have[i >> 6] >> (i & 63)) & 1) ? "1" : "0");
    return 0;
}
