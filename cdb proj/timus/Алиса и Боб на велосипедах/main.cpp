#include <iostream>
#include <stdio.h>

using namespace std;

int L, T, va, vb;

int checkPos(int papos, int pbpos, int v)
{
    if (v == 0)
        return 0;
    int R = pbpos - papos;
    if (R <= 0)
        R += L;
    double t = (double)R / v;
    if (t > 1)
        return 0;
    int c = (int)((double)v * (1 - t) / L);
    return c + 1;
}

int main()
{
    int n;
    int al = 0, ar = 0;
    int bl = 0, br = 0;
    int apos = 0, bpos = 0;
    int papos = 0, pbpos = 0;
    int fl = 0, fr = 0, ft = 0;
    bool astate = true;
    bool bstate = true;
    int res = 0;
    int k = 0;
    scanf("%i %i %i %i", &L, &T, &va, &vb);
    vb = -vb;
    scanf("%i", &n);
    for (int t = 0; t <= T; ++t)
    {
        if (t != 0)
            res += checkPos(papos, pbpos, (astate ? va : 0) + (bstate ? -vb : 0));
        while (k <= n && t >= fl)
        {
            if (ft == 1)
            {
                al = fl;
                ar = fr;
                astate = false;
            }
            else if (ft == 2)
            {
                bl = fl;
                br = fr;
                bstate = false;
            }
            if (k < n)
            {
                scanf("%i %i %i", &ft, &fl, &fr);
                fr = fr + fl;
            }
            ++k;
        }
        if (t >= ar)
            astate = true;
        if (t >= br)
            bstate = true;
        papos = apos;
        if (astate)
            apos = ((apos + va) % L + L) % L;
        pbpos = bpos;
        if (bstate)
            bpos = ((bpos + vb) % L + L) % L;
    }
    printf("%i", res);
    return 0;
}
