#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define NAN NAN9823

typedef unsigned int ui;
typedef unsigned char uc;
typedef unsigned long long ull;
typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e6 + 15, M = 220e5, CS = M - 50000;
const ll seed = 7387198;
const int NAN = M + 1;

int x[N];

struct Tree
{
    int c;
    int v;
    ll sum;
    int l;
    int r;

    void init(int nc, int nv, ll nsum, int nl, int nr)
    {
        c = nc;
        v = nv;
        sum = nsum;
        l = nl;
        r = nr;
    }
};

typedef Tree *pTree;

Tree mem[M + 2];
int ms = 0;

int nTree(int v)
{
    mem[ms].init(1, v, v, NAN, NAN);
    return ms++;
}

int cpyTree(int t)
{
    mem[ms] = mem[t];
    return ms++;
}

mt19937 gen(seed);

void update(pTree t)
{
    t->c = mem[t->l].c + mem[t->r].c + 1;
    t->sum = mem[t->l].sum + mem[t->r].sum + t->v;
}

int smerge(int t1, int t2)
{
    if (t1 == NAN)
        return t2;
    if (t2 == NAN)
        return t1;
    pTree p1 = mem + t1;
    pTree p2 = mem + t2;
    if (gen() % (p1->c + p2->c) < p1->c)
    {
        p1->r = smerge(p1->r, t2);
        update(p1);
        return t1;
    }
    else
    {
        p2->l = smerge(t1, p2->l);
        update(p2);
        return t2;
    }
}

int merge(int t1, int t2)
{
    if (t1 == NAN)
        return t2;
    if (t2 == NAN)
        return t1;
    if (gen() % (mem[t1].c + mem[t2].c) < mem[t1].c)
    {
        int t = cpyTree(t1);
        pTree p = mem + t;
        p->r = merge(p->r, t2);
        update(p);
        return t;
    }
    else
    {
        int t = cpyTree(t2);
        pTree p = mem + t;
        p->l = merge(t1, p->l);
        update(p);
        return t;
    }
}

int splitL(int t, int k)
{
    if (t == NAN)
        return NAN;
    pTree p = mem + t;
    int ls = mem[p->l].c;
    if (ls >= k)
        return splitL(p->l, k);
    else
    {
        int nt = cpyTree(t);
        pTree np = mem + nt;
        np->r = splitL(p->r, k - ls - 1);
        update(np);
        return nt;
    }
}

int splitR(int t, int k)
{
    if (t == NAN)
        return NAN;
    pTree p = mem + t;
    int ls = mem[p->l].c;
    if (ls >= k)
    {
        int nt = cpyTree(t);
        pTree np = mem + nt;
        np->l = splitR(p->l, k);
        update(np);
        return nt;
    }
    else
        return splitR(p->r, k - ls - 1);
}

int n, a, b, m, k;
int t = NAN;

void reload(int t, int ad)
{
    if (t == NAN)
        return;
    pTree p = mem + t;
    int ls = mem[p->l].c;
    x[ls + ad] = p->v;
    reload(p->l, ad);
    reload(p->r, ls + ad + 1);
}

void reload(int &t)
{
    reload(t, 0);
    ms = 0;
    t = NAN;
    forn(i, n)
        t = smerge(t, nTree(x[i]));
}

void print(int t)
{
    if (t == NAN)
        return;
    pTree p = mem + t;
    print(p->l);
    cout << p->v << ' ';
    print(p->r);
}

int getSeg(int t, int l, int r)
{
    return splitR(splitL(t, r), l - 1);
}

void print(int t, int l, int r)
{
    print(getSeg(t, l, r));
    cout << '\n';
}

void sum(int t, int l, int r)
{
    cout << mem[getSeg(t, l, r)].sum << '\n';
}

void copy(int &t, int a, int b, int len)
{
    t = merge(splitL(t, b - 1), merge(getSeg(t, a, a + len - 1), splitR(t, b + len - 1)));
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    mem[NAN].init(0, 0, 0, NAN, NAN);

    debug("%lld\n", seed);
    srand(seed);
    cin >> n >> x[0] >> a >> b >> m >> k;
    forn (i, n)
    {
        t = smerge(t, nTree(x[i]));
        x[i + 1] = ((ll)x[i] * a + b) % m;
    }
    string com;
    forn (i, k)
    {
        cin >> com;
        if (com[0] == 'o')
        {
            int l, r;
            cin >> l >> r;
            print(t, l, r);
        }
        else if (com[0] == 's')
        {
            int l, r;
            cin >> l >> r;
            sum(t, l, r);
        }
        else
        {
            int a, b, len;
            cin >> a >> b >> len;
            copy(t, a, b, len);
        }
        if (ms > CS)
            reload(t);
    }

    return 0;
}
