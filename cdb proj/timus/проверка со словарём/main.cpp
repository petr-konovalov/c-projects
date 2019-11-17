#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    char word[101][10];
    int cwrong = 0;
    int cword = 0;
    scanf("%s", word[0]);
    while (word[cword++][0] != '#')
        scanf("%s", word[cword]);
    --cword;
    char str[20000];
    scanf(" ");
    while (fgets(str, 20000, stdin) != NULL)
    {
        int l = 0;
        int r = 0;
        int len = strlen(str);
        while (1)
        {
            while (l < len && (str[l] < 'a' || str[l] > 'z'))
                ++l;
            r = l + 1;
            while (r < len && ('a' <= str[r] && str[r] <= 'z'))
                ++r;
            if (r > len)
                break;
            for (int j = 0; j < cword; ++j)
            {
                int id = -1;
                int len = r - l;
                if (len != strlen(word[j]))
                    continue;
                for (int i = 0; i < len; ++i)
                    if (word[j][i] != str[l + i])
                        if (id == -1)
                            id = i;
                        else
                        {
                            id = -1;
                            break;
                        }
                if (id != -1)
                {
                    str[l + id] = word[j][id];
                    ++cwrong;
                    break;
                }
            }
            l = r + 1;
        }
        printf("%s", str);
    }
    printf("%i", cwrong);
    return 0;
}
