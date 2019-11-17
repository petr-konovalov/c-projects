#include <iostream>
#include <vector>
#include <list>

#define tr(c, it) \
    for(typeof(c.begin()) it=c.begin(); it != c.end(); ++it)

using namespace std;

void f(const vector<int>& v) {
   tr(v, it)
      cout << *it << ' ';
}

void f2(const vector<int>& v) {
    for(vector<int>::const_iterator it = v.begin(); it < v.end(); ++it)
        cout << *it << ' ';
}

int main()
{
    list<int> l;
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int a;
        cin >> a;
        l.push_back(a);
    }
    vector<int> v(l.begin(), l.end());
    f(v);
    return 0;
}
