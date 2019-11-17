#include "geometry.h"
#include <algorithm>
#include <queue>
#include <map>

struct Triangle
{
    int a;
    int b;
    int c;
    Triangle(){};
    Triangle(int a, int b, int c): a(a), b(b), c(c){};
};

typedef vector<vector<int> > Graph;
typedef vector<Triangle> Triangulation;

Point operator- (Point a, Point b)
{
    return Point(a.x - b.x, a.y - b.y);
}

Point operator- (Point a)
{
    return Point(-a.x, -a.y);
}

Point operator+ (Point a, Point b)
{
    return Point(a.x + b.x, a.y + b.y);
}

Point operator/ (Point a, double b)
{
    return Point(a.x / b, a.y / b);
}

Point operator* (Point a, double b)
{
    return Point(a.x * b, a.y * b);
}

bool operator< (Point a, Point b)
{
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool operator!= (Point a, Point b)
{
    return a.x != b.x || a.y != b.y;
}

bool operator == (Point a, Point b)
{
    return a.x == b.x && a.y == b.y;
}

//псевдоскалярное произведение векторов
double operator* (Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

//вычисляет угол менжду векторами
double operator^ (Point a, Point b)
{
    double res = acos((a.x * b.x + a.y * b.y) / sqrt((a.x * a.x + a.y * a.y) * (b.x * b.x + b.y * b.y)));

    if (a * b < 0)
        res = 2 * M_PI - res;

    return res;
}

double len(Point a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}

//для заданной вершины (предполагается что угол в ней < 180 градусов) ищет
//ближайшую точку которая лежит в треугольнике построенном на рёбрах смежных этой точке
//в случае отсутствия таких точек возвращает -1
int findConf(const Polygon poly, const vector<int> id, const int i)
{
    const double eps = 10e-10;
    int n = id.size();
    Point p0 = poly[id[i]], pr = poly[id[(i + 1) % n]], pl = poly[id[((i - 1) % n + n) % n]];
    double S = abs((pr - p0) * (pl - p0));
    int conf = -1;
    double dist = 1000000000;
    for (int j = 0, r = (i + 1) % n, l = ((i - 1) % n + n) % n; j < n; ++j)
    {
        if (j == i || j == l || j == r)
            continue;
        Point p = poly[id[j]];
        double pdist = len(p - p0);
        if (abs(S - abs((pr - p) * (pl - p)) - abs((pl - p) * (p0 - p)) - abs((p0 - p) * (pr - p))) < eps &&
            dist > pdist)
        {
            conf = j;
            dist = pdist;
        }
    }
    return conf;
}

//проверяет на выпуклость многоугольника и ищет точку с углом меньшим 180 градусов
bool isConvex(const Polygon poly, const vector<int> id, int &convexPoint)
{
    const double eps = 10e-10;
    double angle = (poly[id[1]] - poly[id[0]]) ^ (poly[id.back()] - poly[id[0]]);
    convexPoint = 0;
    bool res = true;
    if (angle + eps >= M_PI)
        res = false;
    for (int i = 1; i < id.size(); ++i)
    {
        angle = (poly[id[(i + 1) % id.size()]] - poly[id[i]]) ^ (poly[id[i - 1]] - poly[id[i]]);
        if (angle + eps < M_PI)
            convexPoint = i;
        else
            res = false;
    }
    return res;
}

//возращает вектор номеров вершин подполигона
vector<int> getNid(const vector<int> id, const int l, const int r)
{
    vector<int> nid;

    for (int cur = l; cur != r; cur = (cur + 1) % id.size())
        nid.push_back(id[cur]);

    return nid;
}

//тривиальная триангуляция выпуклого многоугольника
void triangleConvexPolygon(const vector<int> id, Triangulation &trian)
{
    for (int i = 2; i < id.size(); ++i)
        trian.push_back(Triangle(id[0], id[i], id[i - 1]));
}

//триангулирует многоугольник
//предпологается что вершин в многоугольнике не меньше трёх
void trianglePolygon(const Polygon poly, const vector<int> id, Triangulation &trian)
{
    int n = id.size();
    int i = -1;
    if (isConvex(poly, id, i))        //проверяем на выпуклось, ищем вершину с углом меньшим 180 градусов
    {
        triangleConvexPolygon(id, trian);
        return;
    }
    int conf = findConf(poly, id, i); //проверяем есть ли точки мешающие "отрезать" треугольник
    if (conf == -1)                   //если точка не найдена значит можно "отрезать" треугольник
    {
        trian.push_back(Triangle(id[i], id[(i + 1) % n], id[((i - 1) % n + n) % n]));
        vector<int> nid = getNid(id, (i + 1) % n, i);
        trianglePolygon(poly, nid, trian);
        return;
    }
    //триангулируем куски
    vector<int> nid = getNid(id, i, (conf + 1) % n);
    trianglePolygon(poly, nid, trian);
    nid.clear();
    nid = getNid(id, conf, (i + 1) % n);
    trianglePolygon(poly, nid, trian);
}

Triangulation trianglePolygon(const Polygon poly)
{
    Triangulation trian;
    vector<int> id(poly.size());

    for (int i = 0; i < id.size(); ++i)
        id[i] = i;
    trianglePolygon(poly, id, trian);

    return trian;
}

pair<int, int> getTriangleLine(const Triangle t, const int id)
{
    int a = 0;
    int b = 0;
    switch(id)
    {
        case 0:
            a = t.a;
            b = t.b;
            break;
        case 1:
            a = t.b;
            b = t.c;
            break;
        case 2:
            a = t.a;
            b = t.c;
            break;
    }
    if (a > b)
        swap(a, b);
    return make_pair(a, b);
}

//записывает для каждого треугольника список смежных с ним треугольников
Graph getTriangleGraph(const Triangulation trian)
{
    map<pair<int, int>, int> lineTriangle; //здесь запоминатеся треугольник которому принадлежит ребро
    Graph g(trian.size(), vector<int>());
    for (int i = 0; i < trian.size(); ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            pair<int, int> line = getTriangleLine(trian[i], j);
            map<pair<int, int>, int>::const_iterator it = lineTriangle.find(line);
            if (it != lineTriangle.end())
            {
                g[i].push_back(it->second);
                g[it->second].push_back(i);
            }
            else
                lineTriangle[line] = i;
        }
    }
    return g;
}

bool isPointBelongsTriangle(const int pointId, const Triangle triangle)
{
    return triangle.a == pointId || triangle.b == pointId || triangle.c == pointId;
}

//возвращает очередь из треугольников смежных с данной точкой
queue<int> pointOfTriangles(const int pointId, const Triangulation trian)
{
    queue<int> res;

    for (int i = 0; i < trian.size(); ++i)
        if (isPointBelongsTriangle(pointId, trian[i]))
            res.push(i);

    return res;
}

void makeRoute(const int triangleId, const Graph graph, const vector<int> status, vector<int> &route)
{
    if (status[triangleId] > 1)
    {
        int id = 0;
        while (status[graph[triangleId][id]] + 1 != status[triangleId])
            ++id;
        makeRoute(graph[triangleId][id], graph, status, route);
    }
    route.push_back(triangleId);
}

//возвращает путь состоящий из номеров треугольников по котороым
//можно добраться из точки с номером startPointId до точки с номером finishPointId
vector<int> getRoute(const Graph graph, const Triangulation trian,
                     const int startPointId, const int finishPointId)
{
    queue<int> processedTriangles = pointOfTriangles(startPointId, trian);
    vector<int> status(trian.size(), 0);
    int lastTriangle = -1;
    for (int i = 0, e = processedTriangles.size(); i < e; ++i)
    {
        int currentTriangle = processedTriangles.front();
        processedTriangles.pop();
        status[currentTriangle] = 1;
        processedTriangles.push(currentTriangle);
    }
    while (!processedTriangles.empty() && lastTriangle == -1)
    {
        int currentTriangle = processedTriangles.front();
        processedTriangles.pop();
        if (isPointBelongsTriangle(finishPointId, trian[currentTriangle]))
            lastTriangle = currentTriangle;
        else
            for (int i = 0; i < graph[currentTriangle].size(); ++i)
                if (status[graph[currentTriangle][i]] == 0)
                {
                    processedTriangles.push(graph[currentTriangle][i]);
                    status[graph[currentTriangle][i]] = status[currentTriangle] + 1;
                }
    }
    vector<int> res;
    if (lastTriangle != -1)
        makeRoute(lastTriangle, graph, status, res);
    while (!processedTriangles.empty())
        processedTriangles.pop();
    return res;
}

pair<int, int> getCommonLine(Triangle firstTriangle, Triangle secondTriangle)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (getTriangleLine(firstTriangle, i) == getTriangleLine(secondTriangle, j))
                return getTriangleLine(firstTriangle, i);
}

Polyline getNewLine(const Polygon poly, const Triangulation trian, const vector<int> trianPath)
{
    Polyline res;

    if (trianPath.size() > 1)
    {
        for (int i = 1; i < trianPath.size(); ++i)
        {
            pair<int, int> line = getCommonLine(trian[trianPath[i - 1]], trian[trianPath[i]]);
            res.push_back((poly[line.first] + poly[line.second]) / 2);
        }
    }
    else
        res.push_back((poly[trian[trianPath[0]].a] + poly[trian[trianPath[0]].b]
            - poly[trian[trianPath[0]].c] * 2) / 3 + poly[trian[trianPath[0]].c]);

    return res;
}

//разбивает полигон по триангуляции и пути на триангулиции, начальной и конечной вершине
PolygonPair splitPolygon(const Polygon poly, const Polyline polyline,
                         const int startPointId, const int finishPointId)
{
    PolygonPair res;
    for (int i = finishPointId; i != startPointId; i = (i + 1) % poly.size())
        res.firstPoly.push_back(poly[i]);
    res.firstPoly.push_back(poly[startPointId]);

    for (int i = 0; i < polyline.size(); ++i)
    {
        res.firstPoly.push_back(polyline[i]);
        res.secondPoly.push_back(polyline[i]);
    }

    reverse(res.secondPoly.begin(), res.secondPoly.end());
    for (int i = startPointId; i != finishPointId; i = (i + 1) % poly.size())
        res.secondPoly.push_back(poly[i]);
    res.secondPoly.push_back(poly[finishPointId]);
    return res;
}

//разбивает полигон на два по ломанной соединяющей точки startPointId и secondPointId
PolygonPair splitPolygon(const Polygon poly, const int startPointId, const int finishPointId)
{
    vector<int> id(poly.size());
    Triangulation trian;
    for (int i = 0; i < id.size(); ++i)
        id[i] = i;

    trianglePolygon(poly, id, trian);
    Graph g = getTriangleGraph(trian);
    vector<int> trianPath = getRoute(g, trian, startPointId, finishPointId);
    Polyline polyline = getNewLine(poly, trian, trianPath);
    PolygonPair res = splitPolygon(poly, polyline, startPointId, finishPointId);

    return res;
}

//строит выпуклую оболочку точек
Polygon makeConvexPolygon(const Polygon poly)
{
    const double eps = 10e-10;
    Polygon points(poly.begin(), poly.end());
    sort(points.begin(), points.end());
    Polygon up(1, points[0]);
    Polygon down(1, points[0]);
    for (int i = 1; i < points.size(); ++i)
    {
        double position = (points[0] - points[i]) * (points.back() - points[i]);
        if (position > -eps)
        {
            while (up.size() >= 2 && (up[up.size() - 2] - up.back()) * (points[i] - up.back()) < eps)
                up.pop_back();
            up.push_back(points[i]);
        }
        if (position < eps)
        {
            while (down.size() >= 2 && (down[down.size() - 2] - down.back()) * (points[i] - down.back()) > -eps)
                down.pop_back();
            down.push_back(points[i]);
        }
    }
    for (int i = up.size() - 2; i > 0; --i)
        down.push_back(up[i]);
    return down;
}

//раздувает выпуклый многоугольник power - степень раздувания
Polygon inflateConvexPolygon(const Polygon poly, double power = 1)
{
    Polygon res;

    for (int i = 0; i < poly.size(); ++i)
    {
        int l = ((i - 1) + poly.size()) % poly.size();
        int r = (i + 1) % poly.size();
        Point leftVector = poly[l] - poly[i];
        Point rightVector = poly[r] - poly[i];
        double lenLeftVector = len(leftVector);
        double lenRightVector = len(rightVector);
        Point additionalVector = leftVector / lenLeftVector + rightVector / lenRightVector;
        double sin = sqrt((1 - (leftVector.x * rightVector.x + leftVector.y * rightVector.y) /
                               (lenLeftVector * lenRightVector)) / 2);
        res.push_back(poly[i] - additionalVector * power / (len(additionalVector) * sin));
    }

    return res;
}

//расширяет многоугольник
Polygon getExtendedPolygon(const Polygon poly, const Polygon inflateConvexPoly)
{
    Polygon extendedPolygon;
    int minPointId = 0;

    for (int i = 1; i < poly.size(); ++i)
        if (poly[i] < poly[minPointId])
            minPointId = i;

    extendedPolygon.reserve(poly.size() + inflateConvexPoly.size());
    extendedPolygon.push_back(poly[minPointId]);
    for (int i = minPointId == 0 ? poly.size() - 1: minPointId - 1; i != minPointId;
        i = i == 0 ? poly.size() - 1: i - 1)
        extendedPolygon.push_back(poly[i]);
    for (int i = 0; i < inflateConvexPoly.size(); ++i)
        extendedPolygon.push_back(inflateConvexPoly[i]);

    return extendedPolygon;
}

//триангулирует внешнюю часть многоугольника
Triangulation triangleExternalRegion(const Polygon poly, Polygon &extendedPolygon)
{
    Triangulation trian;
    Polygon convexPoly = makeConvexPolygon(poly);
    Polygon inflateConvexPoly = inflateConvexPolygon(convexPoly, 2);
    extendedPolygon = getExtendedPolygon(poly, inflateConvexPoly);
    vector<int> ids;
    ids.reserve(poly.size() + inflateConvexPoly.size());
    int lastId = 0;
    for (Point e = convexPoly[1]; extendedPolygon[lastId] != e; ++lastId)
        ids.push_back(lastId);
    ids.push_back(lastId);
    for (int i = 1; i < convexPoly.size(); ++i)
        ids.push_back(poly.size() + i);
    ids.push_back(poly.size());
    trianglePolygon(extendedPolygon, ids, trian);
    ids.clear();
    ids.push_back(poly.size());
    ids.push_back(poly.size() + 1);
    for (int i = lastId; i < poly.size(); ++i)
        ids.push_back(i);
    ids.push_back(0);
    trianglePolygon(extendedPolygon, ids, trian);
    return trian;
}

//функция знака возврящяет 1 если аргумент положительный, -1 если отрицательный и 0 в иных случаях
int sign(double value)
{
    const double eps = 10e-9;
    if (value < -eps)
        return -1;
    else if (value > eps)
        return 1;
    else
        return 0;
}

//проверяет пересекает ли луч пущенный из точки checkPoint в сторону оси Ox
//отрезка с концами firstPoint secondPoint
//возврящает -1 если пересекает, 0 если принадлежит отрезку и 1 если не пересекает
int check(const Point firstPoint, const Point secondPoint, const Point checkPoint)
{
    const double eps = 10e-9;
    double ax = firstPoint.x - checkPoint.x;
    double ay = firstPoint.y - checkPoint.y;
    double bx = secondPoint.x - checkPoint.x;
    double by = secondPoint.y - checkPoint.y;
    int s = sign(ax * by - ay * bx);

    if (s == 0 && (abs(ay) < eps || abs(by) < eps) && abs(ax * bx) < eps)
        return 0;
    if (ay < -eps ^ by < -eps)
    {
        if (by < -eps)
            return s;
        return -s;
    }

    return 1;
}

//проверяет принадлежит ли точка многоугольнику
bool pointBelongsPolygon(const Polygon poly, Point point)
{
    int res = 1;

    for (int i = 1; i < poly.size(); ++i)
        res *= check(poly[i - 1], poly[i], point);
    res *= check(poly.back(), poly[0], point);

    return res <= 0;
}

PolygonPair spawnPolygon(const Polygon poly, const int startPointId, const int finishPointId)
{
    Polygon extendedPoly;
    Triangulation trian = triangleExternalRegion(poly, extendedPoly);
    Graph g = getTriangleGraph(trian);
    int sPointId = -1;
    int fPointId = -1;
    for (int i = 0; i < extendedPoly.size(); ++i)
    {
        if (extendedPoly[i] == poly[startPointId])
            sPointId = i;
        if (extendedPoly[i] == poly[finishPointId])
            fPointId = i;
    }
    vector<int> trianPath = getRoute(g, trian, sPointId, fPointId);
    Polyline polyline = getNewLine(extendedPoly, trian, trianPath);
    PolygonPair res = splitPolygon(poly, polyline, startPointId, finishPointId);

    if (pointBelongsPolygon(res.secondPoly, poly[(startPointId + 1) % poly.size()])
        && pointBelongsPolygon(res.secondPoly, poly[(finishPointId + 1) % poly.size()]))
        swap(res.firstPoly, res.secondPoly);
    reverse(res.secondPoly.begin(), res.secondPoly.end());
    return res;
}
