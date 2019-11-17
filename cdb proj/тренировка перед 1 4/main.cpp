#include <bits/stdc++.h>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool comp(pair<string, int> a, pair<string, int> b)
{
    return a.second > b.second;
}

int main()
{
    freopen("bad.in", "r", stdin);
    freopen("bad.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    vector<pair<string, int> > in;
    int n, m;
    cin >> n >> m;
    in.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> in[i].first;
    int inv = 0;
    for (int i = 0; i < m; ++i)
    {
        string b;
        cin >> b;
        int xc = 0;
        int xi = 0;
        for (int i = 0; i < b.size(); ++i)
            if (b[i] == 'X')
            {
                ++xc;
                xi = i;
            }
        if (xc == 1)
            ++in[xi].second;
        else
            ++inv;
    }
    stable_sort(in.begin(), in.end(), comp);
    for (int i = 0; i < n; ++i)
    {
        printf("%s %.2f%%\n", (in[i].first.c_str()), 100.0 * in[i].second / m);
    }
    printf("Invalid %.2f%%", 100.0 * inv / m);
    return 0;
}
