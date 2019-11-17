#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED
#include <iostream>
#include <vector>
#include <cmath>
#define M_PI 3.14159265358979323846

using namespace std;

struct Point
{
    double x;
    double y;
    Point(){};
    Point(double x, double y): x(x), y(y){};
};

Point  operator -  (Point a, Point  b);
Point  operator -  (Point a          );
Point  operator +  (Point a, Point  b);
Point  operator /  (Point a, double b);
Point  operator *  (Point a, double b);
/** псевдоскалярное произведение векторов */
double operator *  (Point a, Point  b);
bool   operator != (Point a, Point  b);
bool   operator == (Point a, Point  b);
/** вычисляет угол менжду векторами */
double operator ^  (Point a, Point  b);
/** сравнивает по первой координате в случае равенства по второй */
bool   operator <  (Point a, Point  b);

typedef vector<Point> Polygon;
typedef vector<Point> Polyline;

struct PolygonPair
{
    Polygon firstPoly;
    Polygon secondPoly;
    PolygonPair()
    {
        firstPoly = Polygon();
        secondPoly = Polygon();
    }
};

/**
 *разбивает многоугольник по ломанной соединяющей точки с индексами startPointId и finishPointId
 *@param poly исходный многоугольник (предпологается что
 *вершины перечислены в порядке против часовой стрелки)
 *@param startPointId номер первой вершины в исходном многоугольнике
 *@param finishPointId номер второй вершины в исходном многоугольнике
 *@return возвращает пару многоугольников полученных в результате (вершины расположены против часовой)
 *первый многоугольник начинается с вершины которая имела номер finishPointId
 *в исходном многоугольнике, а второй заканчивается на эту вершину,
 *причем во втором многоугольнике при движении против часовой стрелки сначала пройдем все новые вершины
 */
PolygonPair splitPolygon(const Polygon poly, const int startPointId, const int finishPointId);

/**
 *порождает новый многоугольник проводя ломанную проходящую по внешней области соединяющей
 *точки с индексами startPointId и finishPointId
 *в качестве первого многоугольника в результате окажется внешняя грань,
 *а в качестве второго окажется порождённый многоугольник
 *@param poly исходный многоугольник (предпологается что вершины перечислены в порядке против часовой стрелки)
 *@param startPointId номер первой вершины в исходном многоугольнике
 *@param finishPointId номер второй вершины в исходном многоугольнике
 *@return возвращает пару многоугольников (вершины расположены против часовой)
 *первый является новой внешней гранью второй является порождённым многоугольником
 */
PolygonPair spawnPolygon(const Polygon poly, const int startPointId, const int finishPointId);

#endif // GEOMETRY_H_INCLUDED
