#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

int a[10000];
int modify[200];
int minim[200];
int n, m, k, len;

void push(int block)
{
    if (modify[block] != 0)
    {
        for (int i = len * block, end = (block + 1) * len - 1; i <= end; ++i)
            a[i] += modify[block];
        minim[block] += modify[block];
        modify[block] = 0;
    }
}

void add(int l, int r)
{
    int cl = l / len;
    int cr = r / len;
    push(cl);
    push(cr);
    if (cl == cr)
    {
        for (int i = l; i <= r; ++i)
        {
            --a[i];
            if (a[i] < minim[cl])
                minim[cl] = a[i];
        }
    }
    else
    {
        for (int i = l, end = (cl + 1) * len - 1; i <= end; ++i)
        {
            --a[i];
            if (a[i] < minim[cl])
                minim[cl] = a[i];
        }
        for (int i = cl + 1, end = cr - 1; i <= end; ++i)
            --modify[i];
        for (int i = len * cr; i <= r; ++i)
        {
            --a[i];
            if (a[i] < minim[cr])
                minim[cr] = a[i];
        }
    }
}

int get(int l, int r)
{
    int cl = l / len;
    int cr = r / len;
    push(cl);
    push(cr);
    int res = a[l];
    if (cl == cr)
    {
        for (int i = l + 1; i <= r; ++i)
            if (a[i] < res)
                res = a[i];
    }
    else
    {
        for (int i = l + 1, end = (cl + 1) * len - 1; i <= end; ++i)
            if (a[i] < res)
                res = a[i];
        for (int i = cl + 1, end = cr - 1; i <= end; ++i)
            if (minim[i] + modify[i] < res)
                res = minim[i] + modify[i];
        for (int i = len * cr; i <= r; ++i)
            if (a[i] < res)
                res = a[i];
    }
    return res;
}

int main()
{
    scanf("%i %i %i", &n, &k, &m);
    len = (int)sqrt(n + .0) + 1;
    for (int i = 0; i < n; ++i)
        a[i] = k;
    for (int i = 0; i < len; ++i)
        minim[i] = k;
    for (int i = 0; i < m; ++i)
    {
        int l, r;
        scanf("%i %i", &l, &r);
        if (get(l + 1, r) != 0)
        {
            printf("Yes\n");
            add(l + 1, r);
        }
        else
            printf("No\n");
    }
    return 0;
}
