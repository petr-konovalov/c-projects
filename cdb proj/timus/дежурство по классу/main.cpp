#include <bits/stdc++.h>

using namespace std;

map<string, long long> cityStatus;
map<string, long long> richStatus;
map<string, int> ans;
set<pair<long long, string> > state;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        string name, city;
        long long status;
        cin >> name >> city >> status;
        richStatus[name] = status;
        cityStatus[city] += status;
        state.insert(make_pair(cityStatus[city], city));
    }
    int k, m;
    cin >> m >> k;
    for (int i = 0; i < k; ++i)
    {

    }
    return 0;
}
