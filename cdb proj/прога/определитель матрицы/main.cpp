#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<double> > mat(n, vector<double>(n));
    for (auto &s: mat)
        for (auto &v: s)
            cin >> v;
    double res = 1;
    vector<int> id(n);
    for (int i = 0; i < n; ++i)
        id[i] = i;
    for (int i = 0; i < n; ++i)
    {
        int mid = i;
        for (int j = i + 1; j < n; ++j)
            if (abs(mat[i][id[mid]]) < abs(mat[i][id[j]]))
                mid = j;
        if (mid != i)
        {
            res *= -1;
            swap(id[mid], id[i]);
        }
        for (int j = i + 1; j < n; ++j)
        {
            double mn = mat[i][id[j]] / mat[i][id[i]];
            for (int k = i; k < n; ++k)
                mat[k][id[j]] -= mn * mat[k][id[i]];
        }
    }
    for (int i = 0; i < n; ++i)
        res *= mat[i][id[i]];
    cout << res;
    return 0;
}
