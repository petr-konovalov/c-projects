#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Point
{
    int x, y;
    bool operator< (const Point &b)
    {
        return (x * 1ll * x + y * 1ll * y) < (b.x * 1ll * b.x + b.y * 1ll * b.y);
    }
};

Point getPoint()
{
    Point res;
    cin >> res.x >> res.y;
    return res;
}

int main()
{
    vector<Point> arr;
    int n;
    cin >> n;
    arr.reserve(n);
    while (n--)
        arr.push_back(getPoint());
    sort(arr.begin(), arr.end());
    for (auto &v: arr)
        cout << v.x << ' ' << v.y << endl;
    return 0;
}
