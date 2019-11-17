#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>

using namespace std;

char dig[256];

char number[101];
int nlen;

int n;
char word[50000][51];
int len[50000];

int t[101];
int p[101];

bool checkWord(int s, int m)
{
    for (int j = 0; j < len[m]; ++j)
        if (dig[word[m][j]] != number[s + j] - '0')
            return false;
    return true;
}

void printResult(int l)
{
    if (l > 0)
    {
        printResult(l - len[p[l]]);
        printf("%s ", word[p[l]]);
    }
}

int main()
{
    dig['i'] = dig['j'] = 1;
    dig['a'] = dig['b'] = dig['c'] = 2;
    dig['d'] = dig['e'] = dig['f'] = 3;
    dig['g'] = dig['h'] = 4;
    dig['k'] = dig['l'] = 5;
    dig['m'] = dig['n'] = 6;
    dig['p'] = dig['r'] = dig['s'] = 7;
    dig['t'] = dig['u'] = dig['v'] = 8;
    dig['w'] = dig['x'] = dig['y'] = 9;
    dig['o'] = dig['q'] = dig['z'] = 0;

    scanf("%s", number);
    while (number[0] != '-')
    {
        nlen = strlen(number);
        scanf("%i", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%s", word[i]);
            len[i] = strlen(word[i]);
        }
        t[0] = 0;
        for (int i = 1; i <= nlen; ++i)
            t[i] = 200;
        for (int i = 0; i < nlen; ++i)
            if (t[i] != 200)
            {
                for (int j = 0; j < n; ++j)
                    if (i + len[j] <= nlen && t[i + len[j]] > t[i] + 1 && checkWord(i, j))
                    {
                        t[i + len[j]] = t[i] + 1;
                        p[i + len[j]] = j;
                    }
            }
        if (t[nlen] == 200)
            printf("No solution.");
        else
            printResult(nlen);
        printf("\n");
        scanf("%s", number);
    }
    return 0;
}
