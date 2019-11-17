#include <iostream>
#include <stdio.h>
#include <map>

using namespace std;

map<int, bool> odd;
map<int, int> prev;

bool add(int a, int b, bool c)
{
    if (odd.find(b) == odd.end())
    {
        odd[b] = c;
        prev[b] = a;
        return true;
    }
    int i = prev[b];
    if (i == a) return c == odd[b];
    if (i < a) return add(i, a - 1, c != odd[b]);
    return add(a, i - 1, c != odd[b]);
}

int main()
{
    while (1)
    {
        int res;
        int n;
        scanf("%i", &n);
        if (n == -1)
            break;
        scanf("%i", &n);
        res = n;
        odd.clear();
        prev.clear();
        for (int i = 0; i < n; ++i)
        {
            int l, r;
            char str[8];
            scanf("%i %i %s", &l, &r, str);
            if (res == n && !add(l, r, str[0] == 'o'))
                res = i;
        }
        printf("%i\n", res);
    }
    return 0;
}
