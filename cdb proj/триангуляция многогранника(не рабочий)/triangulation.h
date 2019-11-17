#ifndef TRIANGULATION_H_INCLUDED
#define TRIANGULATION_H_INCLUDED

#include <vector>

using namespace std;

struct Triangulation;

struct Point
{
    double x;
    double y;
    Point(){};
    Point(double x, double y): x(x), y(y){};
};

Point operator- (const Point p, const Point q);
/*
Point operator+ (const Point p, const Point q);
Point operator* (const Point p, const Point q);
*/

//предпологаеться что многоугольник имеет не меньше четырех вершин
Triangulation *getTriangulation(const vector<Point> polygon);

vector<Point> getPolyline(const Triangulation *triangulation, const int p, const int q);

#endif // TRIANGULATION_H_INCLUDED
