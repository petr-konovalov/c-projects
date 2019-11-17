#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>

using namespace std;

typedef struct
{
    int x, y;
} Pt;

Pt pnt[1200];
vector<int> r[1200];
int freq[1200];
int ostDist[1200];
int ostL[1200];

int dist(Pt p1, Pt p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int main()
{
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
        scanf("%i %i", &pnt[i].x, &pnt[i].y);
    freq[0] = 1;
    for (int i = 1; i < n; ++i)
    {
        ostDist[i] = dist(pnt[0], pnt[i]);
        ostL[i] = 0;
    }
    for (int i = 1; i < n; ++i)
    {
        int p = -1;
        for (int j = 0; j < n; ++j)
            if (freq[j] == 0 && (p == -1 || ostDist[j] < ostDist[p]))
                p = j;
        freq[p] = freq[ostL[p]] == 1 ? 2 : 1;
        for (int j = 0; j < n; ++j)
            if (freq[j] == 0 && dist(pnt[p], pnt[j]) < ostDist[j])
            {
                ostDist[j] = dist(pnt[p], pnt[j]);
                ostL[j] = p;
            }
    }
    int r = 2000000000;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (freq[i] == freq[j] && dist(pnt[i], pnt[j]) < r)
                r = dist(pnt[i], pnt[j]);
    printf("%.10llf\n", sqrt(r + .0) / 2);
    for (int i = 0; i < n; ++i)
        printf("%i ", freq[i]);
    return 0;
}
