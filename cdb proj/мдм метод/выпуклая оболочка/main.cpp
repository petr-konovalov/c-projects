#include <iostream>
#include <graphics.h>

using namespace std;

void drawPoints(int pointsCount, int *points)
{
    for (int i = 0; i < pointsCount; ++i)
        fillellipse(points[i * 2], points[i * 2 + 1], 3, 3);
}

int main()
{
    int gd = DETECT;
    int gm;
    initgraph(&gd, &gm,"");

    const int maxPointsCount = 2048;
    int points[maxPointsCount];
    int pointsCount = 0;

    char c = '\0';

    while (c != 'q')
    {
        while (!anykeypressed())
        {
            g_mousestate st, oldst;
            getmousestate(&st);
            if (c == ' ')
            {
                if (pointsCount <= maxPointsCount - 2)
                {
                    points[pointsCount++] = st.x;
                    points[pointsCount++] = st.y;
                    points[pointsCount] = points[0];
                    points[pointsCount + 1] = points[1];
                    clearviewport();
                    drawpoly(pointsCount / 2 + 1, points);
                    drawPoints(pointsCount / 2, points);
                }
                c = '\0';
            }
            if (oldst.x != st.x || oldst.y != st.y)
            {
                fillellipse(st.x, st.y, 2, 2);
                setfillstyle(1, 0);
                setcolor(0);
                fillellipse(oldst.x, oldst.y, 2, 2);
                setfillstyle(1, 15);
                setcolor(15);
                fillellipse(st.x, st.y, 2, 2);

                drawpoly(pointsCount / 2 + 1, points);
                drawPoints(pointsCount / 2, points);

                delay(15);
            }
            oldst = st;
        }

        c = readkey();
    }

    closegraph();
    return 0;
}
