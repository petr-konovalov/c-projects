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
/** ��������������� ������������ �������� */
double operator *  (Point a, Point  b);
bool   operator != (Point a, Point  b);
bool   operator == (Point a, Point  b);
/** ��������� ���� ������ ��������� */
double operator ^  (Point a, Point  b);
/** ���������� �� ������ ���������� � ������ ��������� �� ������ */
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
 *��������� ������������� �� �������� ����������� ����� � ��������� startPointId � finishPointId
 *@param poly �������� ������������� (�������������� ���
 *������� ����������� � ������� ������ ������� �������)
 *@param startPointId ����� ������ ������� � �������� ��������������
 *@param finishPointId ����� ������ ������� � �������� ��������������
 *@return ���������� ���� ��������������� ���������� � ���������� (������� ����������� ������ �������)
 *������ ������������� ���������� � ������� ������� ����� ����� finishPointId
 *� �������� ��������������, � ������ ������������� �� ��� �������,
 *������ �� ������ �������������� ��� �������� ������ ������� ������� ������� ������� ��� ����� �������
 */
PolygonPair splitPolygon(const Polygon poly, const int startPointId, const int finishPointId);

/**
 *��������� ����� ������������� ������� �������� ���������� �� ������� ������� �����������
 *����� � ��������� startPointId � finishPointId
 *� �������� ������� �������������� � ���������� �������� ������� �����,
 *� � �������� ������� �������� ���������� �������������
 *@param poly �������� ������������� (�������������� ��� ������� ����������� � ������� ������ ������� �������)
 *@param startPointId ����� ������ ������� � �������� ��������������
 *@param finishPointId ����� ������ ������� � �������� ��������������
 *@return ���������� ���� ��������������� (������� ����������� ������ �������)
 *������ �������� ����� ������� ������ ������ �������� ���������� ���������������
 */
PolygonPair spawnPolygon(const Polygon poly, const int startPointId, const int finishPointId);

#endif // GEOMETRY_H_INCLUDED
