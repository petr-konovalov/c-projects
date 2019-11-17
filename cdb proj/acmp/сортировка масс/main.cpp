#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

const unsigned int base = 1000000000;
typedef struct
{
    unsigned int num[5];
    unsigned int value;
    char e[5];
} LongNum;

LongNum operator* (const LongNum a, const unsigned int &b)
{
    unsigned int ost = 0;
    LongNum res;
    res.value = a.value;
    for (int i = 0; i < 5; ++i)
    {
        res.e[i] = a.e[i];
        long long  cur = a.num[i] * 1ll * b + ost;
        res.num[i] = cur % base;
        ost = cur / base;
    }
    return res;
}

bool operator< (const LongNum &a, const LongNum &b)
{
    for (int i = 4; i >= 0; --i)
        if (a.num[i] < b.num[i])
            return true;
        else if (a.num[i] > b.num[i])
            return false;
    return false;
}

void initLongNum(LongNum &a, const unsigned int value)
{
    a.num[0] = value;
    for (int i = 1; i < 5; ++i)
        a.num[i] = 0;
}

int main()
{
    int n;
    scanf("%i", &n);
    LongNum mas[1000];
    for (int i = 0; i < n; ++i)
    {
        LongNum cm;
        scanf("%u %s", &cm.value, cm.e);
        initLongNum(cm, cm.value);
        int b = false;
        switch (cm.e[0])
        {
            case 'm':
                b = true;
                break;
            case 'k':
                cm = cm * 1000;
                break;
            case 'M':
                cm = cm * 1000000;
                break;
            case 'G':
                cm = cm * 1000000000;
                break;
        }
        switch (cm.e[cm.e[1] == '\0' ? 0: 1])
        {
            case 'g':
                cm = cm * (b ? 1 : 1000);
                break;
            case 'p':
                cm = cm * (b ? 16380 : 16380000);
                break;
            case 't':
                cm = cm * (b ? 1000000: 1000000000);
        }
        mas[i] = cm;
    }
    stable_sort(mas, mas + n);
    for (int i = 0; i < n; ++i)
        printf("%u %s\n", mas[i].value, mas[i].e);
    return 0;
}
