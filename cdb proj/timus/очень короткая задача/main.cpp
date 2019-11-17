#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int table[8][256];
bool termination[8] = {false};
typedef vector<char> Long;

char IntSign;
Long Number;
int PointPos;
char ESign;
int EPart;

void initializeTable()
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 256; ++j)
            table[i][j] = -1;
    termination[1] = true;
    termination[4] = true;
    termination[6] = true;
    for (unsigned char i = '0'; i <= '9'; ++i)
    {
        table[0][i] = 1;
        table[1][i] = 1;
        table[2][i] = 1;
        table[3][i] = 4;
        table[4][i] = 4;
        table[5][i] = 6;
        table[6][i] = 6;
        table[7][i] = 6;
    }
    table[0]['+'] = table[0]['-'] = 2;
    table[0]['.'] = 3;
    table[1]['.'] = 3;
    table[1]['e'] = table[1]['E'] = 5;
    table[4]['e'] = table[4]['E'] = 5;
    table[5]['+'] = table[5]['-'] = 7;
}

void initializeNumber()
{
    Number.clear();
    IntSign = '+';
    PointPos = -1000000;
    ESign = '+';
    EPart = 0;
}

bool isDigit(char c)
{
    return '0' <= c && c <= '9';
}

bool isSign(char c)
{
    return c == '-' || c == '+';
}

bool parse(char *str)
{
    int state = 0;
    initializeNumber();
    while (state != -1 && *str != '\n')
    {
        if (*str == '.')
            PointPos = Number.size();
        else
        if (isSign(*str))
        {
            if (state == 0)
                IntSign = *str;
            else if (state == 5)
                ESign = *str;
        }
        else
        if (isDigit(*str))
            if (0 <= state && state <= 4)
                Number.push_back(*str);
            else if (5 <= state && state <= 7)
                EPart = min(EPart * 10 + (int)(*str - '0'), 10000);
        state = table[state][*str];
        ++str;
    }
    int i = 0;
    while (i < Number.size() && Number[i] == '0')
        ++i;
    for (int j = 0; j + i < Number.size(); ++j)
        Number[j] = Number[j + i];
    Number.resize(Number.size() - i);
    if (PointPos == -1000000)
        PointPos = Number.size();
    else
        PointPos += EPart * (ESign == '-' ? -1: 1) - i;
    return state != -1 && termination[state];
}

int main()
{
    char str[300];
    initializeTable();
    fgets(str, 300, stdin);
    while (!(str[0] == '#' && str[1] == '\n'))
    {
        int n = 0;
        scanf("%i", &n);
        if (parse(str))
        {
            int k = 0;
            int len = 0;
            bool z = false;
            if (PointPos <= 0)
            {
                if (n > 0)
                    sprintf(str, "0."), len = 2;
                else
                    sprintf(str, "0"), len = 1;
                while (k < n && PointPos < 0)
                {
                    sprintf(str + len++, "0");
                    ++k;
                    ++PointPos;
                }
                int j = 0;
                while (k < n && j < Number.size())
                {
                    sprintf(str + len++, "%c", Number[j]);
                    z = z || Number[j] != '0';
                    ++k;
                    ++j;
                }
                while (k < n)
                {
                    sprintf(str + len++, "0");
                    ++k;
                }
                str[len] = '\0';
            }
            else
            {
                int i = 0;
                z = true;
                for (; i < PointPos && i < Number.size(); ++i)
                    sprintf(str + len++, "%c", Number[i]);
                for (; i < PointPos; ++i)
                    sprintf(str + len++, "0");
                if (n > 0)
                    sprintf(str + len++, ".");
                int k = 0;
                for(; i < Number.size() && k < n; ++i, ++k)
                    sprintf(str + len++, "%c", Number[i]);
                for(;k < n; ++k)
                    sprintf(str + len++, "0");
            }
            if (z && IntSign == '-')
                printf("-");
            printf("%s\n", str);
        }
        else
            printf("Not a floating point number\n");
        scanf(" ");
        fgets(str, 300, stdin);
    }
    return 0;
}
