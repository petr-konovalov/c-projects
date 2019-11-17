#include <bits/stdc++.h>

using namespace std;

#define LEN 65536 * 2

int c[20][LEN];
char s[LEN];
int n;
int Log[LEN];
int cnt[LEN];

void getSuf()
{
    int a[n];
    for (int i = 0; i < 256; ++i)
        cnt[i] = 0;
    for (int i = 0; i < n; ++i)
        ++cnt[s[i]];
    for (int i = 1; i < 256; ++i)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i)
        a[--cnt[s[i]]] = i;
    c[0][a[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; ++i)
    {
        if (s[a[i]] != s[a[i - 1]])
            ++classes;
        c[0][a[i]] = classes - 1;
    }

    for (int h = 0, k; (k = 1 << h) < n; ++h)
    {
        int na[n];
        for (int i = 0; i < n; ++i)
        {
            na[i] = a[i] - k;
            if (na[i] < 0)
                na[i] += n;
        }
        for (int i = 0; i < classes; ++i)
            cnt[i] = 0;
        for (int i = 0; i < n; ++i)
            ++cnt[c[h][i]];
        for (int i = 1; i < n; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i)
            a[--cnt[c[h][na[i]]]] = na[i];
        c[h + 1][a[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; ++i)
        {
            if (c[h][a[i]] != c[h][a[i - 1]] || c[h][(a[i] + k) % n] != c[h][(a[i - 1] + k) % n])
                ++classes;
            c[h + 1][a[i]] = classes - 1;
        }
    }
}

bool compSubStr(int A, int B, int C, int D)
{
    int k = B - A;
    if (k != D - C)
        return false;
    while (k > 0)
    {
        int d = Log[k];
        if (c[d][B - k] != c[d][D - k])
            return false;
        else
            k -= 1 << d;
    }
    return c[0][B] == c[0][D];
}

int main()
{
    for (int i = 0, j = 0; i < LEN; ++i)
    {
        if (1 << (j + 1) <= i)
            ++j;
        Log[i] = j;
    }
    scanf("%s", s);
    n = strlen(s);
    getSuf();
    int M;
    scanf("%i", &M);
    for (int i = 0; i < M; ++i)
    {
        int A, B, C, D;
        scanf("%i %i %i %i", &A, &B, &C, &D);
        --A;--B;--C;--D;
        printf(compSubStr(A, B, C, D) ? "Yes\n" : "No\n");
    }
    return 0;
}
