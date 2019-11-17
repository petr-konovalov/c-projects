#include <stdio.h>

using namespace std;

bool state[200][16];
int res[200][16];

int main()
{
    int h, m, l, t, c, s;
    scanf("%i %i %i %i %i %i", &h, &m, &l, &t, &c, &s);
    int startTime = h * 60 + m;
    for (int i = 0; i < s; ++i)
    {
        int hk, mk, tk, ck;
        char result[8];
        scanf("%i %i %i %i %s", &hk, &mk, &tk, &ck, result);
        --tk;
        --ck;
        int curTime = hk * 60 + mk;
        if (!state[tk][ck])
        {
            if (result[0] == 'O')
            {
                state[tk][ck] = true;
                if (curTime >= startTime)
                    res[tk][ck] += curTime - startTime;
                else
                    res[tk][ck] += curTime + 1440 - startTime;
            }
            else
                res[tk][ck] += 20;
        }
    }
    for (int i = 0; i < t; ++i)
    {
        int pCount = 0, ptime = 0;
        for (int j = 0; j < c; ++j)
            if (state[i][j])
            {
                ++pCount;
                ptime += res[i][j];
            }
        printf("%i %i\n", pCount, ptime);
    }
    return 0;
}
