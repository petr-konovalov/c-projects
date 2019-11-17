#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)

typedef long long ll;

int n, x, y, s;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> x >> y;
    bool prev = true;
    string str;
    cin >> str;
    for (char c: str)
    {
        if (c == '0' && prev)
            ++s;

        prev = c == '1';
    }

    if (s == 0)
        cout << 0;
    else
        cout << min((ll)(s - 1) * x + y, (ll)s * y);
    return 0;
}
