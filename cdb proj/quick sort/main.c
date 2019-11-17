#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void swap (int *a, int *b)
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
            swap(&a[i], &a[j]);
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
                swap(&a[i], &a[j]);
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
            swap (&a[j], &a[j - 1]);
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

long long mTime ()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (long long)tv.tv_usec + tv.tv_sec * 1000000ll;
}

int main()
{
    int n = 10000000;

    int *a,*b;
    int i = 0;

    long long t = mTime();

    a = calloc(n, sizeof(int));
    b = calloc(n, sizeof(int));

    for (i = 0; i < n; ++i)
    {
        a[i] = i;
    }

    srand(time(0));

    for (i = n - 1; i > 0; --i)
    {
        int NextValue = rand() % i;
        swap(&a[i], &a[NextValue]);
        swap(&b[i], &b[NextValue]);
    }

    printf("%15lli\n", mTime() - t);

    t = mTime();

    QuickPartSort(a, n);
    InsertSort(a, n);

    printf("%15lli\n", mTime() - t);

    t = mTime();

    QuickSort(b, n);

    printf("%15lli", mTime() - t);

    return 0;
}
