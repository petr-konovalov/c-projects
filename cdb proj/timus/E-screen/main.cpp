#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    char out[81];
    int cursor = 0;
    for (int i = 0; i < 80; ++i)
        out[i] = ' ';
    int c;
    while ((c = getc(stdin)) != '\n')
    {
        if (c == '<')
            cursor = max(0, cursor - 1);
        else
        {
            if (c != '>')
                out[cursor] = c;
            cursor = (cursor + 1) % 80;
        }
    }
    out[80] = '\0';
    cout << out;
    return 0;
}
