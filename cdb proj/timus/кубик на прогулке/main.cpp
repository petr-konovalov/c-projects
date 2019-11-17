#include <iostream>
#include <set>

using namespace std;

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

int g[36][4];

void rotateLeft(int cube[6])
{
    int temp = cube[2];
    cube[2] = cube[3];
    cube[3] = cube[4];
    cube[4] = cube[5];
    cube[5] = temp;
}

void rotateRight(int cube[6])
{
    int temp = cube[5];
    cube[5] = cube[4];
    cube[4] = cube[3];
    cube[3] = cube[2];
    cube[2] = temp;
}

void rotateForward(int cube[6])
{
    int temp = cube[4];
    cube[4] = cube[1];
    cube[1] = cube[2];
    cube[2] = cube[0];
    cube[0] = temp;
}

void rotateAgo(int cube[6])
{
    int temp = cube[0];
    cube[0] = cube[2];
    cube[2] = cube[1];
    cube[1] = cube[4];
    cube[4] = temp;
}

void rotateA(int cube[6])
{
    int temp = cube[5];
    cube[5] = cube[1];
    cube[1] = cube[3];
    cube[3] = cube[0];
    cube[0] = temp;
}

int getIndex(int cube[6])
{
    return cube[4] * 6 + cube[1];
}

void setg(int cube[6])
{
    for (int i = 0; i < 4; ++i)
    {
        int index = getIndex(cube);
        rotateLeft(cube);
        g[index][0] = getIndex(cube);
        rotateRight(cube);
        rotateForward(cube);
        g[index][1] = getIndex(cube);
        rotateAgo(cube);
        rotateRight(cube);
        g[index][2] = getIndex(cube);
        rotateLeft(cube);
        rotateAgo(cube);
        g[index][3] = getIndex(cube);
        rotateForward(cube);
        rotateA(cube);
    }
}

void initialize(int cube[6])
{
    setg(cube);
    rotateLeft(cube);
    setg(cube);
    rotateLeft(cube);
    setg(cube);
    rotateLeft(cube);
    setg(cube);
    rotateLeft(cube);
    rotateForward(cube);
    setg(cube);
    rotateAgo(cube);
    rotateAgo(cube);
    setg(cube);
}

const int INF = 1000000000;

struct State
{
    int x, y;
    int id;
    State(){};
    State(int x, int y, int id): x(x), y(y), id(id){}
} p[8][8][36];

bool operator!= (State a, State b)
{
    return a.x != b.x || a.y != b.y || a.id != b.id;
}

void printState(State a)
{
    cout << a.x << " " << a.y << " " << a.id;
}

void printWay(State s, State e)
{
    if (s != e)
        printWay(s, p[e.x][e.y][e.id]);
    cout << (char)(e.x + 'a') << e.y + 1 << ' ';
}

void findWay(char x1, char y1, char x2, char y2, int cube[6])
{
    int sx = (int)(x1 - 'a'), sy = (int)(y1 - '1'),
        ex = (int)(x2 - 'a'), ey = (int)(y2 - '1');
    int d[8][8][36];
    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
            for (int state = 0; state < 36; ++state)
                d[x][y][state] = INF;
    d[sx][sy][25] = cube[4];
    set<pair<int, pair<int, pair<int, int> > > > q;
    q.insert(make_pair(cube[4], make_pair(25, make_pair(sx, sy))));
    while (!q.empty())
    {
        int vid = q.begin()->second.first,
            vx = q.begin()->second.second.first,
            vy = q.begin()->second.second.second;
        q.erase(make_pair(d[vx][vy][vid], make_pair(vid, make_pair(vx, vy))));
        for (int i = 0; i < 4; ++i)
        {
            int tox = vx + dx[i], toy = vy + dy[i];
            if (0 <= tox && tox < 8 && 0 <= toy && toy < 8)
            {
                int tov = g[vid][i];
                int len = cube[tov / 6];
                if (d[tox][toy][tov] > d[vx][vy][vid] + len)
                {
                    q.erase(make_pair(d[tox][toy][tov], make_pair(tov, make_pair(tox, toy))));
                    d[tox][toy][tov] = d[vx][vy][vid] + len;
                    p[tox][toy][tov] = State(vx, vy, vid);
                    q.insert(make_pair(d[tox][toy][tov], make_pair(tov, make_pair(tox, toy))));
                }
            }
        }
    }
    int optId = 0;
    for (int i = 0; i < 36; ++i)
        if (d[ex][ey][i] < d[ex][ey][optId])
            optId = i;
    cout << d[ex][ey][optId] << " ";
    printWay(State(sx, sy, 25), State(ex, ey, optId));
}

int main()
{
    char x1, y1, x2, y2;
    int cube[6];
    cin >> x1 >> y1 >> x2 >> y2;
    for (int i = 0; i < 6; ++i)
        cube[i] = i;
    initialize(cube);
    for (int i = 0; i < 6; ++i)
        cin >> cube[i];
    findWay(x1, y1, x2, y2, cube);
    return 0;
}
