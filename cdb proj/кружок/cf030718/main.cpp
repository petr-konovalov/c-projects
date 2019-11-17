#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)

const int N = 5e3 + 5;

typedef double db;

map<int, int> lg;
int cnt[32];

int n, q;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int num = 1;
    forn (i, 31)
    {
        lg[num] = i;
        num *= 2;
    }
    cin >> n >> q;
    forn (i, n)
    {
        int a;
        cin >> a;
        ++cnt[lg[a]];
    }
    forn (i, q)
    {
        int b, pos = 30, ans = 0;
        cin >> b;
        while (b > 0 && pos >= 0)
        {
            int c = min(b / (1 << pos), cnt[pos]);
            b -= c * (1 << pos);
            ans += c;
            --pos;
        }
        if (b != 0)
            cout << -1 << '\n';
        else
            cout << ans << '\n';
    }
    return 0;
}
