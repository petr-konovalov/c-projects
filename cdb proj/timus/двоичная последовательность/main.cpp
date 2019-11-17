#include <iostream>

using namespace std;

int main()
{
    long long c[45][2] = {0};
    c[0][1] = 0;
    c[0][0] = 1;
    int N, K;
    cin >> N >> K;
    for (int i = 1; i <= N; ++i)
    {
        c[i][1] = c[i - 1][0];
        c[i][0] = c[i - 1][0] + c[i - 1][1];
    }
    K--;
    if (K >= c[N][0] + c[N][1])
        cout << -1;
    else
    {
        for (int i = N; i >= 1; --i)
        {
            if (K >= c[i][0])
            {
                cout << 1;
                K -= c[i][0];
            }
            else
                cout << 0;
        }
    }
    return 0;
}
