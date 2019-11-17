/*В массиве из n элементов числа образуют неубывающую последовательность.
Несколько элементов, идущих подряд, равны между собой.
 Сколько различных чисел имеется в массиве?*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    int cnt = 1;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < arr.size(); ++i)
        cin >> arr[i];

    for (int i = 0; i < arr.size() - 1; ++i)
        if (arr[i] != arr[i + 1])
            ++cnt;

    cout << cnt;
    return 0;
}
