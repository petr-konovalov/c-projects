#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)

const int base = 1e9;
const int MAXD = 50;
const int mSize = 64;

typedef vector<int> LNum;
typedef long long ll;

void div(LNum &a, int b)
{
    LNum ans = LNum(a.size());
    int ost = 0;
    for (int i = (int)a.size() - 1; i >= 0; --i)
    {
        ll cur = (ll)ost * base + a[i];
        a[i] = cur / b;
        ost = cur % b;
    }
    while (a.size() >= 1 && a.back() == 0)
        a.pop_back();
}

LNum getL()
{
    string s;
    cin >> s;
    LNum ans;

    int i = s.length();
    for (; i >= 9; i -= 9)
    {
        ans.push_back(atoi(s.substr(i - 9, 9).c_str()));
    }
    if (i > 0)
        ans.push_back(atoi(s.substr(0, i).c_str()));

    return ans;
}

int m;
int sz;
int matr[mSize][mSize];
int mod;

void mulMatr(int res[mSize][mSize], int m1[mSize][mSize], int m2[mSize][mSize])
{
    for (int i = 0; i < sz; ++i)
        for (int j = 0; j < sz; ++j)
        {
            ll val = 0;
            for (int k = 0; k < sz; ++k)
                val += (ll)m1[i][k] * m2[k][j];
            res[i][j] = val % mod;
        }
}

void cpy(int dest[mSize][mSize], int source[mSize][mSize])
{
    forn (i, mSize)
    forn (j, mSize)
        dest[i][j] = source[i][j];
}

void binPow(LNum deg)
{
    int res[mSize][mSize];
    int buf[mSize][mSize];
    for (int i = 0; i < sz; ++i)
        res[i][i] = 1;
    while (deg.size() > 0)
    {
        if (deg[0] & 1)
        {
            mulMatr(buf, res, matr);
            cpy(res, buf);
        }
        mulMatr(buf, matr, matr);
        cpy(matr, buf);
        div(deg, 2);
    }
    cpy(matr, res);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    LNum n = getL();
    int i = 0;
    while (n[i] == 0)
    {
        n[i] = base - 1;
        ++i;
    }
    --n[i];
    while (n.size() >= 1 && n.back() == 0)
        n.pop_back();

    cin >> m >> mod;
    sz = 1 << m;

    forn (m1, sz)
        forn (m2, sz)
        {
            int b1 = m1, b2 = m2;
            bool res = true;
            for (int i = 2; i <= m && res; ++i)
            {
                if ((b1 & 3) == (b2 & 3) && ((b1 & 3) == 0 || (b1 & 3) == 3))
                    res = false;
                b1 >>= 1;
                b2 >>= 1;
            }
            matr[m1][m2] = res ? 1: 0;
        }
    binPow(n);
    ll ans = 0;
    forn (i, sz)
    {
        forn (j, sz)
        {
            //debug("%i ", matr[i][j]);
            ans += matr[i][j];
        }
        //debug("\n");
    }
    cout << ans % mod;
    return 0;
}
