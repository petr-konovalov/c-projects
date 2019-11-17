#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define X first
#define Y second

typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e6 + 7, K = 21, MOD = 1e9 + 7;

int n, k;
int a[N];
int tb[N][K];
int lg[N];

/*
int ordinary(vector<int> a)
{
    if (a.size() < k)
        return 0;
    else
    {
        vector<int> b(a.size() - k + 1);
        int ans = 0;
        for (int i = 0; i <= a.size() - k; ++i)
        {
            int temp = a[i];
            for (int j = i + 1; j < i + k; ++j)
                temp = max(temp, a[j]);
            b[i] = temp;
            ans += temp;
        }
        return ans + ordinary(b);
    }
}

int first()
{
    int ans = 0;
    for (int p = 1; p * (k - 1) + 1 <= n; ++p)
    {
        int len = p * (k - 1) + 1;
        for (int i = 0; i <= n - len; ++i)
        {
            int temp = a[i];
            for (int j = i + 1; j < i + len; ++j)
                temp = max(temp, a[j]);
            ans += temp;
        }
    }
    return ans;
}
*/

void makeTable()
{
    for (int i = 0; i < n; ++i)
        tb[i][0] = i;
    lg[1] = 0;
    for (int i = 2; i < N; ++i)
    {
        if (i >= (1 << (lg[i - 1] + 1)))
            lg[i] = lg[i - 1] + 1;
        else
            lg[i] = lg[i - 1];
    }
    for (int len = 1; len <= lg[n]; ++len)
    {
        int sz = 1 << (len - 1);
        for (int i = 0; i + 2 * sz <= n; ++i)
        {
            if (a[tb[i][len - 1]] > a[tb[i + sz][len - 1]])
                tb[i][len] = tb[i][len - 1];
            else
                tb[i][len] = tb[i + sz][len - 1];
        }
    }
}

int getMaxPos(int l, int r)
{
    int sz = lg[r - l + 1];
    return a[tb[l][sz]] > a[tb[r - (1 << sz) + 1][sz]] ? tb[l][sz]: tb[r - (1 << sz) + 1][sz];
}

int f(int l, int r)
{
    if (l > r)
        return 0;
    int s = (r - l) / (k - 1);
    return ((((ll)(r - l + 1) * s) % MOD - ((ll)(k - 1) * (1 + s) * s / 2) % MOD) + MOD) % MOD;
}

int g(int l, int y, int r)
{
    return ((f(l, r) - f(l, y - 1) - f(y + 1, r)) % MOD + MOD) % MOD;
}

int getAns(int l, int r)
{
    int pos = getMaxPos(l, r);
    int ans = ((ll)g(l, pos, r) * a[pos]) % MOD;
    if (l < pos)
        ans = (ans + getAns(l, pos - 1)) % MOD;
    if (pos < r)
        ans = (ans + getAns(pos + 1, r)) % MOD;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k;
    forn (i, n)
        cin >> a[i];
    makeTable();

    cout << getAns(0, n - 1);

    return 0;
}
