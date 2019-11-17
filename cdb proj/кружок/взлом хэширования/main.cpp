#include <bits/stdc++.h>

using namespace std;

const long long sSize = 4096;
char str[sSize];
long long p, q;
pair<long long, int> d[sSize];

long long multMod(long long a, long long b, long long mod)
{
    long long res = 0;
    while (b)
    {
        if (b & 1)
        {
            res += a;
            if (res > mod)
                res -= mod;
        }
        a += a;
        if (a > mod)
            a -= mod;
        b >>= 1;
    }
    return res;
}

vector<int> getAns(pair<long long, int> *d, int cSize)
{
    sort(d, d + cSize);
    int nSize = cSize >> 1;
    pair<long long, int> *nd = new pair<long long, int>[nSize];
    for (int i = 0; i < nSize; ++i)
    {
        nd[i] = make_pair(d[i * 2 + 1].first - d[i * 2].first, i);
        if (nd[i].first == 0)
        {
            vector<int> res(2);
            res[0] = d[i * 2 + 1].second;
            res[1] = d[i * 2].second;
            return res;
        }
    }
    vector<int> res = getAns(nd, nSize);
    vector<int> nres(res.size() * 2);
    for (int i = 0; i < res.size(); ++i)
    {
        nres[i * 2] = d[res[i] * 2 + 1].second;
        nres[i * 2 + 1] = d[res[i] * 2].second;
        if (i & 1)
            swap(nres[i * 2], nres[i * 2 + 1]);
    }
    delete[] nd;
    return nres;
}

int main()
{
    cin >> p >> q;
    d[0] = make_pair(1, 0);
    for (int i = 1; i < sSize; ++i)
        d[i] = make_pair(multMod(d[i - 1].first, p, q), i);
    vector<int> res = getAns(d, sSize);
    for (int i = 0; i < sSize; ++i)
        str[i] = 'b';
    str[sSize] = '\0';
    cout << str << endl;
    for (int i = 0; i < res.size(); ++i)
        if (i & 1)
            str[sSize - 1 - res[i]] = 'a';
        else
            str[sSize - 1 - res[i]] = 'c';
    cout << str;
    return 0;
}
