#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct
{
    long long e[2][2];
} Matr;

Matr multMatr(const Matr fmatr, const Matr smatr)
{
    Matr r;
    r.e[0][0] = fmatr.e[0][0] * smatr.e[0][0] + fmatr.e[0][1] * smatr.e[1][0];
    r.e[1][0] = fmatr.e[1][0] * smatr.e[0][0] + fmatr.e[1][1] * smatr.e[1][0];
    r.e[0][1] = fmatr.e[0][0] * smatr.e[0][1] + fmatr.e[0][1] * smatr.e[1][1];
    r.e[1][1] = fmatr.e[1][0] * smatr.e[0][1] + fmatr.e[1][1] * smatr.e[1][1];
    return r;
}

Matr binPow(Matr matr, long long deg, long long M)
{
    Matr r;
    r.e[0][0] = r.e[1][1] = 1;
    r.e[1][0] = r.e[0][1] = 0;
    while (deg)
    {
        if (deg & 1)
            r = multMatr(r, matr);
        matr = multMatr(matr, matr);
        deg >>= 1;
    }
    return r;
}

int main()
{
    Matr f;
    long long M, N, K;
    cin >> N >> K;
    f.e[0][0] = 0;
    f.e[1][0] = 1;
    f.e[1][1] = f.e[0][1] = K - 1;
    f = binPow(f, N);
    printf("%lli", f.e[1][1]);
    return 0;
}
