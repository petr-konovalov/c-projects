#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

const int maxSize = 100, maxDeg = 5;

int main()
{
    int size;
    double inp[maxDeg][maxSize];
    cin >> size;
    for (int i = 0; i < size; ++i)
        cin >> inp[0][i];

    for (int i = 1; i < maxDeg; ++i)
        for (int j = 0, e = size - i; j < e; ++j)
            inp[i][j] = inp[i - 1][j + 1] - inp[i - 1][j];

    printf("______________________________________________________\n");
    printf("          |          |          |          |          |\n");
    printf("%10s|%10s|%10s|%10s|%10s|\n", "P(x)  ", "d1  ", "d2  ", "d3  ", "d4  ");
    printf("__________|__________|__________|__________|__________|\n");
    printf("          |          |          |          |          |\n");
    for (int i = 0, e = size * 2 - 1; i < e; ++i)
    {
        if (i & 1)
            printf("%10s|", " ");
        for (int j = i & 1, k = i >> 1; j < maxDeg; j += 2, --k)
            if (k >= 0 && k < size - j)
                printf(j + 1 < maxDeg ? "%10.6f|%10s|": "%10.6f|%10s", inp[j][k], " ");
            else
                printf(j + 1 < maxDeg ? "%10s|%10s|": "%10s|%10s", "", "");
        printf("\n");
    }
    printf("__________|__________|__________|__________|__________|\n");

    return 0;
}
