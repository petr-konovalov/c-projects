#include <bits/stdc++.h>

using namespace std;

#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define forn(i, n) for(int i = 0; i < n; ++i)

const int N = 1e5 + 7;

int n, k;
bool used[N];

int gcd(int a, int b)
{
    while (b != 0)
    {
        int bb = b;
        b = a % b;
        a = bb;
    }
    return a;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k;
    int res = k;
    forn (i, n)
    {
        int a;
        cin >> a;
        res = gcd(a, res);
    }
    int x = res % k;
    int cnt = 0;
    while (!used[x])
    {
        used[x] = true;
        x = (x + res) % k;
        ++cnt;
    }
    cout << cnt << '\n';
    forn (i, k)
        if (used[i])
            cout << i << ' ';
    return 0;
}
