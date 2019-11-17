#include <iostream>

using namespace std;

int main()
{
    bool links[100][100] = {false};
    int part[100];

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int c;
        part[i] = -1;
        cin >> c;
        while (c != 0)
        {
            links[i][c - 1] = true;
            cin >> c;
        }
    }

    int c = 0;
    for (int i = 0; i < n; ++i)
    {
        if (part[i] == -1)
        {
            ++c;
            part[i] = 0;
            for (int j = i + 1; j < n; ++j)
                if (links[j][i] && part[j] == -1)
                    part[j] = 1;
        }
    }

    cout << c << '\n';
    for (int i = 0; i < n; ++i)
        if (part[i] == 0)
            cout << i + 1 << ' ';
    return 0;
}
