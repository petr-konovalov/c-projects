#include <iostream>

using namespace std;

int main()
{
    char text[61] = "";
    unsigned long long p[60][60] = {0};
    unsigned lengthText = 0;
    cin >> text;
    while(text[lengthText] != '\0')
        ++lengthText;
    for (unsigned i = 0; i < lengthText; ++i)
    {
        for (unsigned j = 0; j < lengthText; ++j)
        {
            if (i == j)
                p[i][j] = 1;
            else
                p[i][j] = 0;
        }
    }

    for (unsigned i = 1; i < lengthText; ++i)
    {
        for (unsigned j = 0; j < lengthText - i; ++j)
        {
            unsigned m = j;
            unsigned n = j + i;
            if (text[m] == text[n])
                p[m][n] = p[m + 1][n] + p[m][n - 1] + 1;
            else
                p[m][n] = p[m + 1][n] + p[m][n - 1] - p[m + 1][n - 1];
        }
    }
    cout << p[0][lengthText - 1];
    return 0;
}
