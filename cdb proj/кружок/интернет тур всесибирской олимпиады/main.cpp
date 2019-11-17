#include <bits/stdc++.h>

using namespace std;

bool cmp(pair<double, double> a, pair<double, double> b)
{
    return a.first > b.first;
}

pair<double, double> a[100000];

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int M;
    scanf("%i", &M);
    for (int i = 0; i < M; ++i)
    {
        int N;
        double L;
        scanf("%i %lf", &N, &L);
        L *= 1e3;
        for (int j = 0; j < N; ++j)
        {
            scanf("%lf %lf", &a[j].first, &a[j].second);
            a[j].second /= 1e6;
        }
        sort(a, a + N, cmp);
        /*
        for (int j = 0; j < N; ++j)
            printf("%lf %lf\n", a[j].first, a[j].second);
            */
        int j = 0;
        double S = 0;
        double nS = 0;
        double v = 0;
        double t = 0;
        while (j < N && (nS = S + v * a[j].second + a[j].first * a[j].second * a[j].second / 2) < L)
        {
            S = nS;
            v += a[j].first * a[j].second;
            t += a[j].second;
            ++j;
        }
        double dS = L - S;
        double dt;
        if (j < N)
            dt = (-v + sqrt(v * v + 2 * a[j].first * dS)) / a[j].first;
        else
            dt = dS / v;
        printf("%.9lf\n", t + dt);
    }
    return 0;
}
