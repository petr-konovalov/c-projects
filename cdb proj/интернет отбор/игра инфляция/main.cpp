#include <iostream>
#include <stdio.h>
#include <set>

using namespace std;

int main()
{
    int n;
    set<int> num;
    scanf("%i", &n);
    int ost = n % 3;
    int d = 0;
    num.insert(n);
    while (ost != 2)
    {
        ++d;
        if (ost == 0)
            n /= 3;
        else
            n = 2 * n + 1;
        if (num.find(n) != num.end())
        {
            printf("%i", d);
            return 0;
        }
        else
            num.insert(n);
        ost = n % 3;
    }
    printf("-1");
    return 0;
}
