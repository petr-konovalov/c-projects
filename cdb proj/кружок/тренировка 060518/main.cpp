#include <bits/stdc++.h>

using namespace std;

#define forn(i, n)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define F first
#define S second

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 31, M = 11;

int n, m;
int a[N];
int b[M];
int mb[M];
int cres = 0;
int mres = 1e9 + 7;

void rec(int k, int sum)
{
    int s = 0;
    if (k == m || sum == n)
    {
        b[k] = n - sum;
        for (int i = 1; sum + i <= n; ++i)
            s += a[sum + i] * i;
        if (mres > cres + s)
        {
            mres = cres + s;
            for (int i = 1; i <= m; ++i)
                mb[i] = b[i];
        }
        return;
    }
    for (int i = 1; sum + i <= n; ++i)
    {
        s += a[sum + i] * i;
        cres += a[sum + i] * i;
        b[k] = i;
        rec(k + 1, sum + i);
    }
    cres -= s;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    //freopen("sms.out", "w", stdout);
    //freopen("sms.in", "r", stdin);

    cin >> n >> m;


    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    rec(1, 0);
    for (int i = 1; i <= m; ++i)
        cout << mb[i] << ' ';

    return 0;
}
