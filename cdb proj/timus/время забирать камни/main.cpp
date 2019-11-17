#include <iostream>

using namespace std;

int main()
{
    int n, m;
    int k[50];
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
        cin >> k[i];

    for (int i = 1; i < m; ++i)
        for (int j = i; j > 0 && k[j] < k[j - 1]; --j)
            swap(k[j], k[j - 1]);
    bool state[100001];
    state[0] = true;
    for (int s = k[0]; s <= n; s += k[0])
    {
        state[s] = false;
        for (int i = 0; i < m && s - k[i] >= 0 && !state[s]; ++i)
            state[s] = !state[s - k[i]];
    }
    cout << (state[n] ? 1 : 2);
    return 0;
}
