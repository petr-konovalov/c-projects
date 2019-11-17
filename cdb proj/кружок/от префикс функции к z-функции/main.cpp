#include <bits/stdc++.h>

using namespace std;

char str[1000001];
int p[1000001];
int z[1000001];

void getRes(char *t)
{
    int res = 0;
    z[0] = 0;
    int l = 0, r = 0;
    for (int i = 1; t[i] != '\0'; ++i)
    {
        if (i > r)
            r = i + 1, l = i;
        for (z[i] = min(r - i, z[i - l]); t[i + z[i]] != '\0' && t[i + z[i]] == t[z[i]]; ++z[i]);
        if (i + z[i] > r)
            r = i + z[i], l = i;
    }
}

int main()
{
    int n = 0;
    scanf("%i", &n);
    p[0] = -1;
    p[1] = 0;
    for (int i = 1; i <= n; ++i)
        scanf("%i", p + i);
    str[0] = 'a';
    for (int i = 2; i <= n; ++i)
    {
        if (p[i] != 0)
            str[i - 1] = str[p[i] - 1];
        else
        {
            int j = p[i - 1];
            bool used[32] = {false};
            while (j != -1)
            {
                used[str[j] - 'a'] = true;
                j = p[j];
            }
            int id = 0;
            while (used[id])
                ++id;
            str[i - 1] = 'a' + id;
        }
    }
    str[n] = '\0';
    getRes(str);
    for (int i = 0; i < n; ++i)
        printf("%i ", z[i]);
    return 0;
}
