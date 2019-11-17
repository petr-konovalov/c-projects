#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

vector<int> g[1000];
bool used[1000], st[1000];
vector<int> s;
vector<int> comp;

void findComp(int m)
{
    used[m] = true;
    comp.push_back(m);
    for (int i = 0; i < g[m].size(); ++i)
        if (!used[g[m][i]] && !st[g[m][i]])
            findComp(g[m][i]);
}

int main()
{
    int n, m;
    scanf("%i %i", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        scanf("%i %i", &x, &y);
        --x;
        --y;
        g[x].push_back(y);
        if (x != y)
            g[y].push_back(x);
    }
    int k;
    scanf("%i", &k);
    for (int i = 0; i < k; ++i)
    {
        int t;
        scanf("%i", &t);
        --t;
        st[t] = true;
        s.push_back(t);
    }

    for (int i = 0; i < s.size(); ++i)
    {
        comp.clear();
        findComp(s[i]);
        printf("%i\n", comp.size());
        for (int i = 0; i < comp.size(); ++i)
            printf("%i ", comp[i] + 1);
        printf("\n");
    }
    return 0;
}
