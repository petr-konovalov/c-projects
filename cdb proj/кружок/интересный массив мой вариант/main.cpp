#include <bits/stdc++.h>

using namespace std;

int a[100010];
pair<int, int> t[400010];
int z[100010];
bool res = true;
int n, m;

void push(int v)
{
    t[v * 2] = t[v];
    t[v * 2 + 1] = t[v];
    t[v].first = 0;
    t[v].second = 0;
    ++z[t[v].second];
}

void add(int v, int l, int r, int tl, int tr, int q, int nz)
{
    if (l > r)
        return;
    if (tl == l && tr == r)
    {
        printf("%i %i %i\n", v, t[v].first, t[v].second);
        if (t[v].first & q != t[v].first)
        {
            --z[t[v].second];
            t[v].first = q;
            t[v].second = nz;
            ++z[nz];
        }
    }
    else
    {
        push(v);
        int mid = (tl + tr) / 2;
        add(v * 2, l, min(mid, tr), tl, mid, q, nz);
        add(v * 2 + 1, max(mid + 1, l), r, mid + 1, tr, q, nz);
    }
}

int main()
{
    scanf("%i %i", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int l, r, q;
        scanf("%i %i %i", &l, &r, &q);
        add(1, l, r, 1, n, q, i);
    }
    for (int i = 1; i <= m && res; ++i)
        res = res & z[i] > 0;
    printf(res ? "YES": "NO");
    return 0;
}
