#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back

typedef long long ll;
typedef double db;
typedef long double ld;

const int N = 256;

bitset<N> a[N];
int n, m;

bool gauss()
{
    int cur = 0;
    bool res = false;
    for (int col = 0; col < m; ++col)
    {
        int maxit = cur;
        while (maxit < n && !a[maxit][col])
            ++maxit;
        if (maxit == n)
        {
            cout << "Yes\n";
            res = true;
            continue;
        }
        res = false;
        cout << "No\n";
        swap(a[cur], a[maxit]);
        for (int row = cur + 1; row < n; ++row)
        {
            if (a[row][col])
                a[row] ^= a[cur];
        }
        ++cur;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int t;
            cin >> t;
            a[j][i] = t == 1;
        }
    }

    bool res[N] = {false};
    if (gauss())
    {
        for (int i = n - 1; i >= 0; --i)
        {
            if (!a[i][m - 1])
                continue;
            for (int j = 0; j < m - 1; ++j)
            {
                if (a[i][j])
                {
                    res[j] = true;
                    for (int k = 0; k < n; ++k)
                        a[k][m - 1] = a[k][m - 1] ^ a[k][j];
                    break;
                }
            }
        }
        for (int i = 0; i < m - 1; ++i)
            cout << (res[i] ? 1: 0) << ' ';
    }
    return 0;
}
