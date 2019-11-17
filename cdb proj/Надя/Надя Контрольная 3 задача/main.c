#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f = fopen("input.txt", "r");
    float sr = -1000000;
    int in = 0;
    int cindex = 1;

    while (!feof(f))
    {
        char buf[128] = "";
        float sum = 0;
        int count = 0;
        int l = 0;

        char c;
        while ((c = fgetc(f)) != '\n' && c != EOF)
        {
            if (c == ' ' && l>0)
            {
                buf[l] = '\0';
                sum += atof(buf);
                l = 0;
                ++count;
            }
            else
                buf[l++] = c;
        }
        buf[l] = '\0';
        sum += atof(buf);
        ++count;

        sum /= count;
        if (sum > sr)
            in = cindex;
        ++cindex;
    }

    printf("%i", in);
    close(f);
    return 0;
}
