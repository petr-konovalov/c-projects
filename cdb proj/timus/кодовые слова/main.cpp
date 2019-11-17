#include <iostream>
#include <stdio.h>

using namespace std;

char s[1010];
int n;
int sum;
int len;

void raplaceSymbol()
{
    for (int i = 0; i < n; ++i)
        if (s[i] == '1' && (sum - i - 1) % (n + 1) == 0)
        {
            s[i] = '0';
            break;
        }
    printf("%s\n", s);
}

void addSymbol()
{
    for (int i = len; i >= 0; --i)
    {
        if (s[i] == '1')
            ++sum;
        s[i + 1] = s[i];
        if (sum % (n + 1) == 0)
        {
            s[i] = '0';
            printf("%s\n", s);
            return;
        }
        if ((sum + i + 1) % (n + 1) == 0)
        {
            s[i] = '1';
            printf("%s\n", s);
            return;
        }
    }
}

void deleteSymbol()
{
    for (int i = len; i >= 0; --i)
    {
        if (s[i] == '0' && sum % (n + 1) == 0 || s[i] == '1' && (sum - i - 1) % (n + 1) == 0)
        {
            s[i] = '\0';
            printf("%s%s\n", s, s + i + 1);
            return;
        }
        if (s[i] == '1')
            --sum;
    }
}

int main()
{
    scanf("%i", &n);
    while (1)
    {
        if (scanf(" %s", s) == EOF)
            break;
        len = 0;
        sum = 0;
        while (s[len] != '\0')
        {
            if (s[len] == '1')
                sum += len + 1;
            ++len;
        }
        if (len < n)
            addSymbol();
        else if (len > n)
            deleteSymbol();
        else
            raplaceSymbol();
    }
    return 0;
}
