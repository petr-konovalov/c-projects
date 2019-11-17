#include <iostream>
#include <stdio.h>

using namespace std;

void add_q(int *q, int value, int &qsize)
{
    q[qsize] = value;
    int i = qsize++;
    int j = (i - 1) / 2;

    while (i > 0 && value > q[j])
    {
        swap(q[i], q[j]);
        i = j;
        j = (i - 1) / 2;
    }
}

int get_q(int *q, int &qsize)
{
    int value = q[0];

    q[0] = q[--qsize];

    int i = 0;
    int j = i;

    while (i * 2 + 1 <= qsize)
    {
        if (q[i * 2 + 1] > q[j])
            j = i * 2 + 1;
        if (i * 2 + 2 <= qsize && q[i * 2 + 2] > q[j])
            j = i * 2 + 2;
        if (i == j)
            break;
        swap(q[i], q[j]);
        i = j;
    }
    return value;
}

int main()
{
    int n;
    scanf("%i", &n);
    int qsize = 0;
    int e = n / 2 + 1;
    int q[e];

    for (int i = 0; i < e; ++i)
    {
        int a;
        scanf("%i", &a);
        add_q(q, a, qsize);
    }

    for (int i = e; i < n; ++i)
    {
        int a;
        scanf("%i", &a);
        if (a < q[0])
        {
            get_q(q, qsize);
            add_q(q, a, qsize);
        }
    }

    if (n % 2 == 1)
        printf("%i", get_q(q, qsize));
    else
        printf("%.1lf", (double)get_q(q, qsize) / 2 + (double)get_q(q, qsize) / 2);

    return 0;
}
