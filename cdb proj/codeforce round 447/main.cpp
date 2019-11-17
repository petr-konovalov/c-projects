#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < n; ++i)
#define fst first
#define scd second
#define pb push_back
#define mp make_pair
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int P = 1000000007;
const int N = 1000;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(false);
    cout.tie(false);

    int s[1000];
    int n;
    cin >> n;
    forn (i, n)
        cin >> s[i];
    forn (i, n)
        if (s[i] % s[0] != 0)
        {
            cout << -1;
            return 0;
        }
    cout << 2 * n << '\n';
    for (int i = 0; i < n; ++i)
        cout << s[0] << ' ' << s[i] << ' ';

    return 0;
}
