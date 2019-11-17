#include <iostream>
#include <cmath>
#define MAX_HEIGHT 16

using namespace std;

const double inf = 1.0f / 0.0f;

double calcTower(double tower[MAX_HEIGHT], int height)
{
    double result = tower[height - 1];

    for (int i = height - 2; i >= 0; --i)
    {
        if (result == inf)
            break;

        result = pow(tower[i], result);
    }

    return result;
}

int compTower(double t1[MAX_HEIGHT], double t2[MAX_HEIGHT])
{
    int level = 0;

    while (calcTower(&t1[level], MAX_HEIGHT - 1 - level) == inf && calcTower(&t2[level], MAX_HEIGHT - 1 - level) == inf)
        ++level;

    double ct1 = calcTower(&t1[level], MAX_HEIGHT - 1 - level);
    double ct2 = calcTower(&t2[level], MAX_HEIGHT - 1 - level);
    if (level > 0)
    {
        ct1 *= log(t1[level - 1]);
        ct2 *= log(t2[level - 1]);
        if (level > 1)
        {
            ct1 += log(t1[level - 2]);
            ct2 += log(t2[level - 2]);
        }
    }

    return ct1 > ct2 ? 1 : ct1 < ct2 ? -1: 0;
}

void quickSort(double *towers[MAX_HEIGHT], int *num, int l, int r)
{
    int k = num[(l + r) / 2];
    int i = l;
    int j = r;
    while (i <= j)
    {
        while (compTower(towers[num[i]], towers[k]) < 0)
            ++i;
        while (compTower(towers[num[j]], towers[k]) > 0)
            --j;
        if (i <= j)
        {
            swap(num[i], num[j]);
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
        int t = -1;
        for (int j = 0; j <= k[i]; ++j)
        {
            cin >> towers[i][j];
            if (t == -1 && towers[i][j] == 1)
                t = j;
        }
        if (t != -1)
            for (int j = t + 1; j <= k[i]; ++j)
                towers[i][j] = 1;
    }

    quickSort(towers, num, 0, n - 1);
    for (int i = 0; i < n; ++i)
        cout << num[i] + 1 << ' ';
    return 0;
}
