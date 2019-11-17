#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>

using namespace std;

char pref[1024][35];
int c = 0;
int cnt[1024] = {0};

int main()
{
    int n;
    scanf("%i", &n);
    for (int i = 0, e = 1 << n; i < e; ++i)
    {
        char str[35];
        scanf("%s", str);
        scanf("%s", str);
        int j = 0;
        for (j = 0; j < c; ++j)
            if (strcmp(pref[j], str) == 0)
                break;
        ++cnt[j];
        if (j == c)
        {
            strcpy(pref[j], str);
            ++c;
        }
    }
    sort(cnt, cnt + c);
    for (int i = n - 1; i >= 0; --i)
    {
        int s = 1 << i;
        for (int j = 0; j < c; ++j)
            if (cnt[j] > s)
            {
                printf("%i", n - 1 - i);
                return 0;
            }
        for (int j = 0; j < c && s; ++j)
        {
            int d = min(s, cnt[j]);
            s -= d;
            cnt[j] -= d;
        }
    }
    printf("%i", n);
    return 0;
}
