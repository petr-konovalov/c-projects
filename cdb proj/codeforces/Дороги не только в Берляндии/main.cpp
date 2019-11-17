#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct Road
{
    int s, e;
} Road;

int parent[1000];
int size[1000];

void makeSet(int v)
{
    parent[v] = v;
    size[v] = 1;
}

int findSet(int v)
{
    return parent[v] == v ? v : parent[v] = findSet(parent[v]);
}

bool unionSet(int a, int b)
{
    a = findSet(a);
    b = findSet(b);
    if (a == b)
        return false;
    if (size[a] < size[b])
        swap(a, b);
    parent[b] = a;
    size[a] += size[b];
    return true;
}

int main()
{
    int n;
    Road extraRoad[1000];
    int eRoadCount = 0;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
        makeSet(i);
    for (int i = 0; i < n - 1; ++i)
    {
        Road road;
        scanf("%i %i", &road.s, &road.e);
        --road.s;
        --road.e;
        if (!unionSet(road.s, road.e))
            extraRoad[eRoadCount++] = road;
    }
    printf("%i\n", eRoadCount);
    for (int i = 0; i < eRoadCount; ++i)
    {
        for (int e = 0; e < n; ++e)
            if (unionSet(extraRoad[i].s, e))
            {
                printf("%i %i %i %i\n", extraRoad[i].s + 1, extraRoad[i].e + 1, extraRoad[i].s + 1, e + 1);
                break;
            }
    }
    return 0;
}
