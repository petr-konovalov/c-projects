#include <iostream>

using namespace std;

struct vect
{
    double x,y;
};

vect operator+ (vect a, vect b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

int main()
{
    vect a;
    vect b;
    cin>>a.x>>a.y>>b.x>>b.y;
    a = a + b;
    cout<<a.x<<' '<<a.y<<endl;
    int n;
    cin>>n;
    cout<<n;
    return 0;
}
