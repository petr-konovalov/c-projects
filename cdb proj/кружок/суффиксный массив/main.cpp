#include <bits/stdc++.h>

using namespace std;

int *getSuffArr(char *s)
{
    int len = strlen(s) + 1;
    int *a = new int[len];
    int c[len];
    int cnt[max(len, 256)];

    for (int i = 0; i < 256; ++i)
        cnt[i] = 0;
    for (int i = 0; i < len; ++i)
        ++cnt[s[i]];
    for (int i = 1; i < 256; ++i)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < len; ++i)
        a[--cnt[s[i]]] = i;

    int classes = 1;
    c[a[0]] = 0;
    for (int i = 1; i < len; ++i)
    {
        if (s[a[i]] != s[a[i - 1]])
            ++classes;
        c[a[i]] = classes - 1;
    }

    for (int k = 1; k <= len; k <<= 1)
    {
        int na[len];
        for (int i = 0; i < len; ++i)
        {
            na[i] = a[i] - k;
            if (na[i] < 0)
                na[i] += len;
        }
        for (int i = 0; i < classes; ++i)
            cnt[i] = 0;
        for (int i = 0; i < len; ++i)
            ++cnt[c[i]];
        for (int i = 1; i < classes; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = len - 1; i >= 0; --i)
            a[--cnt[c[na[i]]]] = na[i];
        int nc[len];
        classes = 1;
        nc[a[0]] = 0;
        for (int i = 1; i < len; ++i)
        {
            if (c[a[i]] != c[a[i - 1]] || c[(a[i] + k) % len] != c[(a[i - 1] + k) % len])
                ++classes;
            nc[a[i]] = classes - 1;
        }
        for (int i = 0; i < len; ++i)
            c[i] = nc[i];
    }
    --len;
    for (int i = 0; i < len; ++i)
        a[i] = a[i + 1];
    return a;
}

int *buildLCP(char *str, int *suf)
{
    int len = strlen(str);
    int *lcp = new int[len - 1];
    int pos[len];
    for (int i = 0; i < len; ++i)
        pos[suf[i]] = i;
    for (int l = 0, r = 0; l < len; ++l)
    {
        r = max(l, r);
        if (pos[l] < len - 1)
        {
            int k = suf[pos[l] + 1];
            for (;r < len && r - l + k < len && str[r] == str[r - l + k]; ++r);
            lcp[pos[l]] = r - l;
        }
    }
    return lcp;
}

int main()
{
    char s[100001];
    int k;
    cin >> s;
    cin >> k;
    int *suf = getSuffArr(s);
    int *lcp = buildLCP(s, suf);
    bool res = true;
    for (int i = 0; s[i + 1] != '\0' && res; ++i)
    {
        if (lcp[i] >= k)
        {
            s[suf[i] + k] = '\0';
            cout << s + suf[i];
            res = false;
        }
    }
    if (res)
        cout << "NONE";
    delete[] suf;
    delete[] lcp;
    return 0;
}
