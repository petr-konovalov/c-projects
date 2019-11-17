#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int read()
{
    int val;
    cin >> val;
    return val;
}

int main()
{
    vector<int> arr;
    int n;
    int item;
    cin >> n;
    while(n--)
        arr.push_back(read());
    sort(arr.begin(), arr.end());
    cin >> item;
    cout << (*lower_bound(arr.begin(), arr.end(), item) == item ? "Belongs\n": "Not belongs\n");
    return 0;
}
