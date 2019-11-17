#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int l[5000];
    int r[5000];
    char c[5000];
    vector<int> b;
    int n;
    cin >> n;
    b.push_back(0);
    b.push_back(1000000000);
    for (int i = 0; i < n; ++i)
    {
        cin >> l[i] >> r[i] >> c[i];
        b.push_back(l[i]);
        b.push_back(r[i]);
    }
    sort(b.begin(), b.end());
    b.resize(unique(b.begin(), b.end()) - b.begin());
    int resl = 0;
    int resr = 0;
    int cl = 0;
    int cr = 0;
    for (int i = 1; i < b.size(); ++i)
    {
        bool f = true;
        for (int j = n - 1; j >= 0; --j)
            if (l[j] <= b[i - 1] && b[i] <= r[j])
            {
                f = c[j] == 'w';
                break;
            }
        if (f)
        {
            cr = b[i];
            if (cr - cl > resr - resl)
            {
                resr = cr;
                resl = cl;
            }
        }
        else
            cl = b[i];
    }
    cout << resl << " " << resr;
    return 0;
}
