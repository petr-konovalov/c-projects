#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)

typedef double db;
typedef long long ll;
typedef long double ld;

const int N = 16;
const ld eps = 1e-10;
const ld INF = 1e+6;

valarray<ld> a[N];
valarray<ld> b[N];
valarray<ld> arr[N];
valarray<ld> ans;
valarray<ld> c;
ld res = -INF;
int n, m;

ld calc()
{
    ld val = 0;

    for (int i = 0; i < n; ++i)
        val += c[i] * ans[i];

    return val;
}

bool check()
{
    for (int i = 0, e = n + m; i < e; ++i)
    {
        ld val = 0;
        for (int j = 0; j < n; ++j)
            val += ans[j] * arr[i][j];
        if (val > arr[i][n] + eps)
            return false;
    }

    return true;
}

bool gauss()
{
    int cur = 0;

    for (int col = 0; col < n; ++col)
    {
        int mrow = cur;
        for (int row = cur + 1; row < n; ++row)
            if (abs(a[row][col]) > abs(a[mrow][col]))
                mrow = row;
        if (abs(a[mrow][col]) < eps)
            return false;
        swap(a[mrow], a[cur]);
        for (int row = cur + 1; row < n; ++row)
        {
            ld cf = a[row][col] / a[cur][col];
            a[row] -= a[cur] * cf;
        }
        ++cur;
    }

    for (int i = n - 1; i >= 0; --i)
    {
        ans[i] = a[i][n];
        for (int j = i + 1; j < n; ++j)
            ans[i] -= ans[j] * a[i][j];
        ans[i] /= a[i][i];
    }

    return true;
}

void getAns(int depth = 0)
{
    if (depth >= n)
    {
        for (int i = 0; i < n; ++i)
            a[i] = b[i];
        if (gauss() && check())
        {
            ld val = calc();
            if (res < val)
                res = val;
        }
        return;
    }
    for (int i = 0, e = m + n; i < e; ++i)
    {
        b[depth] = arr[i];
        getAns(depth + 1);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    ans.resize(n);
    c.resize(n);
    forn (i, m)
    {
        arr[i].resize(n + 1);
        for (int j = 0; j <= n; ++j)
            cin >> arr[i][j];
    }

    forn (i, n)
        cin >> c[i];

    forn (i, n)
    {
        a[i].resize(n + 1);
        b[i].resize(n + 1);
        arr[i + m].resize(n + 1);
        for (int j = 0; j <= n; ++j)
            arr[i + m][j] = 0;
        arr[i + m][i] = -1;
    }

    getAns();
    cout << fixed << setprecision(10) << res;

    return 0;
}
