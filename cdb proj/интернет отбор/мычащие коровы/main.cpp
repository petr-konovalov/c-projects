#include <stdio.h>
#include <vector>

using namespace std;

int main()
{
    vector<int> x;
    vector<int> y;
    int m, n;
    scanf("%i %i", &m, &n);
    for (int i = 0; i < n; ++i)
    {
        char str[51];
        scanf("%s", str);
        for (int j = 0; j < m; ++j)
            if (str[j] == 'C')
                x.push_back(i), y.push_back(j);
    }
    vector<int> agr(x.size());
    for (int i = 0; i < agr.size(); ++i)
    {
        for (int j = 0; j < agr.size(); ++j)
            if (i != j)
                agr[i] += (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
    }
    int res = 1000000000;
    for (int i = 0; i < agr.size(); ++i)
        if (agr[i] < res)
            res = agr[i];
    printf("%i", res);
    return 0;
}
