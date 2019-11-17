#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f = fopen("file.txt", "w");
    char c = 0;
    for (c = '0'; c <= '9'; ++c)
        fprintf(f, "%c", c);

    fclose(f);
    f = fopen("file.txt", "r");

    int i = 0;
    for (i = 0; i < 10; ++i)
    {
        fseek(f, -1-i, SEEK_END);
        fscanf(f, "%c", &c);
        printf("%c", c);
    }
    fclose(f);
    return 0;
}
