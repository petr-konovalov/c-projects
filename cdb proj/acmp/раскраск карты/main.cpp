#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

vector<int> g[50];
int r[50];
int orr[50];
int n;

bool check(int m)
{
    bool b = true;
    for (int i = 0; i < g[m].size() && b; ++i)
        b = r[m] != r[g[m][i]];
    return b;
}

int mc = 5;

bool draw(int m, int c)
{
    r[m] = c;
    if (c >= mc || !check(m))
    {
        r[m] = 0;
        return false;
    }
    for (int i = m + 1; i < n; ++i)
        if (r[i] == 0)
            if (draw(i, c))
                return true;
    int j = 0;
    for (; j < n && r[j] != 0; ++j);
    if (j == n)
    {
        for (int i = 0; i < n; ++i)
            orr[i] = r[i];
        mc = c;
        if (c == 3)
            return true;
    }
    else
        if (draw(j, c + 1))
            return true;
    r[m] = 0;
}

vector<int> comp;
bool vis2[50];

bool draw2(int m, int c)
{
    comp.push_back(m);
    vis2[m] = true;
    r[m] = c;
    for (int i = 0; i < g[m].size(); ++i)
        if (c == r[g[m][i]])
            return false;
        else
        if (r[g[m][i]] == 0)
            if (!draw2(g[m][i], 3 - r[m]))
                return false;
    return true;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int d;
            scanf("%i", &d);
            if (d)
                g[i].push_back(j);
        }
    }
    bool b = false;
    for (int i = 0; i < n; ++i)
        if (!vis2[i])
        {
            comp.clear();
            if (!draw2(i, 1))
            {
                b = true;
                for (int j = 0; j < comp.size(); ++j)
                    r[comp[j]] = 0;
            }
        }
    for (int i = 0; i < n; ++i)
        orr[i] = r[i];
    if (b)
    {
        int i = 0;
        for (; i < n && r[i]; ++i);
        if (i != n)
            draw(i, 1);
    }
    for (int i = 0; i < n; ++i)
        printf("%i ", orr[i]);
    return 0;
}
