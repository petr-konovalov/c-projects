#include <stdio.h>

using namespace std;

int main()
{
    int k;
    scanf("%i", &k);
    switch(k)
    {
        case 0:
            printf("1\n0\n");
            break;
        case 1:
            printf("1\n1\n");
            break;
        case 2:
            printf("2\n1 3\n");
            break;
        default:
            long long t = 1ll << (k - 1);
            printf("4\n1 %lli %lli %lli\n", t - 1, t + 1, (t << 1) - 1);
    }
    return 0;
}
