#include <iostream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Rect
{
    int x, y;
    int size;
    Rect(int x, int y, int size): x(x), y(y), size(size) {};
};

const unsigned char VERT  = 179,
                    HOR   = 196,
                    LUP   = 218,
                    RUP   = 191,
                    LDOWN = 192,
                    RDOWN = 217;

unsigned char disp[50][20];

bool checkRect(int x, int y, int size)
{
    int xl = x, xr = x + size - 1;
    int yl = y, yr = y + size - 1;
    bool b = false;
    for (int i = 1; i < size - 1; ++i)
    {
        if ((disp[xl][yl + i] != '+' && disp[xl][yl + i] != VERT) ||
            (disp[xr][yl + i] != '+' && disp[xr][yl + i] != VERT) ||
            (disp[xl + i][yl] != '+' && disp[xl + i][yl] != HOR)  ||
            (disp[xl + i][yr] != '+' && disp[xl + i][yr] != HOR))
        return false;
        if (disp[xl][yl + i] != '+' || disp[xr][yl + i] != '+' ||
            disp[xl + i][yl] != '+' || disp[xl + i][yr] != '+')
        b = true;
    }
    if ((disp[xl][yl] != '+' && disp[xl][yl] != LUP) ||
        (disp[xr][yl] != '+' && disp[xr][yl] != RUP) ||
        (disp[xr][yr] != '+' && disp[xr][yr] != RDOWN) ||
        (disp[xl][yr] != '+' && disp[xl][yr] != LDOWN))
    return false;
    if (disp[xl][yl] != '+' || disp[xr][yl] != '+' ||
        disp[xr][yr] != '+' || disp[xl][yr] != '+')
    b = true;
    return b;
}

void drawRect(int x, int y, int size)
{
    int xl = x, xr = x + size - 1;
    int yl = y, yr = y + size - 1;
    for (int i = 0; i < size; ++i)
    {
        disp[xl][yl + i] = '+';
        disp[xr][yl + i] = '+';
        disp[xl + i][yl] = '+';
        disp[xl + i][yr] = '+';
    }
}

int main()
{
    stack<Rect> res;
    for (int y = 0; y < 20; ++y)
        for (int x = 0; x < 50; ++x)
            scanf(" %c", &disp[x][y]);
    bool b = true;
    while (b)
    {
        b = false;
        for (int y = 0; y < 20; ++y)
            for (int x = 0; x < 50; ++x)
                if (disp[x][y] != '.')
                    for (int size = min(20 - y, 50 - x); size >= 2; --size)
                    {
                        if (checkRect(x, y, size))
                        {
                            b = true;
                            res.push(Rect(x, y, size));
                            drawRect(x, y, size);
                        }
                    }
    }
    printf("%i\n", res.size());
    while (!res.empty())
    {
        printf("%i %i %i\n", res.top().x, res.top().y, res.top().size);
        res.pop();
    }
    return 0;
}
