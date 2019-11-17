#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

vector<int> g[100];
bool r[100];
bool vis[100];

bool check(int m)
{
    vis[m] = true;
    for (size_t i = 0; i < g[m].size(); ++i)
    {
        if (vis[g[m][i]])
        {
            if (r[m] == r[g[m][i]])
                return false;
        }
        else
        {
            r[g[m][i]] = !r[m];
            if (!check(g[m][i]))
                return false;
        }
    }
    return true;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int num;
        scanf("%i", &num);
        while (--num != -1)
        {
            g[i].push_back(num);
            g[num].push_back(i);
            scanf("%i", &num);
        }
    }

    if (check(0))
    {
        for (int i = 0; i < n; ++i)
            printf("%i", r[i] ? 1 : 0);
    }
    else
        printf("-1");
    return 0;
}
