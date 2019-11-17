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

const int N = 1e2 + 7, INF = 1e9 + 7;
const ll INF64 = (ll)1e18 + 3;

int n, m;

int cnt[N];
int c[N];
int ans = INF;

void addHuman()
{
    int minId = -1, minv = -1;
    for (int i = 0; i < N; ++i)
        if (cnt[i] != 0 && cnt[i] / (c[i] + 1) > minv)
        {
            minId = i;
            minv = cnt[i] / (c[i] + 1);
        }
    ++c[minId];
    ans = minv;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    forn (i, m)
    {
        int a;
        cin >> a;
        ++cnt[a];
    }

    forn (i, n)
        addHuman();

    cout << ans;

    return 0;
}
