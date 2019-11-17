#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int n;
    char c;
    scanf("%i ", &n);
    int h = n + 2;
    for (int i = 0; i < n; ++i)
    {
        while ((c = fgetc(stdin)) != '\n')
            if (c == '+')
                ++h;
    }
    if (h == 13)
        cout << 1400;
    else
        cout << h * 100;
    return 0;
}
