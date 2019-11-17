#include <iostream>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    if (m > n)
        swap(m, n);
    if (m == 1)
        cout << (n + 1) / 2;
    else
        cout << (m * n % 3 == 0 ? 2 : 1);
    return 0;
}
