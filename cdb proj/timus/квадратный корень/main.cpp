#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

int nv[40000], mods[100000], numbs[100000];

int powmod (int a, int b, int p) {
	int res = 1;
	while (b)
		if (b & 1)
			res = int (res * 1ll * a % p),  --b;
		else
			a = int (a * 1ll * a % p),  b >>= 1;
	return res;
}

void findSqrt(int a, int n)
{
    int s = n - 1;
    while ((s & 1) == 0)
        s >>= 1;
    int k = s >> 1;

    for (int res = powmod(a, k + 1, n), p = powmod(nv[n], 2 * k + 1, n);;res = res * p % n)
    {
        if (res * res % n == a)
        {
            if (res < n - res)
                printf("%i %i\n", res, n - res);
            else
                printf("%i %i\n", n - res, res);
            return;
        }
    }
}

int generator(int n)
{
    for (int i = 2; i < n; ++i)
        if (powmod(i, (n - 1) >> 1, n) != 1)
            return i;
    return n - 1;
}

int main()
{
    int k;
    scanf("%i", &k);
    for (int i = 0; i < 40000; ++i)
        nv[i] = 0;
    for (int i = 0; i < k; ++i)
    {
        scanf("%i %i", numbs + i, mods + i);
        numbs[i] = numbs[i] % mods[i];
        if (!nv[mods[i]])
            nv[mods[i]] = generator(mods[i]);
    }

    for (int i = 0; i < k; ++i)
    {
        if (mods[i] == 2)
            printf("%i\n", numbs[i]);
        else
        if (powmod(numbs[i], (mods[i] - 1) >> 1, mods[i]) == mods[i] - 1)
            printf("No root\n");
        else
            findSqrt(numbs[i], mods[i]);
    }
    return 0;
}
