#include <stdio.h>
#include <string.h>

using namespace std;

unsigned long long C[32][32];
unsigned long long A[32][32];

void initC()
{
    for (int n = 0; n < 32; ++n)
        C[n][0] = 1;
    for (int n = 0; n < 32; ++n)
        for (int k = 1; k < 32; ++k)
            if (k > n)
                C[n][k] = 0;
            else
                C[n][k] = C[n - 1][k] + C[n - 1][k - 1];
}

void initA()
{
    A[0][0] = 2;
    for (int k = 1; k < 32; ++k)
        A[0][k] = 0;
    for (int k = 0; k < 32; ++k)
        for (int b = 1; b < 32; ++b)
            A[b][k] = C[b][k] + A[b - 1][k];
}

int main()
{
    initC();
    initA();
    unsigned int n;
    int k;
    bool bits[32] = {false};
    scanf("%u %i", &n, &k);
    int cbit = 0;
    while (n)
    {
        bits[cbit] = (n & 1);
        ++cbit;
        n >>= 1;
    }
    --cbit;
    if (cbit == 0 || k > 31)
        printf("0");
    else
    {
        --cbit;
        unsigned long long res = A[cbit][k];
        while (cbit >= 0 && k > 0)
        {
            if (bits[cbit])
                res += C[cbit][k - 1];
            else
                --k;
            --cbit;
        }
        if (cbit == -1 && k == 0)
            ++res;
        printf("%llu", res);
    }
    return 0;
}
