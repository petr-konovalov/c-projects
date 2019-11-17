#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define F first
#define S second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e5 + 7, INF = 1e9 + 7;

int n;
int cnt[3][256];
int cr[3];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);


    cin >> n;
    string s[3];
    forn (i, 3)
    {
        cin >> s[i];
        for (char c: s[i])
        {
            ++cnt[i][c];
            if (cnt[i][c] > cr[i])
                cr[i] = cnt[i][c];
        }
    }
    if (n == 1)
    {
        forn (i, 3)
            cr[i] = min(cr[i] + 1, (int)s[i].size() - 1);
    }
    else
        forn (i, 3)
            cr[i] = min(cr[i] + n, (int)s[i].size());
    int mx = max(max(cr[0], cr[1]), cr[2]);
    int ccc = 0;
    forn (i, 3)
        if (cr[i] == mx)
            ++ccc;
    if (ccc > 1)
        cout << "Draw";
    else
    {
        if (cr[0] == mx)
            cout << "Kuro";
        else if (cr[1] == mx)
            cout << "Shiro";
        else
            cout << "Katie";
    }
    return 0;
}
