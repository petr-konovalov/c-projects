#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < (int)(n); ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define x first
#define y second
#define all(x) x.begin(), x.end()
#define sqr(x) ((x) * (x))
#define sz(c) int((c).size())

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 2e5 + 7, INF = 1e9 + 7, M = 1e2 + 9;

struct point
{
    point () {}
    point(int x, int y, int turn, int od) : x(x), y(y), turn(turn), od(od) {}
    int x, y;
    char turn, od;
};

bool operator<(const point &a, const point &b)
{
    return a.turn < b.turn || a.turn == b.turn && a.od > b.od;
}

bool operator<(const pii &a, const pii &b)
{
    return a.x < b.x || a.x == b.x && a.y > b.y;
}

pair<char, char> a[M][M];
bool river[M][M][M][M];
set<point> q;
int dx[] = {-1, 0, 1, -1, 0, 1};
int dy[] = {-1, -1, 0, 1, 1, 0};
pii dp[M][M];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int w, h, r, m, xs, ys, yf, xf, x, y, z, t, M;

    cin >> w >> h;

    forn(i, h)
    forn(j, w)
        cin >> a[i][j].x >> a[i][j].y;


    forn(i, h)
    {
        forn(j, w)
            cout << a[i][j].x << a[i][j].y << " ";
        cout << endl;
    }
    cout << "X" << endl;

    forn(i, h)
    forn(j, w)
        dp[i][j] = {INF, -1};

    cout << "X";

    cin >> r;
    forn(i, r)
    {
        cin >> x >> y >> z >> t;
        river[x][y][z][t] = 1;
    }

        cout << "X";

    cin >> M;
    cin >> xs >> ys >> xf >> yf;

    cout << "X";

    dp[xs][ys] = {1, M};
    q.insert(point(xs, ys, 1, M));

    while(!q.empty())
    {
        point v = *q.begin();
        q.erase (q.begin());
        x = v.x;
        y = v.y;
        if (dp[x][y].y <= 0)
        {
            q.insert(point(x, y, dp[x][y].x + 1, M));
            continue;
        }
        forn(i, 6)
        {
            int xx = x + dx[i];
            int yy = y + dy[i];

            if (xx < 0 || yy < 0 || xx >= h || yy >= w)
                continue;
            if (river[x][y][xx][yy])
            {
                if (mp(dp[x][y].x, 0) < dp[xx][yy])
                {
                    dp[xx][yy] = {dp[x][y].x, 0};
                    q.insert(point(xx, yy, dp[x][y].x, 0));
                }
                continue;
            }
            int law = 1;
            if (a[xx][yy].y == 'f' || a[xx][yy].y == 'm')
                law++;

            if (a[x][y].x == 'p' || a[xx][yy].x == 'h')
                law++;

            if (mp(dp[x][y].x, dp[x][y].y - law) < dp[xx][yy])
            {
                q.insert(point(xx, yy, dp[x][y].x, dp[x][y].y - law));
            }
        }
    }

    cout << dp[xf][yf].x << endl;

    return 0;
}
