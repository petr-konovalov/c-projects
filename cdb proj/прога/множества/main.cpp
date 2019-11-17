#include <iostream>
#include <set>

using namespace std;

int main()
{
    set<int> nums;
    int n;
    cin >> n;
    while (n--)
    {
        int cur;
        cin >> cur;
        if (nums.find(cur) != nums.end())
            cout << "YES\n";
        else
        {
            cout << "NO\n";
            nums.insert(cur);
        }
    }
    return 0;
}
