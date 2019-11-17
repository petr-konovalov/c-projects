#include <bits/stdc++.h>

using namespace std;

int z[1000000];
char str[1000001];
int p[1000001];

void calcPrefix(int *p, char *str)
{
    p[0] = -1;
    for (int i = 1; str[i - 1] != '\0'; ++i)
    {
        int j = p[i - 1];
        while (j != -1 && str[j] != str[i - 1])
            j = p[j];
        p[i] = j + 1;
    }
}

int main()
{
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
        scanf("%i", z + i);
    str[0] = 'a';
    int l = 0, r = 1;
    for (int i = 1; i < n; ++i)
    {
        int t = i + z[i];
        if (z[i] != 0 && t > r)
            for (;r < t; ++r)
                str[r] = str[r - i];
        else if (i == r)
        {
            bool used[32] = {false};
            for (;l <= r; ++l)
                if (l + z[l] == r)
                    used[str[z[l]] - 'a'] = true;
            ++r;
            int id = 0;
            while (used[id])
                ++id;
            str[i] = 'a' + id;
        }
    }
    str[n] = '\0';
    calcPrefix(p, str);
    for (int i = 1; i <= n; ++i)
        printf("%i ", p[i]);
    return 0;
}
