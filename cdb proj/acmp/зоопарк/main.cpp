#include <iostream>

using namespace std;

int main()
{
    unsigned long long zoo[1000] = {0};
    unsigned long long a[4][1000] = {0};
    int N = 0;
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        cin >> zoo[i];
        a[0][i] = 1;
    }
    for (int i = 1; i < 4; ++i)
    {
        a[i][0] = zoo[0];
        for (int j = 1; j < i; ++j)
            a[i][j] = a[i][j - 1] * zoo[j];
        for (int j = i; j < N; ++j)
            a[i][j] = a[i - 1][j - 1] * zoo[j] + a[i][j - 1];
    }
    if (N < 3)
        cout << 0;
    else
        cout << a[3][N - 1];
    return 0;
}
