#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <graphics.h>
#include <math.h>
#define PI 3.14159265359

const double c=PI/4;

void draw4(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
    line(x1,y1,x2,y2);
    line(x2,y2,x3,y3);
    line(x3,y3,x4,y4);
    line(x4,y4,x1,y1);
}

int main()
{
    int gd=DETECT,gn=DETECT;
    initgraph(&gd, &gn, "");
    double x1,y1,x2,y2,x3,y3,x4,y4,ox=200,oy=200,l=30;
    double a = 0.0f;
    g_mousestate st;
    while(1)
    {
        getmousestate(&st);
        ox=st.x;oy=st.y;
        x1=cos(a)*l+ox;y1=sin(a)*l+oy;
        x2=cos(a+2*c)*l+ox;y2=sin(a+2*c)*l+oy;
        x3=cos(a+4*c)*l+ox;y3=sin(a+4*c)*l+oy;
        x4=cos(a+6*c)*l+ox;y4=sin(a+6*c)*l+oy;
        draw4(x1,y1,x2,y2,x3,y3,x4,y4);
        a+=PI/90;
        delay(5);
        clearviewport();
    }
    closegraph();
    return 0;
}
