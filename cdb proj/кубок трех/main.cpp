#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int w;
    cin >> w;
    cout << ((w & 1) || w == 2 ? "NO": "YES");
    return 0;
}
