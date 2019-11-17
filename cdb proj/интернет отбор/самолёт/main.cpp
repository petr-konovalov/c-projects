#include <stdio.h>

using namespace std;

int main()
{
    int x, m, n, k;
    scanf("%i %i %i %i", &x, &m, &k, &n);
    printf("%i", ((x + k - m + n) % 24 + 24) % 24);
    return 0;
}
