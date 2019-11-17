#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define ins insert
#define ers erase

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e5 + 20, P = 1e9 + 7, M = 1e6 + 20;
const ll seed = 8098232482812;

struct Tree
{
    int v;
    int c;
    int sum;
    Tree *l, *r;

    Tree (int v): v(v)
    {
        l = NULL;
        r = NULL;
        c = 1;
        sum = v;
    }

    Tree (Tree* t)
    {
        v = t->v;
        l = t->l;
        r = t->r;
        c = t->c;
        sum = t->sum;
    }
};

typedef Tree* pTree;
typedef pair<pTree, pTree> ptt;

pTree rev[M];
int cnt = 0;
mt19937 gen(seed);

int n, m;

int sum(pTree t)
{
    return t? t->sum: 0;
}

int sz(pTree t)
{
    return t? t->c: 0;
}

void update(pTree t)
{
    if (t)
    {
        t->sum = ((ll)sum(t->l) + sum(t->r) + t->v) % P;
        t->c = sz(t->l) + sz(t->r) + 1;
    }
}

pTree cmerge(pTree t1, pTree t2)
{
    if (!t1)
        return t2;
    if (!t2)
        return t1;
    pTree t;
    if (gen() & 1)
    {
        t = new Tree(t1);
        t->r = cmerge(t1->r, t2);
    }
    else
    {
        t = new Tree(t2);
        t->l = cmerge(t1, t2->l);
    }
    update(t);
    return t;
}

ptt split(pTree t, int k)
{
    if (!t)
        return mp((pTree)NULL, (pTree)NULL);
    pTree nt = new Tree(t);
    int ls = sz(t->l);
    if (ls >= k)
    {
        ptt sp = split(t->l, k);
        nt->l = sp.S;
        update(nt);
        return mp(sp.F, nt);
    }
    else
    {
        ptt sp = split(t->r, k - ls - 1);
        nt->r = sp.F;
        update(nt);
        return mp(nt, sp.S);
    }
}

ptt head(pTree t)
{
    pTree nt = new Tree(t);
    if (t->l)
    {
        ptt sp = head(t->l);
        nt->l = sp.S;
        update(nt);
        return mp(sp.F, nt);
    }
    else
    {
        nt->r = NULL;
        update(nt);
        return mp(nt, t->r);
    }
}

ptt tail(pTree t)
{
    pTree nt = new Tree(t);
    if (t->r)
    {
        ptt sp = tail(t->r);
        nt->r = sp.F;
        update(nt);
        return mp(nt, sp.S);
    }
    else
    {
        nt->l = NULL;
        update(nt);
        return mp(t->l, nt);
    }
}

pTree merge(pTree t1, pTree t2)
{
    int s1 = sz(t1);
    int s2 = sz(t2);

    if (s1 + s2 >= 10 * N)
    {
        pTree t = cmerge(t1, t2);
        ptt sp1 = split(t, N);
        ptt sp2 = split(sp1.S, sp1.S->c - N);

        pTree node = new Tree(sp2.F->sum);
        return cmerge(sp1.F, cmerge(node, sp2.S));
    }
    else
        return cmerge(t1, t2);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    debug("%ld\n", seed);
    srand(seed);
    cin >> n;

    forn (i, n)
    {
        int v;
        cin >> v;
        rev[i] = new Tree(v);
    }
    cnt = n;

    cin >> m;
    forn (i, m)
    {
        string com;
        cin >> com;
        if (com[0] == 'm')
        {
            int a, b;
            cin >> a >> b;
            rev[cnt++] = merge(rev[a - 1], rev[b - 1]);
        }
        else if (com[0] == 'h')
        {
            int a;
            cin >> a;
            ptt sp = head(rev[a - 1]);
            rev[cnt++] = sp.F;
            rev[cnt++] = sp.S;
        }
        else
        {
            int a;
            cin >> a;
            ptt sp = tail(rev[a - 1]);
            rev[cnt++] = sp.F;
            rev[cnt++] = sp.S;
        }
    }
    for (int i = n; i < cnt; ++i)
        cout << rev[i]->sum << '\n';
    return 0;
}
