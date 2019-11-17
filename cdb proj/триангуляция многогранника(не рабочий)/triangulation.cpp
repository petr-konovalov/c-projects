#include "triangulation.h"
#include <cmath>
#include <set>
#include <iostream>

struct Line
{
    int a;
    int b;
    Line(){};
    Line(int a, int b): a(a), b(b){};
};

struct Triangle
{
    int a, b, c;
    Triangle(){};
    Triangle(int a, int b, int c): a(a), b(b), c(c){};
};

Point operator- (const Point p, const Point q)
{
    return Point(p.x - q.x, p.y - q.y);
}

/*
Point operator+ (Point p, Point q)
{
    return Point(p.x + q.x, p.y + q.y);
}

Point operator* (Point p, double r)
{
    return Point(p.x * r, p.y * r);
}
*/

struct Triangulation
{
    vector<Line> lines;
    vector<Point> points;
    vector<vector<int> > pointTriangles;
    vector<Triangle> triangles;
    vector<vector<pair<int, int> > > graph;

    Triangulation(vector<Point> polygon)
    {
        int n = polygon.size();
        points = vector<Point>(polygon.begin(), polygon.end());
        graph = vector<vector<pair<int, int> > >(n - 2);
        for (int i = 0, e = n - 2; i < e; ++i)
            graph[i] = vector<pair<int, int> >();
        pointTriangles = vector<vector<int> >(n);
        for (int i = 0; i < n; ++i)
            pointTriangles[i] = vector<int>();
        lines = vector<Line>(n);
        for (int i = 0, e = n - 1; i < e; ++i)
        {
            lines[i].a = i;
            lines[i].b = i + 1;
        }
        lines[n - 1].a = n - 1;
        lines[n - 1].b = 0;
    };
};

void initNextPrev(vector<int> &next, vector<int> &prev, const unsigned int n)
{
    next.resize(n);
    prev.resize(n);
    next[0] = 1;
    prev[0] = n - 1;
    for (int i = 1, e = n - 1; i < e; ++i)
    {
        next[i] = i + 1;
        prev[i] = i - 1;
    }
    next[n - 1] = 0;
    prev[n - 1] = n - 2;
}

double len(const Point p)
{
    return sqrt(p.x * p.x + p.y * p.y);
}

double getCos(const Point p, const Point q)
{
    return (p.x * q.x + p.y * q.y) / (len(p) * len(q));
}

double getPseudoScalar(const Point p, const Point q)
{
    return p.x * q.y - p.y * q.x;
}

double getAngle(const Point p, const Point q)
{
    double res = acos(getCos(p, q));

    if (getPseudoScalar(p, q) < 0)
        res = 2 * M_PI - res;

    return res;
}

Triangulation *getTriangulation(const vector<Point> polygon)
{
    Triangulation *res = new Triangulation(polygon);
    vector<int> next;
    vector<int> prev;
    vector<double> ang(polygon.size());
    vector<int> lineTriangle(polygon.size(), -1);
    vector<pair<int, int> > pointLines(polygon.size());
    set<pair<double, int> > angles;
    initNextPrev(next, prev, polygon.size());

    for (int i = 0, n = polygon.size(); i < n; ++i)
    {
        double angle = getAngle(polygon[next[i]] - polygon[i], polygon[prev[i]] - polygon[i]);
        angles.insert(make_pair(angle, i));
        ang[i] = angle;
        pointLines[i] = make_pair(((i - 1) % n + n) % n, i);
    }
    for (int i = 0, e = polygon.size() - 3; i < e; ++i)
    {
        double angle = angles.begin()->first;
        int id = angles.begin()->second;
        int firstLine = pointLines[id].first;
        int secondLine = pointLines[id].second;
        int prevPoint = prev[id];
        int nextPoint = next[id];

        //обнавляем информацию об ицидентных ребрах
        pointLines[nextPoint].first = res->lines.size();
        pointLines[prevPoint].second = res->lines.size();

        //проверяем не принадлежали ли ребра другим треугольникам обновляем граф в случае необходимости
        if (lineTriangle[firstLine] != -1)
        {
            res->graph[res->triangles.size()].push_back(make_pair(lineTriangle[firstLine], firstLine));
            res->graph[lineTriangle[firstLine]].push_back(make_pair(res->triangles.size(), firstLine));
        }
        if (lineTriangle[secondLine] != -1)
        {
            res->graph[res->triangles.size()].push_back(make_pair(lineTriangle[secondLine], secondLine));
            res->graph[lineTriangle[secondLine]].push_back(make_pair(res->triangles.size(), secondLine));
        }

        //добавляем информацию о принадлежности ребра треугольнику
        lineTriangle.push_back(res->triangles.size());

        //добавляем новый треугольник
        res->pointTriangles[id].push_back(res->triangles.size());
        res->pointTriangles[prevPoint].push_back(res->triangles.size());
        res->pointTriangles[nextPoint].push_back(res->triangles.size());
        res->triangles.push_back(Triangle(res->lines.size(), firstLine, secondLine));

        //добавляем новое ребро и обновляем ссылки
        res->lines.push_back(Line(prevPoint, nextPoint));
        next[prevPoint] = nextPoint;
        prev[nextPoint] = prevPoint;

        //уничтожаем старую информацию об углах
        angles.erase(make_pair(ang[prevPoint], prevPoint));
        angles.erase(make_pair(ang[nextPoint], nextPoint));
        angles.erase(make_pair(angle, id));

        //добавляем новую информацию об углах
        angle = getAngle(polygon[nextPoint] - polygon[prevPoint], polygon[prev[prevPoint]] - polygon[prevPoint]);
        angles.insert(make_pair(angle, prevPoint));
        ang[i] = angle;
        angle = getAngle(polygon[next[nextPoint]] - polygon[nextPoint], polygon[prevPoint] - polygon[nextPoint]);
        angles.insert(make_pair(angle, nextPoint));
        ang[i] = angle;
    }
    //добавляем последний треугольник
    Line lastLine = res->lines.back();
    int lineId = res->lines.size() - 1;
    res->pointTriangles[lastLine.a].push_back(res->triangles.size());
    res->pointTriangles[lastLine.b].push_back(res->triangles.size());
    res->pointTriangles[next[lastLine.b]].push_back(res->triangles.size());
    res->graph[res->triangles.size()].push_back(make_pair(lineTriangle[lineId], lineId));
    res->graph[lineTriangle[lineId]].push_back(make_pair(res->triangles.size(), lineId));
    res->triangles.push_back(Triangle(lineId, pointLines[lastLine.a].first, pointLines[lastLine.b].second));

    cout << "lines:\n";
    for (int i = 0; i < res->lines.size(); ++i)
        cout << res->lines[i].a << ' ' << res->lines[i].b << endl;

    cout << "triangles:\n";
    for (int i = 0; i < res->triangles.size(); ++i)
    {
        cout << i << ": "
             << res->lines[res->triangles[i].a].a << '-'
             << res->lines[res->triangles[i].a].b << ' '
             << res->lines[res->triangles[i].b].a << '-'
             << res->lines[res->triangles[i].b].b << ' '
             << res->lines[res->triangles[i].c].a << '-'
             << res->lines[res->triangles[i].c].b << ' '
             << endl;
    }

    cout << "pointTriangles:\n";
    for (int i = 0; i < res->pointTriangles.size(); ++i)
    {
        cout << i << ": ";
        for (int j = 0; j < res->pointTriangles[i].size(); ++j)
            cout << res->pointTriangles[i][j] << ' ';
        cout << endl;
    }

    cout << "graph:\n";
    for (int i = 0; i < res->graph.size(); ++i)
    {
        cout << i << ": ";
        for (int j = 0; j < res->graph[i].size(); ++j)
            cout << '(' << res->graph[i][j].first << ", "
                      << res->lines[res->graph[i][j].second].a << '-'
                      << res->lines[res->graph[i][j].second].b << ')';
        cout << endl;
    }

    next.clear();
    prev.clear();
    lineTriangle.clear();
    ang.clear();
    pointLines.clear();
    angles.clear();

    return res;
};

vector<Point> getPolyline(const Triangulation *triangulation, const int p, const int q)
{

};
