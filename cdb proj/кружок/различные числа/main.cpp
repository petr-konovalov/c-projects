
#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define all(a) (a).begin(), (a).end()

const int N = 300050, A = 350;
int arr[N];

int read()
{
    int val;
    cin >> val;
    return val;
}

struct Request
{
    int l, r;
    int id;
    bool operator < (Request b)
    {
        int bla = l / A;
        int blb = b.l / A;
        return (bla != blb ? bla < blb : (bla & 1) ? r > b.r: r < b.r);
    }
    Request(int id): l(read() - 1), r(read() - 1), id(id){}
};
vector<Request> z;
int res[N];
int n, q;

void calcPrev()
{
    map<int, int> s;
    int cur = 1;
    forn(i, n)
    {
        auto &v = s[arr[i]];
        if (!v) v = cur++;
        arr[i] = v;
    }
}

int f[N];
void calc()
{
    int a = 0, b = 0, ans = 0;
    for (auto &v: z)
    {
        int l = v.l;
        int r = v.r;
        while (a < l) ans -= (--f[arr[a++]] == 0);
        while (b <= r) ans += (++f[arr[b++]] == 1);
        while (a > l) ans += (++f[arr[--a]] == 1);
        while (b - 1 > r) ans -= (--f[arr[--b]] == 0);
        res[v.id] = ans;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    forn(i, n)
        arr[i] = read();
    calcPrev();
    cin >> q;
    forn(i, q)
        z.push_back(Request(i));
    sort(all(z));
    calc();
    forn(i, q)
        printf("%d\n", res[i]);
    return 0;
}
