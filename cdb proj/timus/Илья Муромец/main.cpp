#include <iostream>

using namespace std;

long long log(long long arg)
{
    long long res = 0;
    while (arg > 1)
    {
        arg >>= 1;
        ++res;
    }
    return res;
}

int main()
{
    long long D, E, F, Dp, Ep, H;
    cin >> D >> E >> F >> Dp >> Ep >> H;
    long long PE = ((1 << F) + Ep - 1) >> E;
    long long PD = ((1 << F) + Dp - 1) >> D;
    long long logPD = log(PD);
    long long logPE = log(PE);
    long long res = 0;
    if (logPE > logPD)
    {
        res = logPE - logPD;
        PE >>= res;
    }
    else if (logPD > logPE)
    {
        res = logPD - logPE;
        PD >>= res;
    }
    while (PE != PD)
    {
        PE >>= 1;
        PD >>= 1;
        res += 2;
    }
    if (res <= H)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
