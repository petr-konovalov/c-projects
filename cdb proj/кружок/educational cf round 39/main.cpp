#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define L first
#define R second

typedef long long ll;
typedef double db;
typedef float fl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 500 + 3;
const ll INF = 1e18 + 3;

int read()
{
    int val;
    cin >> val;
    return val;
}

vector<int> tb[N];
int lp[N][N];
int rp[N][N];
int ans[N];

int nans[N];
int nlp[N][N];
int nrp[N][N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    forn (i, n)
    {
        char str[N];
        cin >> str;
        forn (j, m)
            if (str[j] == '1')
                tb[i].pb(j);
        if (!tb[i].empty())
        {
            forn (j, n)
            {
                ans[j] += tb[i].back() - tb[i].front() + 1;
                lp[j][i] = 0;
                rp[j][i] = tb[i].size() - 1;
            }
        }
        else
        {
            forn (j, n)
            {
                lp[j][i] = 1;
                rp[j][i] = 0;
            }
        }
    }

    forn (i, k)
    {
        forn (j, n)
            forn (l, n)
            {
                nlp[j][l] = lp[j][l];
                nrp[j][l] = rp[j][l];
            }
        forn (j, n)
        {
            nans[j] = ans[j];
            forn (l, n)
            {
                if (lp[l][j] == rp[l][j])
                {
                    if (ans[j] - 1 < nans[j])
                    {
                        nans[j] = ans[j] - 1;
                        nlp[j][j] = lp[l][j] + 1;
                    }
                }
                else if (lp[l][j] < rp[l][j])
                {
                    int d = tb[j][rp[l][j]] - tb[j][rp[l][j] - 1];
                    if (ans[j] - d < nans[j])
                    {
                        nans[j] = ans[j] - d;
                        nrp[j][j] = rp[l][j] - 1;
                    }
                    d = tb[j][lp[l][j] + 1] - tb[j][lp[l][j]];
                    if (ans[j] - d < nans[j])
                    {
                        nans[j] = ans[j] - d;
                        nlp[j][j] = lp[l][j] + 1;
                    }
                }
            }
        }
        forn (j, n)
        {
            ans[j] = nans[j];
            forn (l, n)
            {
                lp[j][l] = nlp[j][l];
                rp[j][l] = nrp[j][l];
            }
        }
    }

    int res = 1000000000;
    forn (i, n)
        res = min(res, ans[i]);
    cout << res;
    return 0;
}
