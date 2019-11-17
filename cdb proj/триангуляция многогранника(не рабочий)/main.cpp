#include <iostream>
#include "triangulation.h"

using namespace std;

int main()
{
    vector<Point> polygon;
    int n;
    cin >> n;
    polygon.resize(n);
    for (int i = 0; i < n; ++i)
    {
        double x, y;
        cin >> x >> y;
        polygon[i] = Point(x, y);
    }
    Triangulation *t = getTriangulation(polygon);
    return 0;
}
