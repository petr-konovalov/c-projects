#include <stdio.h>

using namespace std;

int div(int a, int b)
{
    return a / b + (a % b != 0 ? 1 : 0);
}

int dec(int &a, int &b, const int n)
{
    a = a * n - b;
    b *= n;
}

int main()
{
    int a, b;
    scanf("%i %i", &a, &b);
    while (a > 0)
    {
        int n = div(b, a);
        printf("1/%i\n", n);
        dec(a, b, n);
    }
    return 0;
}
