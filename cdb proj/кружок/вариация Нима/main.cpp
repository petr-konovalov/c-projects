#include <bits/stdc++.h>

#define init(p) freopen(p".in", "r", stdin); freopen(p".out", "w", stdout);

using namespace std;

int main()
{
    init("varnim");
    int t;
    scanf("%i", &t);
    while (t--)
    {
        int n;
        unsigned int res = 0;
        scanf("%u", &n);
        for (int i = 0; i < n; ++i)
        {
            unsigned int a;
            scanf("%u", &a);
            if ((a & 3) == 2 || (a & 3) == 1)
                res ^= a;
            else
                res ^= (a & 1) ? a + 1: a - 1;
        }
        printf(res ? "FIRST\n": "SECOND\n");
    }
    return 0;
}
