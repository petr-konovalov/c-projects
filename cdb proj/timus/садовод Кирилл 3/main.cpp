#include <iostream>
#include <cmath>

using namespace std;

void quickSort(long long *a, const int l, const int r)
{
    int p = a[(l + r) / 2];
    int i = l;
    int j = r;
    while (i < j)
    {
        while (a[i] < p)
            ++i;
        while (a[j] > p)
            --j;
        if (i <= j)
        {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        quickSort(a, i, r);
    if (l < j)
        quickSort(a, l, j);
}

void deleteReplays(long long *a, int &n)
{
    int j = 0;
    for (int i = 1; i < n; ++i)
    {
        if (a[i - 1] != a[i])
            a[++j] = a[i];
    }
    n = j + 1;
}

int pos(long long *b, long long a, int len)
{
    int l = 0;
    int r = len;
    while ((r - l) > 1)
    {
        int m = (l + r) / 2;
        if (b[m] <= a)
            l = m;
        else
            r = m;
    }
    return l;
}

long long a[100000] = {0};
long long b[100000] = {0};
long long c[100000] = {0};
int l[100000] = {0};
int r[100000] = {0};
long long ml[100000] = {0};
long long mr[100000] = {0};

int main()
{
    long long infinity = 1;
    infinity <<= 62;
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        c[i] = 0;
        cin >> a[i];
        b[i] = a[i];
        l[i] = -1;
        r[i] = -1;
    }
    quickSort(b, 0, n - 1);
    int m = n;
    deleteReplays(b, m);
    for (int i = 0; i < n; ++i)
    {
        int j = pos(b, a[i], m);
        ++c[j];
        if (l[j] == -1)
            l[j] = i;
        if (r[j] < i)
            r[j] = i;
    }
    mr[0] = c[0] + r[0];
    ml[0] = mr[0] + r[0] - l[0];
    for (int i = 1; i < m; ++i)
    {
        int h = r[i] - l[i] + c[i];
        ml[i] = ml[i - 1] + abs(l[i - 1] - r[i]) + h;
        mr[i] = ml[i - 1] + abs(l[i - 1] - l[i]) + h;
        if (mr[i - 1] + abs(r[i - 1] - r[i]) + h < ml[i])
            ml[i] = mr[i - 1] + abs(r[i - 1] - r[i]) + h;
        if (mr[i - 1] + abs(r[i - 1] - l[i]) + h < mr[i])
            mr[i] = mr[i - 1] + abs(r[i - 1] - l[i]) + h;
    }
    cout << min(ml[m - 1], mr[m - 1]);
    return 0;
}
