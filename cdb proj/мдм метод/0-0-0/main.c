#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

int main()
{
    int gd = DETECT;
    int gm;
    initgraph(&gd, &gm,"");

    while (!anykeypressed())
    {
        g_mousestate st;

        getmousestate(&st);
        circle(st.x, st.y, 10);
        delay(5);
        clearviewport();
    }

    closegraph();
    return 0;
}
