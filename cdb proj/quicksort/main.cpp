#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

void Swap (int *a, int *b)
{
    if (*a ^ *b) *a^=*b^=*a^=*b;
}

void QuickSort (int *a, int n)
{
    int p = a[n >> 1];
    int i = 0;
    int j = n - 1;

    while (i <= j)
    {
        while (a[i] < p) ++i;
        while (a[j] > p) --j;
        if (i <= j)
        {
            Swap(&a[i], &a[j]);
            ++i;
            --j;
        }
    }

    if (i < n - 1) QuickSort(&a[i], n - i);
    if (j > 0) QuickSort(&a[0], j + 1);
}

void QuickPartSort (int *a, int n)
{
    if (n > 5)
    {
        int p = a[n >> 1];
        int i = 0;
        int j = n - 1;

        while (i <= j)
        {
            while (a[i] < p) ++i;
            while (a[j] > p) --j;
            if (i <= j)
            {
                Swap(&a[i], &a[j]);
                ++i;
                --j;
            }
        }

        if (i < n - 1) QuickPartSort(&a[i], n - i);
        if (j > 0) QuickPartSort(&a[0], j + 1);
    }
}

void InsertSort (int *a, int n)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < n; ++i)
    {
        j = i;
        while (j > 0 && a[j] < a[j - 1])
        {
            Swap (&a[j], &a[j - 1]);
            --j;
        }
    }
}

void PrintArray (int *a, int n)
{
    int i = 0;
    for (i = 0; i < n; ++i)
        printf("%i ", a[i]);
    printf("\n");
}

int main()
{
    int n = 200000;

    int a[n], b[n];
    int i = 0;

    int t = clock();

    for (i = 0; i < n; ++i)
    {
        a[i] = i;
        b[i] = i;
    }

    srand(time(0));

    for (i = n - 1; i > 0; --i)
    {
        int NextValue = rand() % i;
        Swap(&a[i], &a[NextValue]);
        Swap(&b[i], &b[NextValue]);
    }

    printf("%i\n", clock() - t);

    t = clock();

    QuickPartSort(a, n);
    InsertSort(a, n);

    printf("%i\n", clock() - t);

    t = clock();

    QuickSort(b, n);

    printf("%i", clock() - t);

    return 0;
}

