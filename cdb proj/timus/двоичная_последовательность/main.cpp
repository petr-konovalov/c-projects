#include <iostream>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    int r[50];
    r[0] = 1;
    r[1] = 2;
    for (int i = 2; i <= n; ++i)
        r[i] = r[i - 1] + r[i - 2];

    --k;
    if (k >= r[n])
        cout << -1;
    else
    for (int i = n; i > 0; --i)
    {
        if (k >= r[i - 1])
        {
            if (i > 1)
                cout << "10";
            else
                cout << "1";
            k -= r[i - 1];
            --i;
        }
        else
            cout << "0";
    }
    return 0;
}
