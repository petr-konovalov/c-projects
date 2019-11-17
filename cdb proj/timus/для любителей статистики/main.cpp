#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>

using namespace std;

map<int, vector<int> > stat;

bool citiesCheck(const vector<int> &v, int l, int r)
{
    int left = 0, right = v.size();
    if (right == 0)
        return false;

    while (right - left > 1)
    {
        int m = (right + left) / 2;
        if (v[m] > r)
            right = m;
        else
            left = m;
    }

    return l <= v[left] && v[left] <= r;
}

int main()
{
    int n = 0;

    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
    {
        int a;
        scanf("%i", &a);
        stat[a].push_back(i + 1);
    }

    int q = 0;

    scanf("%i", &q);
    for (int i = 0; i < q; ++i)
    {
        int l = 0;
        int r = 0;
        int x = 0;

        scanf("%i %i %i", &l, &r, &x);

        if (stat.find(x) != stat.end() && citiesCheck(stat[x], l, r))
            printf("1");
        else
            printf("0");
    }

    return 0;
}
