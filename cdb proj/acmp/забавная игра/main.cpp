#include <iostream>
#include <stdio.h>
#include <set>

using namespace std;

set<int> g[1000];
bool used[1000];

int calc(int m)
{
    used[m] = true;
    for (set<int>::iterator it = g[m].begin(); it != g[m].end(); ++it)
        if (!used[*it] && calc(*it) == -1)
            return *it;
    return -1;
}

int main()
{
    int n, k;
    scanf("%i %i", &n, &k);
    --k;
    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        scanf("%i %i", &a, &b);
        --a;
        --b;
        g[a].insert(b);
        g[b].insert(a);
    }
    int res = calc(k);
    if (res == -1)
        printf("First player loses\n");
    else
        printf("First player wins flying to airport %i", res + 1);
    return 0;
}
