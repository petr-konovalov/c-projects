#include <bits/stdc++.h>

using namespace std;

#define MAXSIZE 100000

typedef long long ll;

struct Node
{
    int maxv;
    ll sum;
};

Node t[MAXSIZE * 4 + 100];
int a[MAXSIZE];

int build(int v, int tl, int tr)
{
    if (tl == tr)
    {
        t[v].sum = a[tl];
        t[v].maxv = a[tl];
    }
    else
    {
        int m = (tl + tr) >> 1;
        build(v * 2, tl, m);
        build(v * 2 + 1, m + 1, tr);
        t[v].sum = t[v * 2].sum + t[v * 2 + 1].sum;
        t[v].maxv = max(t[v * 2].maxv, t[v * 2 + 1].maxv);
    }
}

void mod(int v, int l, int r, int tl, int tr, int x)
{
    if (t[v].maxv >= x)
    {
        if (tl == tr)
        {
            t[v].sum = t[v].sum % x;
            t[v].maxv = t[v].sum;
        }
        else
        {
            int m = (tl + tr) >> 1;
            if (r <= m)
                mod(v * 2, l, r, tl, m, x);
            else if (l > m)
                mod(v * 2 + 1, l, r, m + 1, tr, x);
            else
            {
                mod(v * 2, l, m, tl, m, x);
                mod(v * 2 + 1, m + 1, r, m + 1, tr, x);
            }
            t[v].sum = t[v * 2].sum + t[v * 2 + 1].sum;
            t[v].maxv = max(t[v * 2].maxv, t[v * 2 + 1].maxv);
        }
    }
}

void modify(int v, int id, int tl, int tr, int x)
{
    if (tl == id && tr == id)
    {
        t[v].maxv = x;
        t[v].sum = x;
    }
    else
    {
        int m = (tl + tr) >> 1;
        if (id <= m)
            modify(v * 2, id, tl, m, x);
        else
            modify(v * 2 + 1, id, m + 1, tr, x);
        t[v].sum = t[v * 2].sum + t[v * 2 + 1].sum;
        t[v].maxv = max(t[v * 2].maxv, t[v * 2 + 1].maxv);
    }
}

ll get(int v, int l, int r, int tl, int tr)
{
    if (l == tl && r == tr)
        return t[v].sum;
    else
    {
        int m = (tl + tr) >> 1;
        if (r <= m)
            return get(v * 2, l, r, tl, m);
        else if (l > m)
            return get(v * 2 + 1, l, r, m + 1, tr);
        else
            return get(v * 2, l, m, tl, m) + get(v * 2 + 1, m + 1, r, m + 1, tr);
    }
}

int main()
{
    int n, m;
    scanf("%i %i", &n, &m);
    for (int i = 0; i < n; ++i)
        scanf("%i", a + i);
    build(1, 0, n - 1);
    for (int i = 0; i < m; ++i)
    {
        int t, a, b, c;
        scanf("%i %i %i", &t, &a, &b);
        --a;
        switch (t)
        {
            case 1:
                --b;
                printf("%I64d\n", get(1, a, b, 0, n - 1));
                break;
            case 2:
                --b;
                scanf("%i", &c);
                mod(1, a, b, 0, n - 1, c);
                break;
            case 3:
                modify(1, a, 0, n - 1, b);
                break;
            default:
                break;
        }
    }
    return 0;
}
