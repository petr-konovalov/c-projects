#include <iostream>
#include <stdio.h>

using namespace std;

int t[10000];
int n;

void initT()
{
    for (int i = 0; i < n; ++i)
        t[i] = 0;
}

int sum(int i)
{
    int res = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1)
        res += t[i];
    return res;
}

void change(int i)
{
    for (; i < n; i = (i | (i + 1)))
        t[i] += 1;
}

int main()
{
    int k;
    int res = 0;
    scanf("%i %i", &n, &k);
    for (int i = 0; i < k; ++i)
    {
        initT();
        for (int j = 0; j < n; ++j)
        {
            int num;
            scanf("%i", &num);
            --num;
            res += j - sum(num - 1);
            change(num);
        }
    }
    printf("%i", res);
    return 0;
}
