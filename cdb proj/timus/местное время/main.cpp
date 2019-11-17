#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct Time
{
    int minutes;
    int hour;
};

Time stringToTime(char *str)
{
    Time res;
    char buf[128];
    int i = 0;
    int j = 0;
    while (str[i] != '.')
    {
        buf[j++] = str[i];
        ++i;
    }
    buf[j] = '\0';
    res.hour = atoi(buf);
    j = 0;
    ++i;
    while (str[i] != '\0')
    {
        buf[j++] = str[i];
        ++i;
    }
    buf[j] = '\0';
    res.minutes = atoi(buf);
    return res;
}

int main()
{
    Time a, b;
    Time c, d;
    char str[128];
    cin >> str;
    a = stringToTime(str);
    cin >> str;
    b = stringToTime(str);
    cin >> str;
    c = stringToTime(str);
    cin >> str;
    d = stringToTime(str);
    int m = 1440;
    int rm = -5;
    for (int r = -5; r <= 5; ++r)
    {
        int d1 = (b.hour - a.hour + r) * 60 + b.minutes - a.minutes;
        int d2 = (d.hour - c.hour - r) * 60 + d.minutes - c.minutes;
        if (d1 < 0)
            d1 += 1440;
        if (d2 < 0)
            d2 += 1440;
        if (d1 <= 360 && d2 <= 360 && abs(d1 - d2) < m)
        {
            m = abs(d1 - d2);
            rm = r;
        }
    }
    printf("%i", abs(rm));
    return 0;
}
