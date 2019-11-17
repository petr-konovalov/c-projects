#include <bits/stdc++.h>

using namespace std;

#define MAXSIZE 200000

typedef long long ll;
pair<ll, ll> t[MAXSIZE * 4 + 100];
ll a[MAXSIZE];
int n, m;

void build(int v, int tl, int tr)
{
    t[v].second = 0;
    if (tl == tr)
        t[v].first = a[tl];
    else
    {
        int m = (tl + tr) >> 1;
        build(v * 2, tl, m);
        build(v * 2 + 1, m + 1, tr);
        t[v].first = min(t[v * 2].first, t[v * 2 + 1].first);
    }
}

void push(int v)
{
    t[v * 2].first += t[v].second;
    t[v * 2 + 1].first += t[v].second;
    t[v * 2].second += t[v].second;
    t[v * 2 + 1].second += t[v].second;
    t[v].second = 0;
}

void add(int v, int l, int r, int tl, int tr, ll d)
{
    if (tl == l && tr == r)
    {
        t[v].second += d;
        t[v].first += d;
    }
    else
    {
        push(v);
        int m = (tl + tr) >> 1;
        if (r <= m)
            add(v * 2, l, r, tl, m, d);
        else if (l > m)
            add(v * 2 + 1, l, r, m + 1, tr, d);
        else
        {
            add(v * 2, l, m, tl, m, d);
            add(v * 2 + 1, m + 1, r, m + 1, tr, d);
        }
        t[v].first = min(t[v * 2].first, t[v * 2 + 1].first);
    }
}

ll rmq(int v, int l, int r, int tl, int tr)
{
    if (tl == l && tr == r)
        return t[v].first;
    else
    {
        push(v);
        int m = (tl + tr) >> 1;
        if (r <= m)
            return rmq(v * 2, l, r, tl, m);
        else if (l > m)
            return rmq(v * 2 + 1, l, r, m + 1, tr);
        else
            return min(rmq(v * 2, l, m, tl, m), rmq(v * 2 + 1, m + 1, r, m + 1, tr));
    }
}

void getOperation()
{
    char in[128];
    int l, r;
    ll v;
    bool state = false;
    scanf(" ");
    fgets(in, 127, stdin);
    if (sscanf(in, "%i %i %I64d", &l, &r, &v) == 3)
    {
        if (l <= r)
            add(1, l, r, 0, n - 1, v);
        else
        {
            add(1, 0, r, 0, n - 1, v);
            add(1, l, n - 1, 0, n - 1, v);
        }
    }
    else
    {
        if (l <= r)
            printf("%I64d\n", rmq(1, l, r, 0, n - 1));
        else
            printf("%I64d\n", min(rmq(1, 0, r, 0, n - 1), rmq(1, l, n - 1, 0, n - 1)));
    }
}

int main()
{
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
        scanf("%I64d", a + i);
    build(1, 0, n - 1);
    scanf("%i", &m);
    for (int i = 0; i < m; ++i)
        getOperation();
    return 0;
}
