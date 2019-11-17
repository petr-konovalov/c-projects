#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

const int base = 1000000000;

typedef vector<int> LongNum;

int getDigit(const LongNum &a, const int index)
{
    return index < (int)a.size() ? a[index] : 0;
}

LongNum sumLong(const LongNum &a, const LongNum &b)
{
    int ost = 0;
    LongNum r;
    for (int i = 0; i < max(a.size(), b.size()); ++i)
    {
        r.push_back(getDigit(a, i) + getDigit(b, i) + ost);
        ost = r[i] / base;
        r[i] %= base;
    }
    if (ost > 0)
        r.push_back(ost);
    return r;
}

LongNum multLong(const LongNum &a, const LongNum &b)
{
    LongNum r(a.size() + b.size());
    int ost = 0;
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < b.size() || ost; ++j)
        {
            long long cur = r[i + j] + a[i] * 1ll * getDigit(b, j) + ost;
            ost = int(cur / base);
            r[i + j] = int(cur % base);
        }
    while (r.size() > 1 && r.back() == 0)
        r.pop_back();
    return r;
}

LongNum getLong()
{
    char s[1000];
    scanf("%s", s);
    LongNum r;
    for (int i = strlen(s); i > 0; i-=9)
    {
        s[i] = '\0';
        r.push_back(atoi(i < 9 ? s : s + i - 9));
    }
    return r;
}

void printLong(const LongNum &a)
{
    printf("%i", a.empty() ? 0: a.back());
    for (int i = (int)a.size() - 2; i >= 0; --i)
        printf("%09d", a[i]);
}

int main()
{
    LongNum a, b;
    int n, s;
    LongNum t[51][1001];

    cin >> n >> s;

    t[0][0].push_back(1);
    for (int i = 1; i < s; ++i)
        t[0][i].push_back(0);

    if (s & 1)
        cout << 0;
    else
    {
        s >>= 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j <= s; ++j)
            {
                t[i][j].push_back(0);
                for (int d = 0; d <= 9 && j - d >= 0; ++d)
                    t[i][j] = sumLong(t[i][j], t[i - 1][j - d]);
            }
        printLong(multLong(t[n][s], t[n][s]));
    }
    return 0;
}
