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

struct Tree
{
    int k;
    int p;
    ll sum;

    Tree *l;
    Tree *r;

    Tree(int k, int p): k(k), p(p)
    {
        l = NULL;
        r = NULL;
    }
};

typedef pair<Tree*, Tree*> ptt;

const int P = 1e9;

ll sum(Tree *t)
{
    return t? t->sum: 0;
}

void update(Tree *t)
{
    if (t)
        t->sum = sum(t->l) + sum(t->r) + t->k;
}

pair<Tree*, Tree*> split(Tree *t, int k)
{
    if (t == NULL)
        return mp((Tree*)NULL, (Tree*)NULL);

    if (t->k >= k)
    {
        ptt sp = split(t->l, k);
        t->l = sp.S;
        update(t);
        return mp(sp.F, t);
    }
    else
    {
        ptt sp = split(t->r, k);
        t->r = sp.F;
        update(t);
        return mp(t, sp.S);
    }
}

Tree* merge(Tree *t1, Tree *t2)
{
    if (t1 == NULL)
        return t2;
    if (t2 == NULL)
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

Tree* insert(Tree *t, int k, int p)
{
    if (t == NULL || t->p < p)
    {
        ptt sp = split(t, k);
        t = new Tree(k, p);
        t->l = sp.F;
        t->r = sp.S;
    }
    else
    {
        if (k < t->k)
            t->l = insert(t->l, k, p);
        else
            t->r = insert(t->r, k, p);
    }
    update(t);
    return t;
}

void destroy(Tree* t)
{
    if (t == NULL)
        return;
    destroy(t->l);
    destroy(t->r);
    delete t;
}

void printTree(Tree* t)
{
    if (t == NULL)
        return;
    printTree(t->l);
    cout << t->p << ' ';
    printTree(t->r);
}

ll sum(Tree* t, int l, int r)
{
    ptt sp1 = split(t, r + 1);
    ptt sp2 = split(sp1.F, l);
    ll res = sum(sp2.S);
    t = merge(merge(sp2.F, sp2.S), sp1.S);

    return res;
}

ll seed = time(0);
mt19937 gen(seed);
Tree *t = NULL;
int n;
ll y = 0;
set<int> used;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    debug("%ld\n", seed);

    freopen("sum2.in", "r", stdin);
    freopen("sum2.out", "w", stdout);

    cin >> n;

    vector<int> p(n);
    forn (i, n)
        p[i] = i;
    shuffle(p.begin(), p.end(), gen);

    forn (i, n)
    {
        char c;
        cin >> c;
        if (c == '+')
        {
            int k;
            cin >> k;
            int v = (k + y) % P;
            if (used.find(v) == used.end())
            {
                t = insert(t, v, p[i]);
                used.ins(v);
            }
            y = 0;
        }
        else
        {
            int l, r;
            cin >> l >> r;
            y = sum(t, l, r);
            cout << y << '\n';
        }
    }

    destroy(t);
    return 0;
}
