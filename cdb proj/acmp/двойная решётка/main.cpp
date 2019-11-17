#include <iostream>
#include <stdio.h>

using namespace std;

bool rx[101] = {false}, ry[101] = {false};
bool sz[10001] = {false};
int sc = 0;

int main()
{
    int x1, y1, x2, y2, dx, dy;
    scanf("%i %i %i %i %i %i", &x1, &y1, &x2, &y2, &dx, &dy);
    if (x1 < x2)
    {
        dx = (-dx + x1) % x2;
        swap(x1, x2);
    }
    if (y1 < y2)
    {
        dy = (-dy + y1) % y2;
        swap(y1, y2);
    }
    for (int i = 0; i <= 10000; ++i)
    {
        rx[min((x2 * i + dx) % x1, x2)] = true;
        rx[min(x1 - (x2 * i + dx) % x1, x2)] = true;
        ry[min((y2 * i + dy) % y1, y2)] = true;
        ry[min(y1 - (y2 * i + dy) % y1, y2)] = true;
    }
    for (int i = 1; i < 101; ++i)
        for (int j = 1; j < 101; ++j)
            if (rx[i] && ry[j])
                sz[i * j] = true;
    for (int i = 1; i < 10001; ++i)
        if (sz[i])
            ++sc;
    printf("%i\n", sc);
    for (int i = 1; i < 10001; ++i)
        if (sz[i])
            printf("%i\n", i);
    return 0;
}
