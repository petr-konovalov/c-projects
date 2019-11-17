#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define X first
#define Y second

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e6 + 7, MOD = 998244353, M1 = 1e9 + 7, M2 = 1e9 + 9;

struct Hash
{
    ll x1, x2;

    Hash(): x1(0), x2(0){};
    Hash(ll x1, ll x2): x1(x1), x2(x2){};

    Hash operator+(const Hash &h) const
    {
        Hash res(x1 + h.x1, x2 + h.x2);
        if (res.x1 >= M1)
            res.x1 -= M1;
        if (res.x2 >= M2)
            res.x2 -= M2;
        return res;
    }

    Hash operator-(const Hash &h) const
    {
        Hash res(x1 - h.x1, x2 - h.x2);
        if (res.x1 < 0)
            res.x1 += M1;
        if (res.x2 < 0)
            res.x2 += M2;
        return res;
    }

    Hash operator*(const Hash &h) const
    {
        return Hash((x1 * h.x1) % M1, (x2 * h.x2) % M2);
    }

    bool operator==(const Hash &h) const
    {
        return x1 == h.x1 && x2 == h.x2;
    }

    bool operator!=(const Hash &h) const
    {
        return x1 != h.x1 || x2 != h.x2;
    }
};

Hash P[N];

struct HashStr
{
    string str;
    vector<Hash> h;

    void buildHash()
    {
        h.reserve(str.size());
        Hash curHash;
        for (char c: str)
        {
            curHash = curHash * P[1] + Hash(c, c);
            h.pb(curHash);
        }
    }

    HashStr()
    {

    }

    Hash getHash(int l, int r) const
    {
        Hash res = h[r];
        if (l > 0)
            res = res - h[l - 1] * P[r - l + 1];
        return res;
    }

    void read()
    {
        cin >> str;
        buildHash();
    }

    int size() const
    {
        return str.size();
    }

    char operator[](int i) const
    {
        return str[i];
    }
};

void buildP(int seed = 2731)
{
    P[0] = Hash(1, 1);
    P[1] = Hash(seed, seed);
    for (int i = 2; i < N; ++i)
        P[i] = P[i - 1] * P[1];
}

HashStr a, lf, rg;
int nPos[N];

int comp(const HashStr &a, const HashStr &x, int pos)
{
    int l = 0, r = x.size();

    while (r - l > 1)
    {
        int m = (l + r) >> 1;
        if (a.getHash(pos, pos + m - 1) == x.getHash(0, m - 1))
            l = m;
        else
            r = m;
    }

    return a[pos + r - 1] == x[r - 1] ? 0: a[pos + r - 1] < x[r - 1] ? -1: 1;
}

int getRes(const HashStr &a, const HashStr &x, const HashStr &y)
{
    vector<int> dp(a.size() + 1);
    vector<int> sumdp(a.size() + 1);
    dp[0] = 1;
    sumdp[0] = -1;

    int l = 0;
    int r = -1;
    forn (i, a.size())
    {
        l = max(l, i - x.size() + 1);
        if (i - l + 1 == x.size() && comp(a, x, i - x.size() + 1) == 1)
            ++l;
        while (l < i && a[l] == '0')
            ++l;

        int nr = r == -1 ? 0: min(nPos[r], i);
        while (i - nr + 1 > y.size() || i - nr + 1 == y.size() && comp(a, y, i - y.size() + 1) >= 0)
        {
            r = nr;
            nr = nPos[r];
        }

        if (l <= r)
            dp[i + 1] = ((ll)sumdp[r] - sumdp[l] + MOD + dp[r]) % MOD;

        if (a[i] != '0')
            sumdp[i + 1] = ((ll)sumdp[i] + dp[i]) % MOD;
        else
            sumdp[i + 1] = sumdp[i];
    }

    return dp[a.size()];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    buildP();
    a.read();
    lf.read();
    rg.read();

    int curn = a.size();
    for (int i = a.size() - 1; i >= 0; --i)
    {
        nPos[i] = curn;
        if (a[i] != '0')
            curn = i;
    }

    cout << getRes(a, rg, lf);

    return 0;
}
