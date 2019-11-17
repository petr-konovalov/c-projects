#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define STRING_COUNT 1024
#define STRING_LENGTH 128

void qs(char s[STRING_COUNT][STRING_LENGTH], int first, int last)
{
    int i = first, j = last;
    char x[STRING_LENGTH], t[STRING_LENGTH];
    strcpy(x, s[(first + last) / 2]);

    do {
        while (strcmp(s[i], x) < 0)
            ++i;
        while (strcmp(s[j], x) > 0)
            --j;

        if (i <= j) {
            if (strcmp(s[i], s[j]) != 0)
            {
                strcpy(t, s[i]);
                strcpy(s[i], s[j]);
                strcpy(s[j], t);
            }
            ++i;
            --j;
        }
    } while (i <= j);

    if (i < last)
        qs(s, i, last);
    if (first < j)
        qs(s, first, j);
}

int main()
{
    FILE *fin, *fout;
    char s[STRING_COUNT][STRING_LENGTH], s0[STRING_LENGTH];
    int n = 0, i;

    fin = fopen( "input.txt", "r");
    fout = fopen( "output.txt", "w");

    for (i = n; fgets(s[n], STRING_LENGTH - 1, fin); ++n);
    qs(s, 0, n - 1);
    for (i = 0; i < n; i++)
        fputs(s[i], fout);

    fclose(fin);
    fclose(fout);
    return 0;
}
