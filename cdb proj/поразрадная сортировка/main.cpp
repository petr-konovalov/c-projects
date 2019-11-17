#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>

using namespace std;

void splitMerge(vector<int> &a, int bit, int rev = 0)
{
    vector<int> b[2];
    for (int i = 0; i < a.size(); ++i)
        b[(a[i] >> bit) & 1].push_back(a[i]);
    a.clear();
    for (int j = 0; j < 2; ++j)
        for (int i = 0; i < b[j ^ rev].size(); ++i)
            a.push_back(b[j ^ rev][i]);
}

void psort(vector<int> &a, int maxbit)
{
    for (int bit = 0; bit < maxbit - 1; ++bit)
        splitMerge(a, bit);
    splitMerge(a, maxbit - 1, 1);
}

vector<int> generateArr(int n)
{
    vector<int> r(n);
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        r[i] = (rand() & 0xFFFF) * (rand() & 1 ? 1 : -1);
        cout << r[i] << ' ';
    }
    cout << endl;
    return r;
}

int main()
{
    int n = 0;
    vector<int> a;
    cin >> n;
    a = generateArr(n);

    psort(a, 32);
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    return 0;
}
