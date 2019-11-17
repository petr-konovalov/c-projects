#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

long long x[1500], y[1500];

long long dist(int i, int j)
{
    return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

long long trianS(int i, int j, int k)
{
    long long x1 = x[j] - x[i], x2 = x[k] - x[i], y1 = y[j] - y[i], y2 = y[k] - y[i];
    return x1 * y2 - x2 * y1;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> x[i] >> y[i];

    long long res = 0;
    vector<pair<long long, int> > len;
    len.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        len.clear();
        for (int j = 0; j < n; ++j)
            len.push_back(make_pair(dist(i, j), j));
        sort(len.begin(), len.end());
        int l = 1, r = 2;
        set<pair<long long, long long> > diam;
        while (l < n)
        {
            while (r < n && len[l].first == len[r].first)
                ++r;
            res += ((r - l) * (r - l - 1) >> 1);
            diam.clear();
            for (int j = l; j < r; ++j)
            {
                int id = len[j].second;
                if (diam.find(make_pair(2 * x[i] - x[id], 2 * y[i] - y[id])) != diam.end())
                    --res;
                else
                    diam.insert(make_pair(x[id], y[id]));
            }
            l = r;
            ++r;
        }
    }
    cout << res;
    return 0;
}
