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
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;
typedef pair<int, int> pii;

const int N = 1e5 + 7, INF = 1e9 + 7;

int calcBalance(string str)
{
    int cntOp = 0;
    int cntCl = 0;
    for (char c: str)
    {
        if (c == '(')
            ++cntOp;
        else
        {
            if (cntOp > 0)
                --cntOp;
            else
                ++cntCl;
        }
    }

    if (cntOp > 0 && cntCl > 0)
        return INF;
    else
        return cntOp - cntCl;
}

int n;
multiset<int> bls;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    int ans = 0;
    forn (i, n)
    {
        string str;
        cin >> str;
        int balance = calcBalance(str);
        if (balance == INF)
            continue;

        auto fndRes = bls.find(-balance);
        if (fndRes != bls.end())
        {
            bls.erase(fndRes);
            ++ans;
        }
        else
        {
            bls.insert(balance);
        }
    }
    cout << ans;

    return 0;
}
