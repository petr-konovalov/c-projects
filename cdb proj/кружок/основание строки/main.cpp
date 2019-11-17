#include <bits/stdc++.h>

using namespace std;

char str[50001];
int p[50001];

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
    scanf("%s", str);
    calcPrefix(p, str);
    int len = strlen(str);
    printf("%i", len - p[len]);
    return 0;
}
