#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 9;
char s[N];

int *makeSuff(char *s, int n)
{
    int cnt[N] = {0};
    ++n;
    int *a = new int[n];
    int c[n] = {0};
    for (int i = 0; i < n; ++i)
        ++cnt[s[i]];
    for (int i = 1; i < 255; ++i)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i)
        a[--cnt[s[i]]] = i;
    int classes = 1;
    c[a[0]] = 0;
    for (int i = 1; i < n; ++i)
    {
        if (s[a[i]] != s[a[i - 1]])
            ++classes;
        c[a[i]] = classes - 1;
    }
    for (int h = 1; h < n; h <<= 1)
    {
        int na[n];
        for (int i = 0; i < n; ++i)
        {
            na[i] = a[i] - h;
            if (na[i] < 0)
                na[i] += n;
        }
        for (int i = 0; i < classes; ++i)
            cnt[i] = 0;
        for (int i = 0; i < n; ++i)
            ++cnt[c[i]];
        for (int i = 1; i < classes; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i)
            a[--cnt[c[na[i]]]] = na[i];
        int nc[n];
        classes = 1;
        nc[a[0]] = 0;
        for (int i = 1; i < n; ++i)
        {
            if (c[a[i]] != c[a[i - 1]] || c[(a[i] + h) % n] != c[(a[i - 1] + h) % n])
                ++classes;
            nc[a[i]] = classes - 1;
        }
        for (int i = 0; i < n; ++i)
            c[i] = nc[i];
    }
    return a;
}

int pos[N];

int *getLcp(char *s, int *a, int n)
{
    int *lcp = new int[n];
    for (int i = 1; i <= n; ++i)
        pos[a[i]] = i;
    int k = 0;
    for (int i = 0; i < n; ++i)
    {
        if (k > 0)
            --k;
        if (pos[i] == n)
            k = 0;
        else
        {
            int j = a[pos[i] + 1];
            while (j + k < n && i + k < n && s[i + k] == s[j + k])
                ++k;
            lcp[pos[i]] = k;
        }
    }

    return lcp;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> s;
    int n = strlen(s);
    int *a = makeSuff(s, n);
    int *lcp = getLcp(s, a, n);
    int res = ((n * (n + 1)) >> 1);
    for (int i = 1; i < n; ++i)
        res -= lcp[i];
    cout << res;
    delete[] lcp;
    delete[] a;
    return 0;
}
