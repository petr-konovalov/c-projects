#include <bits/stdc++.h>

using namespace std;

#define N 5000100

typedef long long ll;

ll sig[N];
ll sum[N];

int main()
{
    for (ll i = 1; i <= N; ++i)
        for (ll j = i; j <= N; j += i)
            sig[j] += i;
    sum[0] = 0;
    for (ll i = 1; i <= N; ++i)
        sum[i] = sum[i - 1] + sig[i];
    int a, b;
    while (scanf("%i %i", &a, &b) == 2)
        printf("%I64d\n", sum[b] - sum[a - 1]);
    return 0;
}
