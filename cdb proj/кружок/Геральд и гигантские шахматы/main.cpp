#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

int binPow(int a, int b)
{
    int res = 1;

    while (b)
    {
        if (b & 1)
            res = (res * 1ll * a) % MOD;
        a = (a * 1ll * a) % MOD;
        b >>= 1;
    }

    return res;
}

int fact[200010];
int rfact[200010];

int C(int n, int k)
{
    return (fact[n] * 1ll * rfact[k] % MOD) * rfact[n - k] % MOD;
}

struct Point
{
    int x;
    int y;
};

bool operator< (const Point &p1, const Point &p2)
{
    return p1.y < p2.y || p1.y == p2.y && p1.x < p2.x;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    fact[0] = 1;
    rfact[0] = 1;
    for (int i = 1; i < 200010; ++i)
    {
        fact[i] = (fact[i - 1] * 1ll * i) % MOD;
        rfact[i] = binPow(fact[i], MOD - 2);
    }
    int h, w, n;
    cin >> h >> w >> n;
    --h;
    --w;
    vector<Point> pnt(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> pnt[i].x >> pnt[i].y;
        --pnt[i].x;
        --pnt[i].y;
    }
    sort(pnt.begin(), pnt.end());
    int d[2000];
    for (int i = 0; i < n; ++i)
    {
        d[i] = C(pnt[i].x + pnt[i].y, pnt[i].x);
        for (int j = 0; j < i; ++j)
            if (pnt[j].x <= pnt[i].x)
                d[i] = ((d[i] - d[j] * 1ll *
                         C(pnt[i].x + pnt[i].y - pnt[j].x - pnt[j].y, pnt[i].x - pnt[j].x) % MOD) + MOD) % MOD;
    }
    int res = C(h + w, h);
    for (int i = 0; i < n; ++i)
        res = ((res - d[i] * 1ll * C(h + w - pnt[i].x - pnt[i].y, h - pnt[i].x) % MOD) + MOD) % MOD;
    cout << res;
    return 0;
}
