#include <bits/stdc++.h>

using namespace std;

int t[1000100];
int in[1000100];
int a[1000100];
int n;

void add(int i)
{
    for (; i < n; i |= i + 1)
        t[i] += 1;
}

int get(int i)
{
    int res = 0;
    --i;
    for(; i >= 0; i = (i & (i + 1)) - 1)
        res += t[i];
    return res;
}

int main()
{
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
        scanf("%i", in + i);
    map<int, int> cnt;
    for (int i = 0; i < n; ++i)
    {
        int cur = ++cnt[in[i]];
        a[i] = cur;
    }
    cnt.clear();
    long long res = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        res += get(a[i]);
        add(++cnt[in[i]]);
    }
    cnt.clear();
    printf("%I64d", res);
    return 0;
}
