
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
typedef float fl;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 2e5 + 4, INF = 1e9 + 7;

struct Tree
{
    int c;
    int p;
    int v;
    int minv;
    Tree *l, *r;

    Tree(int c, int p, int v): c(c), p(p), v(v)
    {
        l = NULL;
        r = NULL;
    }
};

typedef Tree* pTree;
typedef pair<pTree, pTree> ptt;

int cnt(pTree t)
{
    return t? t->c: 0;
}

int minv(pTree t)
{
    return t? t->minv: INF;
}

void update(pTree t)
{
    if (t)
    {
        t->c = cnt(t->l) + cnt(t->r) + 1;
        t->minv = min(min(minv(t->l), minv(t->r)), t->v);
    }
}

ptt split(pTree t, int k)
{
    if (t == NULL)
        return mp((pTree)NULL, (pTree)NULL);
    int ls = cnt(t->l);
    if (ls >= k)
    {
        ptt sp = split(t->l, k);
        t->l = sp.S;
        update(t);
        return mp(sp.F, t);
    }
    else
    {
        ptt sp = split(t->r, k - ls - 1);
        t->r = sp.F;
        update(t);
        return mp(t, sp.S);
    }
}

pTree merge(pTree t1, pTree t2)
{
    if (!t1)
        return t2;
    if (!t2)
        return t1;
    if (t1->p < t2->p)
    {
        t2->l = merge(t1, t2->l);
        update(t2);
        return t2;
    }
    else
    {
        t1->r = merge(t1->r, t2);
        update(t1);
        return t1;
    }
}

void insert(pTree &t, int pos, int p, int v)
{
    if (!t || t->p < p)
    {
        ptt sp = split(t, pos);
        t = new Tree(0, p, v);
        t->l = sp.F;
        t->r = sp.S;
    }
    else
    {
        int ls = cnt(t->l);
        if (ls >= pos)
            insert(t->l, pos, p, v);
        else
            insert(t->r, pos - ls - 1, p, v);
    }
    update(t);
}

void printTree(pTree t)
{
    if (!t)
        return;
    printTree(t->l);
    cout << t->v << ' ';
    printTree(t->r);
}

void destroy(pTree &t)
{
    if (!t)
        return;
    destroy(t->l);
    destroy(t->r);
    delete t;
    t = NULL;
}

int getMin(pTree &t, int l, int r)
{
    ptt sp1 = split(t, r);
    ptt sp2 = split(sp1.F, l - 1);
    int ans = sp2.S->minv;
    t = merge(merge(sp2.F, sp2.S), sp1.S);
    return ans;
}

ll seed = time(0);
mt19937 gen(seed);
vector<int> p;
pTree t = NULL;
int n, m;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    debug("%ld\n", seed);
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    cin >> n;
    p.resize(n);
    forn (i, n)
        p[i] = i;
    shuffle(p.begin(), p.end(), gen);
    forn (i, n)
    {
        char c;
        int a, b;
        cin >> c >> a >> b;
        if (c == '+')
        {
            insert(t, a, p[i], b);
        }
        else
        {
            cout << getMin(t, a, b) << '\n';
            //debug("%i\n", getMin(t, a, b));
        }
    }
    destroy(t);
    return 0;
}
