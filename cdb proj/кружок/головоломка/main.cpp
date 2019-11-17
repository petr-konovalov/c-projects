#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)

const int N = 256;

bitset<N> a[N];
bitset<N> b[N];
bitset<N> ans;
int n;

void gauss()
{
    int mrow = 0;
    forn (col, n)
    {
        int crow = -1;
        for (int row = mrow; crow == -1 && row < n; ++row)
            if (a[row][col])
                crow = row;
        if (crow != -1)
        {
            swap(a[crow], a[mrow]);
            for (int row = mrow + 1; row < n; ++row)
            {
                if (a[row][col])
                    a[row] ^= a[mrow];
            }
            ++mrow;
        }
    }
}

bool solve()
{
    gauss();
    forn (row, n)
    {
        bool isZero = true;
        for (int col = 0; isZero && col < n; ++col)
            if (a[row][col])
                isZero = false;
        if (isZero && a[row][n])
            return false;
    }

    for (int row = n - 1; row >= 0; --row)
    {
        int ccol = 0;
        while (ccol < n && !a[row][ccol])
            ++ccol;
        if (ccol == n)
            continue;
        ans[ccol] = a[row][n];
        for (int col = ccol + 1; col < n; ++col)
            ans[ccol] = ans[ccol] ^ a[row][col] & ans[col];
    }

    return true;
}

void printAns()
{
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        if (ans[i])
            ++cnt;
    cout << cnt << '\n';
    for (int i = 0; i < n; ++i)
        if (ans[i])
            cout << i + 1 << ' ';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    forn (i, n)
    {
        int k;
        cin >> k;
        forn (j, k)
        {
            int t = 0;
            cin >> t;
            --t;
            a[t][i] = true;
        }
    }
    forn (i, n)
    {
        int t;
        cin >> t;
        a[i][n] = t == 1;
    }
    forn (i, n)
        for (int j = 0; j <= n; ++j)
            b[i][j] = a[i][j];
    if (solve())
    {
        printAns();
        return 0;
    }
    else
    {
        forn (i, n)
            for (int j = 0; j <= n; ++j)
                a[i][j] = b[i][j];
        forn (i, n)
            a[i][n] = !a[i][n];
        if (solve())
        {
            printAns();
            return 0;
        }
    }
    cout << "-1";
    return 0;
}
