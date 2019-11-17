#include <iostream>
#include <cmath>
#define MAX_HEIGHT 10

using namespace std;

const double inf = 1.0f / 0.0f;

int compTower(double *t1, double *t2)
{

    return ct1 > ct2 ? 1 : ct1 < ct2 ? -1: 0;
}

void swapn(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

void quickSort(double *towers[MAX_HEIGHT], int *num, int l, int r)
{
    int k = num[(l + r) / 2];
    int i = l;
    int j = r;
    while (i < j)
    {
        while (compTower(towers[num[i]], towers[k]) < 0)
            ++i;
        while (compTower(towers[num[j]], towers[k]) > 0)
            --j;
        if (i <= j)
        {
            swapn(num[i], num[j]);
            ++i;
            --j;
        }
    }

    if (j > l)
        quickSort(towers, num, l, j);
    if (i < r)
        quickSort(towers, num, i, r);
}

int main()
{
    int n;
    cin >> n;
    int *k = new int[n];
    double *towers[MAX_HEIGHT];
    int *num = new int[n];

    for (int i = 0; i < n; ++i)
    {
        num[i] = i;
        towers[i] = new double[MAX_HEIGHT];
        for (int j = 0; j < MAX_HEIGHT; ++j)
            towers[i][j] = 1;
        cin >> k[i];
        for (int j = 0; j <= k[i]; ++j)
            cin >> towers[i][j];
    }

    quickSort(towers, num, 0, n - 1);
    for (int i = 0; i < n; ++i)
        cout << num[i] + 1 << ' ';
    return 0;
}
