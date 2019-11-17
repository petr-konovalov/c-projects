#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

struct Pt
{
    int x, y;
    Pt(){}
    Pt(int x, int y): x(x), y(y){}
};

bool operator< (Pt a, Pt b)
{
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool operator== (Pt a, Pt b)
{
    return a.x == b.x && a.y == b.y;
}

Pt operator- (Pt a, Pt b)
{
    return Pt(a.x - b.x, a.y - b.y);
}

int orientS(Pt a, Pt b)
{
    return a.x * b.y - a.y * b.x;
}

vector<Pt> getConvexHull(vector<Pt> point)
{
    vector<Pt> up;
    vector<Pt> down;
    Pt v = point.back() - point.front();
    up.push_back(point.front());
    down.push_back(point.front());
    for (int i = 1; i < point.size(); ++i)
    {
        if (orientS(v, point[i] - point.front()) >= 0)
        {
            while (up.size() >= 2 && orientS(up[up.size() - 2] - up.back(), point[i] - up.back()) <= 0)
                up.pop_back();
            up.push_back(point[i]);
        }
        else
        {
            while (down.size() >= 2 && orientS(down[down.size() - 2] - down.back(), point[i] - down.back()) >= 0)
                down.pop_back();
            down.push_back(point[i]);
        }
    }
    vector<Pt> res;
    for (int i = 0; i < up.size(); ++i)
        res.push_back(up[i]);
    for (int i = down.size() - 1; i > 0; --i)
        res.push_back(down[i]);
    return res;
}

int getS(vector<Pt> polygon)
{
    int res = 0;
    for (int i = 1; i < polygon.size(); ++i)
        res += (polygon[i].y + polygon[i - 1].y) * (polygon[i].x - polygon[i - 1].x);
    res += (polygon.front().y + polygon.back().y) * (polygon.front().x - polygon.back().x);
    return abs(res);
}

int main()
{
    vector<Pt> point;
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
    {
        Pt t;
        scanf("%i %i", &t.x, &t.y);
        point.push_back(t);
    }
    sort(point.begin(), point.end());
    point.erase(unique(point.begin(), point.end()), point.end());
    vector<Pt> convexHull = getConvexHull(point);
    int s = getS(convexHull);
    printf("%i", (s >> 1) + (s & 1));
    return 0;
}
