#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define ins insert
#define ers erase
#define rank rank18234

const int N = 1e2 + 7, INF = 1e9 + 7;

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<db, db> pdd;
typedef pair<ll, ll> pll;

int n, m;
int ttb[N];
int c[N];
int d[N];
int s[N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    forn (i, m)
    {
        cin >> s[i] >> d[i] >> c[i];
        ttb[d[i]] = m + 1;
    }

    for (int i = 1; i <= n; ++i)
    {
        int cur = -1;
        int curd = INF;
        if (ttb[i] != 0)
        {
            forn (j, m)
                if (d[j] <= i && c[j] > 0)
                {
                    cout << -1;
                    return 0;
                }
            continue;
        }
        for (int j = 0; j < m; ++j)
        {
            if (s[j] <= i && i < d[j] && c[j] > 0 && curd > d[j])
            {
                curd = d[j];
                cur = j;
            }
        }
        if (cur != -1)
            --c[cur];
        ttb[i] = cur + 1;
    }
    for (int i = 1; i <= n; ++i)
        cout << ttb[i] << ' ';

    return 0;
}
