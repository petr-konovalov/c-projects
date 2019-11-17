#include <iostream>

using namespace std;

int p[4000][4000] = {0};

void printp(char *text, const int *l, const int r)
{
    if (r > 0)
    {
        printp(text, l, l[r - 1]);
        for (int i = l[r - 1]; i < r; ++i)
            cout << text[i];
        cout << ' ';
    }
}

int main()
{
    char text[4001] = "";
    cin >> text;
    int length = 0;
    while (text[length] != '\0')
        ++length;
    for (int i = 0; i < length - 1; ++i)
    {
        p[i][i] = 1;
        if (text[i] == text[i + 1])
            p[i][i + 1] = 2;
        else
            p[i][i + 1] = 1;
    }
    p[length - 1][length - 1] = 1;
    for (int len = 3; len <= length; ++len)
    {
        for (int i = 0; i + len <= length; ++i)
        {
            int j = i + len - 1;
            p[i][j] = p[i + 1][j];
            if (p[i + 1][j - 1] == len - 2 && text[i] == text[j])
                p[i][j] = len;
        }
    }
    int mins[4000] = {0};
    int l[4001] = {0};
    int c = 1;
    mins[0] = 1;
    l[0] = 0;
    for (int i = 1; i < length; ++i)
    {
        int j = i - p[0][i] + 1;
        if (j == 0)
        {
            mins[i] = 1;
            l[c++] = 0;
        }
        else
        {
            mins[i] = mins[i - 1] + 1;
            l[c++] = i;
            while (j != i)
            {
                if (mins[i] > mins[j - 1] + 1)
                {
                    mins[i] = mins[j - 1] + 1;
                    l[c - 1] = j;
                }
                j = i - p[j + 1][i] + 1;
            }
        }
    }
    cout << mins[length - 1] << '\n';
    printp(text, l, length);
    return 0;
}
