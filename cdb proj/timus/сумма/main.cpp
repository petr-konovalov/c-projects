#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cin >> n;
    if (n > 0)
        cout << n * (n + 1) / 2;
    else
        cout << (n + 1) * abs(n - 2) / 2;
    return 0;
}
