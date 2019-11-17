#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define F first
#define S second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e6 + 7, INF = 1e9 + 7;
const ll INF64 = 1e18;

int n, k;
bool dir[2 * N];
int rev[2 * N];
ll ans = 0;
int lcnt;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k;
    forn (i, k)
    {
        int pos;
        cin >> pos;
        --pos;
        rev[pos] = i + 1;
    }
    ll cur = 0;
    forn (i, 2 * n)
    {
        if (rev[i] != 0)
        {
            int ldist = i, rdist = 2 * n - i;
            dir[rev[i]] = ldist < rdist;
            if (dir[rev[i]])
                ++lcnt;
            cur += min(ldist, rdist);
        }
    }
    ans = cur;

    forn (i, 2 * n)
    {
        ans = min(ans, cur);
        int id = rev[i];
        forn (k, 2)
        {
            if (id != 0)
            {
                if (dir[id])
                    --lcnt;
                else
                    ++lcnt;
                dir[id] = !dir[id];
            }
            id = rev[(i + n) % (2 * n)];
        }
        cur += k - 2 * lcnt;
    }

    cout << ans;

    return 0;
}
