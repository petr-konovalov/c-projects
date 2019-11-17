#include <bits/stdc++.h>
#include <stdlib.h>

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

const int N = 1e5 + 7, INF = 1e9 + 7, M = 10;
const ll MOD = (ll)1e18 + 3;

ll n;
string ans;
set<ll> s[10];
map<ll, string> m;
ll p10[11];

string toString(ll num)
{
    string res;
    while (num)
    {
        res.pb((char)(num % 10 + '0'));
        num /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int getLen(ll num)
{
    int res = 0;

    while (num)
    {
        ++res;
        num /= 10;
    }

    return res;
}

void relax(ll x, string str)
{
    if (x > n || getLen(x) <= str.length())
        return;

    if (m.count(x) && str.length() >= m[x].length())
        return;

    s[m[x].length()].erase(x);
    m[x] = str;
    s[m[x].length()].insert(x);
}

string get(ll x)
{
    if (m.count(x))
        return m[x];
    return toString(x);
}

void generatePowers()
{
    for (ll x = 2; x * x <= n; ++x)
    {
        ll c = x * x;
        int deg = 2;
        while (c <= n)
        {
            relax(c, toString(x) + "^" + toString(deg));
            c *= x;
            ++deg;
        }
    }
}

void generatePowerAndPower(int maxLen)
{
    for (int i = 1; i < maxLen; ++i)
        for (int j = i; i + j + 1 <= maxLen; ++j)
        {
            for (ll x: s[i])
                for (ll y: s[j])
                    relax(x * y, get(x) + "*" + get(y));
        }
}

void generatePowerAndNumber(int maxLen)
{
    for (int i = 1; i + 2 <= maxLen; ++i)
        for (ll x: s[i])
            for (ll y = 2; y < p10[maxLen - i - 1]; ++y)
                relax(x * y, toString(y) + "*" + get(x));
}

void relaxAns(string str)
{
    if (str.length() < ans.length())
        ans = str;
}

void calcAns(int maxLen)
{
    for (int i = 1; 2 * i < maxLen; ++i)
    {
        for (ll x: s[i])
        {
            ll y = n - x;
            relaxAns(get(x) + "+" + get(y));
            if (n % x == 0)
                relaxAns(get(x) + "*" + get(n / x));
        }
        for (ll x = 1; x < p10[i]; ++x)
        {
            ll y = n - x;
            relaxAns(toString(x) + "+" + get(y));
            if (n % x == 0)
                relaxAns(toString(x) + "*" + get(n / x));
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    p10[0] = 1;
    for (int i = 1; i <= 10; ++i)
        p10[i] = p10[i - 1] * 10;

    cin >> n;

    generatePowers();
    generatePowerAndPower(7);
    generatePowerAndNumber(7);

    ans = get(n);

    calcAns(getLen(n));
    cout << ans;

    return 0;
}
