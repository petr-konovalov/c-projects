#include <bits/stdc++.h>

using namespace std;

#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define forn(i, n) for(int i = 0; i < n; ++i)

typedef long long ll;

const ll seed = time(0);

mt19937 gen(seed);

struct Fenvik
{
    vector<ll> tb;

    Fenvik(int size)
    {
        tb.resize(size);
    }

    void add(int index, int d)
    {
        for (int i = index; i < tb.size(); i = (i | (i + 1)))
            tb[i] += d;
    }

    ll pref(int index)
    {
        ll res = 0;
        for (int i = index; i >= 0; i = (i & (i + 1)) - 1)
            res += tb[i];
        return res;
    }
};

ll getPref(int arr[], int id)
{
    ll res = 0;
    for (int i = 0; i <= id; ++i)
        res += arr[i];
    return res;
}

bool fenvTest(int size)
{
    const int range = 137;
    int arr[size] = {0};
    Fenvik fenv(size);

    forn (i, size)
    {
        int id = gen() % size, d = gen() % range;
        arr[id] += d;
        fenv.add(id, d);
    }

    forn (i, 3 * size)
    {
        int op = gen() & 1;
        int id = gen() % size;
        if (op)
        {
            if (getPref(arr, id) != fenv.pref(id))
                return false;
        }
        else
        {
            int d = gen() % range;
            arr[id] += d;
            fenv.add(id, d);
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int size = 1000; size <= 15000; size += 1000)
    {
        if (fenvTest(size))
        {
            debug("%7i ok\n", size);
        }
        else
        {
            debug("%7i fail\n", size);
        }
    }

    return 0;
}
