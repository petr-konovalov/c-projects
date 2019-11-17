#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
const int n=10;
const double xarr[]= {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
const double yarr[] = {1.614419, 1.656832, 1.694888, 1.728606, 1.758030, 1.783225, 1.804279, 1.821299, 1.834414, 1.843768};
const double x1 = 0.163678, x2 = 0.730047, x3 = 0.219975, y = 1.692653, h = 0.1;
const double eps = 1e-006;

int closest(double a,double b1, double b2, int n1, int n2)
{
    if (fabs(a-b1)<fabs(a-b2))
        return n1;
    else
        return n2;
}

int main()
{
    vector<vector<double> > in(5,vector<double>(n));
    vector<double> v1(yarr, yarr + n);
    vector<double> x(xarr, xarr + n);
    in[0]=v1;
    for (int i=1;i<5; i++)
        for (int j=0;j<n; j++)
        {
            in[i][j]=in[i-1][j+1]-in[i-1][j];
        };
    int num=0;
    while (x[num]<x1)
        num++;
    double fact = 1;
    double tfact = 1;
    double res = 0;
    double t = (x1-x[num-1])/h;
    for (int i=0;i<5; i++)
    {
        res+=(in[i][num-1]*tfact)/fact;
        fact*=i+1;
        tfact*=t-i;
    };
    cout<<x1<<"       "<<res<<endl;
    num=9;
    while (x[num]>x2)
        num--;
    fact = 1;
    tfact = 1;
    res = 0;
    t = (x2-x[num+1])/h;
    for (int i=0;i<5; i++)
    {
        res+=in[i][num+1-i]*tfact/fact;
        fact*=i+1;
        tfact*=t+i;
    };
    cout<<x2<<"       "<<res<<endl;
    num=0;
    while (x[num]<x3)
        num++;

    fact = 1;
    tfact = 1;
    res = 0;
    num = closest(x3, x[num],x[num-1],num,num-1);
    t = (x3-x[num])/h;
    for (int i=0;i<5; i++)
    {
        res+=in[i][num-(i/2)]*tfact/fact;
        fact*=i+1;
        tfact*=t+pow(-1,i%2)*(i/2);
    };
    cout<<x3<<"       "<<res<<endl;
    double tprev = 100000;
    int k=0;
    while (v1[num]<y)
        num++;
    num--;
    t = 0;
    while (abs(t-tprev)>eps)
    {
        tprev=t;
        t=(y-in[0][num]-in[2][num]/2*t*(t-1)-in[3][num]/6*t*(t-1)*(t-2)-in[4][num]/24*t*(t-1)*(t-2)*(t-3))/in[1][num];
    };
    double ansX = x[num] + t * h;
    while (x[num]<t)
        num++;
    fact = 1;
    tfact = 1;
    res = 0;
    num = closest(t, x[num],x[num-1],num,num-1);
    t = (t-x[num])/h;
    for (int i=0;i<5; i++)
    {
        res+=in[i][num-(i/2)]*tfact/fact;
        fact*=i+1;
        tfact*=t+pow(-1,i%2)*(i/2);
    };
    cout<<ansX<<"       "<<res<<endl;
    return 0;
}
