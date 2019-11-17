#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)

const int N = 2e5 + 7;

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

int n, m;
int arr[N];
int x[N];
int cnt[2 * N];

ll greaterCount(int m)
{
    ll res = 0;
    forn (i, n)
        x[i] = arr[i] >= m ? 1: -1;

    int sum = 0;
    int gr = 0;

    forn (i, 2 * N)
        cnt[i] = 0;
    cnt[N] = 1;

    forn (i, n)
    {
        if (x[i] == 1)
            gr += cnt[N + sum];
        else
            gr -= cnt[N + sum - 1];
        gr = max(gr, 0);
        sum += x[i];
        ++cnt[N + sum];
        res += gr;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    forn (i, n)
        cin >> arr[i];

    cout << greaterCount(m) - greaterCount(m + 1);

    return 0;
}
