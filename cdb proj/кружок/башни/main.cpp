
#include <bits/stdc++.h>

using namespace std;

int c[20][65536];
int h = 0;

int *getSuffArr(int *arr, const int n)
{
    int *a = new int[n];
    int cnt[max(n, 101)];

    for (int i = 0; i <= 100; ++i)
        cnt[i] = 0;
    for (int i = 0; i < n; ++i)
        ++cnt[arr[i]];
    for (int i = 1; i <= 100; ++i)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i)
        a[--cnt[arr[i]]] = i;

    int classes = 1;
    c[0][a[0]] = 0;
    for (int i = 1; i < n; ++i)
    {
        if (arr[a[i]] != arr[a[i - 1]])
            ++classes;
        c[0][a[i]] = classes - 1;
    }

    for (int k = 1; k <= n; k <<= 1, ++h)
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
        for (int i = 1; i < classes; ++i)
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

    return a;
}

int getEqualPrefSize(int *arr, int n, int l, int r)
{
    int k = 0;

    for (int d = h; d >= 0; --d)
        if (c[d][(l + k) % n] == c[d][(r + k) % n])
            k += 1 << d;

    return min(k, n);
}

int *buildLCP(int *arr, int n, int *suf)
{
    int e = n - 1;
    int *lcp = new int[e];

    for (int i = 0; i < e; ++i)
        lcp[i] = getEqualPrefSize(arr, n, suf[i], suf[i + 1]);

    return lcp;
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    int *suf = getSuffArr(arr, n);
    int *lcp = buildLCP(arr, n, suf);
    long long res = 0;
    for (int i = 0, e = n - 1; i < e; ++i)
        res += lcp[i];
    cout << res;
    delete[] suf;
    delete[] lcp;
    return 0;
}
