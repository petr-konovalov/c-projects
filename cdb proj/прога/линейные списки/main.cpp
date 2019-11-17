#include <iostream>
#include <list>
#include <vector>

using namespace std;

int read()
{
    int val;
    cin >> val;
    return val;
}

list<list<int>::iterator> getSubList(list<int> &arr)
{
    int maxPrime = arr.size();
    vector<bool> isPrime(maxPrime + 1, true);
    list<list<int>::iterator> subList;
    auto v = arr.begin();
    isPrime[1] = false;
    for (int i = 1; i <= maxPrime; ++i, ++v)
    {
        if (isPrime[i])
        {
            subList.push_back(v);
            for (int j = i * i; j <= maxPrime; j += i)
                isPrime[j] = false;
        }
    }
    return subList;
}

void sortPrimesIndex(list<int> &arr)
{
    list<list<int>::iterator> subList = getSubList(arr);
    bool status = true;

    while (status)
    {
        status = false;
        for (auto v = subList.begin(), p = v++; v != subList.end(); ++v, ++p)
        {
            if (**p > **v)
            {
                status = true;
                swap(**p, **v);
            }
        }
    }
}

int main()
{
    list<int> arr;
    int n;
    cin >> n;
    while (n--)
        arr.push_back(read());
    sortPrimesIndex(arr);
    for (auto &v: arr)
        cout << v << ' ';
    return 0;
}
