#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define X first
#define Y second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 53;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int field[N][N];
int aimMap[N][N];
vector<pii> pos;
vector<pii> aim;
bool block[N];
vector<pair<pii, pii> > res;
int n, m;

void printField()
{
    for (int x = 1; x <= n; ++x)
    {
        for (int y = 1; y <= n; ++y)
        {
            debug("%i ", field[x][y]);
        }
        debug("\n");
    }
    debug("\n");
}

void printAim()
{
    for (int x = 1; x <= n; ++x)
    {
        for (int y = 1; y <= n; ++y)
        {
            debug("%i ", aimMap[x][y]);
        }
        debug("\n");
    }
    debug("\n");
}

void print()
{
    printField();
    printAim();
}

void moveNearest(int aimX, int aimY)
{
    int dist[N][N];
    pii p[N][N];
    queue<pii> q;
    dist[aimX][aimY] = 0;
    q.push(mp(aimX, aimY));

    for (int x = 1; x <= n; ++x)
        for (int y = 1; y <= n; ++y)
            dist[x][y] = 0;

    while (!q.empty())
    {
        pii cur = q.front();
        q.pop();
        int status = field[cur.X][cur.Y];
        if (status != 0 && !block[status - 1])
        {
            pii finish = mp(aimX, aimY);
            pos[status - 1] = finish;
            field[cur.X][cur.Y] = 0;
            field[finish.X][finish.Y] = status;
            block[status - 1] = true;
            while (cur != finish)
            {
                res.pb(mp(cur, p[cur.X][cur.Y]));
                cur = p[cur.X][cur.Y];
            }
            return;
        }
        for (int dir = 0; dir < 4; ++dir)
        {
            pii next = mp(cur.X + dx[dir], cur.Y + dy[dir]);
            if (dist[next.X][next.Y] == 0 && field[next.X][next.Y] != -1)
            {
                q.push(next);
                dist[next.X][next.Y] = dist[cur.X][cur.Y] + 1;
                p[next.X][next.Y] = cur;
            }
        }
    }
}

void saveWay(const pii start, pii pos, pii p[N][N])
{
    if (pos == start)
        return;
    saveWay(start, p[pos.X][pos.Y], p);
    res.pb(mp(p[pos.X][pos.Y], pos));
}

void moveCubeToPos(int id, pii dest)
{
    int dist[N][N];
    pii p[N][N];
    queue<pii> q;
    q.push(pos[id]);

    for (int x = 1; x <= n; ++x)
    {
        for (int y = 1; y <= n; ++y)
        {
            dist[x][y] = 0;
        }
    }

    while (!q.empty())
    {
        pii cur = q.front();
        q.pop();
        if (cur == dest)
        {
            field[pos[id].X][pos[id].Y] = 0;
            field[aim[id].X][aim[id].Y] = id + 1;
            saveWay(pos[id], cur, p);
            return;
        }

        for (int dir = 0; dir < 4; ++dir)
        {
            pii next = mp(cur.X + dx[dir], cur.Y + dy[dir]);
            if (dist[next.X][next.Y] == 0 && field[next.X][next.Y] == 0)
            {
                dist[next.X][next.Y] = dist[cur.X][cur.Y] + 1;
                p[next.X][next.Y] = cur;
                q.push(next);
            }
        }
    }
}

void moveRowLeft(int row)
{
    for (int y = 2; y <= n; ++y)
    {
        if (field[row][y] > 0 && field[row][y - 1] == 0)
        {
            int curY = y;
            while (field[row][curY - 1] == 0)
            {
                res.pb(mp(mp(row, curY), mp(row, curY - 1)));
                --curY;
            }
            pos[field[row][y] - 1] = mp(row, curY);
            field[row][curY] = field[row][y];
            field[row][y] = 0;
        }
    }
}

void moveRowRight(int row)
{
    for (int y = n - 1; y >= 1; --y)
    {
        if (field[row][y] > 0 && field[row][y + 1] == 0)
        {
            int curY = y;
            while (field[row][curY + 1] == 0)
            {
                res.pb(mp(mp(row, curY), mp(row, curY + 1)));
                ++curY;
            }
            pos[field[row][y] - 1] = mp(row, curY);
            field[row][curY] = field[row][y];
            field[row][y] = 0;
        }
    }
}

void arrangeLastRows()
{
    for (int y = 1; y <= n; ++y)
    {
        int id = aimMap[2][y] - 1;
        if (id >= 0)
        {
            field[pos[id].X][pos[id].Y] = 0;
            res.pb(mp(pos[id], mp(pos[id].X + 1, pos[id].Y)));
            field[++pos[id].X][pos[id].Y] = id + 1;
            moveRowLeft(2);
            moveRowRight(1);
        }
    }

    for (int y = 1; y <= n; ++y)
    {
        int id = field[1][y] - 1;
        if (id >= 0)
        {
            field[2][y] = field[1][y];
            field[1][y] = 0;
            res.pb(mp(pos[id], mp(pos[id].X + 1, pos[id].Y)));
            ++pos[id].X;
        }
    }
    moveRowLeft(2);

    for (int y = n; y >= 1; --y)
    {
        int id = aimMap[1][y] - 1;
        if (id >= 0)
        {
            field[pos[id].X][pos[id].Y] = 0;
            res.pb(mp(pos[id], mp(pos[id].X - 1, pos[id].Y)));
            field[--pos[id].X][pos[id].Y] = id + 1;
            moveRowRight(1);
            moveRowLeft(2);
        }
    }

    for (int y = 1; y <= n; ++y)
    {
        int id = aimMap[1][y] - 1;
        if (id >= 0)
            moveCubeToPos(id, aim[id]);
    }
    for (int y = n; y >= 1; --y)
    {
        int id = aimMap[2][y] - 1;
        if (id >= 0)
            moveCubeToPos(id, aim[id]);
    }
}

void read()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        field[0][i] = field[i][0] = field[n + 1][i] = field[i][n + 1] = -1;
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        cin >> x >> y;
        pos.pb(mp(x, y));
        field[x][y] = i;
    }

    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        cin >> x >> y;
        aim.pb(mp(x, y));
        aimMap[x][y] = i;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    read();

    if (n == 1)
    {
        cout << 0 << ' ';
        return 0;
    }

    for (int i = 1; i <= m; ++i)
        moveNearest(1, i);

    for (int x = n; x >= 3; --x)
        for (int y = 1; y <= n; ++y)
        {
            if (aimMap[x][y] > 0)
            {
                moveCubeToPos(aimMap[x][y] - 1, aim[aimMap[x][y] - 1]);
            }
        }

    arrangeLastRows();

    cout << res.size() << '\n';
    for (auto r: res)
        cout << r.X.X << ' ' << r.X.Y << ' ' << r.Y.X << ' ' << r.Y.Y << '\n';

    return 0;
}
