#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int base = 1000000000;
typedef int lnum[350];

void getLnum(lnum a)
{
    char s[3100];
    int n = 0;
    scanf("%s", s);
    for (int i = strlen(s); i > 0; i -= 9)
    {
        s[i] = '\0';
        a[n++] = atoi(i > 9 ? s + i - 9: s);
    }
}

void printLnum(lnum a)
{
    int n = 349;
    while (a[n] == 0 && n > 0)
        --n;
    if (n == 0 && a[n] == 0)
        printf("0");
    else
    {
        printf("%i", a[n]);
        for (int i = n - 1; i >= 0; --i)
            printf("%09i", a[i]);
    }
}

int comp(lnum a, lnum b)
{
    for (int i = 349; i >= 0; --i)
        if (a[i] > b[i])
            return 1;
        else if (a[i] < b[i])
            return -1;
    return 0;
}

void multShort(lnum a, int b, lnum r)
{
    long long curr = 0;
    int ost = 0;
    for (int i = 0; i < 350; ++i)
    {
        curr = a[i] * 1ll * b + ost;
        r[i] = curr % base;
        ost = curr / base;
    }
}

void moveLeft(lnum a, int step)
{
    for (int i = 349; i >= step; --i)
        a[i] = a[i - step];
    for (int i = step - 1; i >= 0; --i)
        a[i] = 0;
}

void sum3(lnum a, lnum b, lnum c, lnum r)
{
    long long curr = 0;
    int ost = 0;
    for (int i = 0; i < 350; ++i)
    {
        curr = a[i] + 0ll + b[i] + c[i] + ost;
        r[i] = curr % base;
        ost = curr / base;
    }
}

void getSqrB(lnum sqrb, int b, int pos)
{
    long long t = b * 1ll * b;
    sqrb[0] = t % base;
    sqrb[1] = t / base;
    moveLeft(sqrb, 2 * pos);
}

void getAB2(lnum ab2, lnum a, int b, int pos)
{
    multShort(a, 2 * b, ab2);
    moveLeft(ab2, pos);
}

void getNextSqr(lnum prevSqr, lnum a, int b, int pos, lnum sqr)
{
    lnum sqrb = {0};
    getSqrB(sqrb, b, pos);
    lnum ab2;
    getAB2(ab2, a, b, pos);
    sum3(prevSqr, sqrb, ab2, sqr);
}

void lnumCpy(lnum a, lnum b)
{
    for (int i = 0; i < 350; ++i)
        a[i] = b[i];
}

void getSqrt(lnum a)
{
    lnum sqr = {0};
    lnum res = {0};
    for (int i = 170; i >= 0; --i)
    {
        int l = 0, r = 1000000000;
        lnum currSqr = {0};
        while (r - l > 1)
        {
            int m = (r + l) / 2;
            getNextSqr(sqr, res, m, i, currSqr);
            if (comp(currSqr, a) == 1)
                r = m;
            else
                l = m;
        }
        getNextSqr(sqr, res, l, i, currSqr);
        lnumCpy(sqr, currSqr);
        res[i] = l;
    }
    lnumCpy(a, res);
}

int main()
{
    lnum a = {0};
    int b = 0;
    getLnum(a);
    getSqrt(a);
    printLnum(a);
    return 0;
}
