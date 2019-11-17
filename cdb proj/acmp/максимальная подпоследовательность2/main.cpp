#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000000000;

int a[100000];
int c[100000];
int p[100000];
vector<int> d;

void print(int j)
{
    if (j != -1)
    {
        print(p[j]);
        cout << a[j] << " ";
    }
}

int main()
{
    int n, k, b, m;
    cin >> n >> a[0] >> k >> b >> m;
    for (int i = 1; i < n; ++i)
        a[i] = (a[i - 1] * k + b) % m;
    d.push_back(-INF);
    for (int i = 1; i <= n; ++i)
        d.push_back(INF);
    int mm = 0;
    p[0] = -1;
    c[0] = -1;
    for (int i = 0; i < n; ++i)
    {
        int j = (int)(upper_bound(d.begin(), d.end(), a[i]) - d.begin());
        if (d[j - 1] < a[i] && a[i] < d[j])
        {
            d[j] = a[i];
            if (j > mm)
                mm = j;
            c[j] = i;
            p[i] = c[j - 1];
        }
    }
    print(c[mm]);
    return 0;
}
