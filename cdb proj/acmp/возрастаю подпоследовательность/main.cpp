#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

int x[10000];
vector<pair<int, int> > t[10000];

void print(int m, int p)
{
    if (p != -1)
    {
        print(m - 1, t[m][p].second);
        printf("%i ", t[m][p].first);
    }
}

int main()
{
    int n, m = 0;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
        scanf("%i", x + i);
    for (int i = 0; i < n; ++i)
    {
        int p = -1;
        for (int j = 0; j < n; ++j)
        {
            if (t[j].empty() || t[j].back().first >= x[i])
            {
                if (j > m)
                    m = j;
                t[j].push_back(make_pair(x[i], p));
                break;
            }
            p = t[j].size() - 1;
        }
    }
    printf("%i\n", m + 1);
    print(m, t[m].size() - 1);
    return 0;
}
