#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const ll MOD = 1e18;
const int N = 15;
const int M = 1 << 13;
const int ParCnt = 1e5;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

char board[N][N];
int bmask[N];
int h, w;
int sz;
vector<int> comb;
vector<pii> par;
vector<int> parr[M];
vector<pii> trip;
ll dp[N][ParCnt] = {0};

bool check()
{
    for (int x = 1; x <= h; ++x)
    {
        for (int y = 1; y <= w; ++y)
        {
            if (board[x][y] == 'B')
                continue;
            int cnt = 0;
            for (int d = 0; d < 4; ++d)
            {
                if (board[x + dx[d]][y + dy[d]] == 'B')
                    ++cnt;
            }
            if (cnt > 1)
                return false;
        }
    }
    return true;
}

ll getAns(int w, int h)
{
    int sz = 1 << (w * h);
    ll result = 0;
    for (int mask = 0; mask < sz; ++mask)
    {
        int m = mask;
        for (int x = 1; x <= h; ++x)
        {
            for (int y = 1; y <= w; ++y)
            {
                board[x][y] = (m & 1) ? 'B': '.';
                m >>= 1;
            }
        }
        if (check())
        {
            ++result;
        }
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> w >> h;
    //debug("%lli\n", getAns(w, h));
    sz = 1 << h;
    for (int i = 0; i < sz; ++i)
    {
        int c = i;
        int p = 0;
        bool res = true;
        for (int j = 0; j < h && res; ++j)
        {
            if ((c & 1) == 0 && p && ((c >> 1) & 1))
                res = false;
            p = c & 1;
            c >>= 1;
        }
        if (res)
            comb.pb(i);
    }
    //debug("%i\n", comb.size());
    for (int i: comb)
    {
        for (int j: comb)
        {
            int m1 = i;
            int m2 = j;
            int p1 = 0;
            int p2 = 0;
            bool res = true;
            for (int k = 0; k < h && res; ++k)
            {
                int b1 = m1 & 1;
                int b2 = m2 & 1;
                if (b1 && !b2 && (p2 || ((m2 >> 1) & 1)) || b2 && !b1 && (p1 || ((m1 >> 1) & 1)))
                    res = false;
                m1 >>= 1;
                m2 >>= 1;
                p1 = b1;
                p2 = b2;
            }
            if (res)
            {
                parr[i].pb(par.size());
                par.pb(mp(i, j));
            }
        }
    }

    for (int i = 0; i < par.size(); ++i)
    {
        for (int j: parr[par[i].S])
        {
            int m1 = par[i].F;
            int m2 = par[i].S;
            int m3 = par[j].S;
            bool res = true;
            for (int s = 0; s < h && res; ++s)
            {
                int b1 = m1 & 1;
                int b2 = m2 & 1;
                int b3 = m3 & 1;
                if (b1 == 1 && b2 == 0 && b3 == 1)
                    res = false;
                m1 >>= 1;
                m2 >>= 1;
                m3 >>= 1;
            }
            if (res)
                trip.pb(mp(i, j));
        }
    }

    forn (i, h)
    {
        forn (j, w)
        {
            cin >> board[i + 1][j + 1];
            //board[i + 1][j + 1] = '.';
        }
    }

    forn (i, 200)
        for (int x = 1; x <= h; ++x)
        {
            for (int y = 1; y <= w; ++y)
            {
                int cnt = 0;
                for (int d = 0; d < 4; ++d)
                {
                    if (board[x + dx[d]][y + dy[d]] == 'B')
                        ++cnt;
                }
                if (cnt > 1)
                    board[x][y] = 'B';
            }
        }

    for (int y = 1; y <= w; ++y)
    {
        int mask = 0;
        for (int x = 1; x <= h; ++x)
            mask |= (board[x][y] == 'B') << (x - 1);
        bmask[y - 1] = mask;
    }

    if (w == 1)
    {
        ll ans = 0;
        for (int i: comb)
            if (bmask[0] == (bmask[0] & i))
                ++ans;
        cout << ans;
        return 0;
    }

    for (int i = 0; i < par.size(); ++i)
        if (bmask[0] == (bmask[0] & par[i].F) && bmask[1] == (bmask[1] & par[i].S))
            dp[0][i] = 1;

    for (int y = 1; y + 1 < w; ++y)
    {
        for (auto tr: trip)
        {
            int t = par[tr.S].S;
            if (bmask[y + 1] == (bmask[y + 1] & t))
                dp[y][tr.S] = (dp[y][tr.S] + dp[y - 1][tr.F]) % MOD;
        }
    }

    ll ans = 0;
    for (int i = 0; i < ParCnt; ++i)
        ans = (ans + dp[w - 2][i]) % MOD;
    cout << ans;
    return 0;
}
