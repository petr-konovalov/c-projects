#include <stdio.h>
#include <graphics.h>
#include <math.h>

void linef(double x1, double y1, double x2, double y2)
{
    line ((int)x1, (int)y1, (int)x2, (int)y2);
}

void Fractal(double x1, double y1 ,double x2, double y2, double x3, double y3, int n)
{
    if (n > 0)
    {
        double x4 ,y4 ,x5 ,y5 ,x6 ,y6;
        x4 = (x1 + x2)/2; y4 = (y1 + y2)/2;
        x5 = (x2 + x3)/2; y5 = (y2 + y3)/2;
        x6 = (x1 + x3)/2; y6 = (y1 + y3)/2;
        linef(x5, y5, x4, y4); linef(x6, y6, x4, y4); linef(x5, y5, x6, y6);
        Fractal(x1,y1,x4,y4,x6,y6,n-1);
        Fractal(x2,y2,x4,y4,x5,y5,n-1);
        Fractal(x3,y3,x5,y5,x6,y6,n-1);
    }
}

int main()
{
    int gd = DETECT;
    int gm;
    int n;

    scanf("%i", &n);

    initgraph(&gd, &gm,"");

    double x1 = 100,y1 = 100,x2 = 100,y2= 400,x3 = 400,y3 = 400;

    linef(x1,y1,x2,y2);
    linef(x1,y1,x3,y3);
    linef(x2,y2,x3,y3);
    Fractal(x1,y1,x2,y2,x3,y3,n);

    readkey();
    closegraph();
    return 0;
}
