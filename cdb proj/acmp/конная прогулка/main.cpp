#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int dx[8] = {+2,+2,-2,-2,+1,+1,-1,-1};
const int dy[8] = {+1,-1,+1,-1,+2,-2,+2,-2};
int cnt;
int oxy[100][100];
int g[100][100];
int kx, ky;
int n, m;

bool func(int x, int y, int dpt)
{
    g[x][y] = dpt;
    if (dpt == cnt)
        return true;
    int tox[8];
    int toy[8];
    int c = 0;
    for (int i = 0; i < 8; ++i)
    {
        int tx = x + dx[i], ty = y + dy[i];
        if (tx >= 0 && tx < n && ty >= 0 && ty < m)
        {
            --oxy[tx][ty];
            if (g[tx][ty] == 0)
            {
                tox[c] = tx;
                toy[c++] = ty;
            }
        }
    }
    for (int i = 1; i < c; ++i)
    {
        int j = i;
        while (j > 0 && oxy[tox[j]][toy[j]] < oxy[tox[j - 1]][toy[j - 1]])
        {
            swap(tox[j], tox[j - 1]);
            swap(toy[j], toy[j - 1]);
            --j;
        }
    }
    while (c > 1 && oxy[tox[c - 1]][toy[c - 1]] > oxy[tox[0]][toy[0]])
        --c;
    for (int i = c - 1; i >= 1; --i)
    {
        int j = rand() % (i + 1);
        swap(tox[i], tox[j]);
        swap(toy[i], toy[j]);
    }
    for (int i = 0; i < c; ++i)
        if (func(tox[i], toy[i], dpt + 1))
            return true;
    for (int i = 0; i < 8; ++i)
    {
        int tx = x + dx[i], ty = y + dy[i];
        if (tx >= 0 && tx < n && ty >= 0 && ty < m)
            ++oxy[tx][ty];
    }
    g[x][y] = 0;
    return false;
}

int main()
{
    srand(17);
    scanf("%i %i\n", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        char c;
        for (int j = 0; j < m; ++j)
        {
            scanf(" %c", &c);
            if (c == 'K')
            {
                kx = i;
                ky = j;
                ++cnt;
            }
            else if (c == '.')
            {
                g[i][j] = 0;
                ++cnt;
            }
            else if (c == 'X')
                g[i][j] = -1;
        }
    }
    for (int x = 0; x < n; ++x)
        for (int y = 0; y < m; ++y)
            for (int i = 0; i < 8; ++i)
            if (x + dx[i] >= 0 && x + dx[i] < n && y + dy[i] >= 0 && y + dy[i] < m
                && g[x + dx[i]][y + dy[i]] == 0)
                ++oxy[x][y];
    func(kx, ky, 1);
    for (int x = 0; x < n; ++x)
    {
        for (int y = 0; y < m; ++y)
            printf("%3i ", g[x][y] == -1 ? 0 : g[x][y]);
        printf("\n");
    }
    return 0;
}
