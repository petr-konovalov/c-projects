#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define mp make_pair
#define pb push_back
#define X first
#define Y second

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int INF = 1e9 + 7;

int n, m;

struct Tree
{
    int key, sz;
    ll sum;
    bool rev;
    Tree *l, *r;

    Tree(int key): key(key), l(NULL), r(NULL), sz(1), sum(key), rev(false){};
};

struct ptt
{
    Tree *first, *second;

    ptt(Tree *first, Tree *second): first(first), second(second){};
};

int getSz(Tree *t)
{
    return t? t->sz: 0;
}

ll getSum(Tree *t)
{
    return t? t->sum: 0;
}

void update(Tree *t)
{
    if (t)
    {
        t->sz = getSz(t->l) + getSz(t->r) + 1;
        t->sum = getSum(t->l) + getSum(t->r) + t->key;
    }
}

void push(Tree *t)
{
    if (t->rev)
    {
        t->rev = false;
        swap(t->l, t->r);
        if (t->l)
            t->l->rev = !t->l->rev;

        if (t->r)
            t->r->rev = !t->r->rev;
    }
}

ptt split(Tree *t, int pos, int cur = 0)
{
    if (t == NULL)
        return ptt(NULL, NULL);
    push(t);

    int cpos = getSz(t->l) + cur + 1;

    if (cpos <= pos)
    {
        ptt res = split(t->r, pos, cpos);
        t->r = res.first;
        update(t);
        return ptt(t, res.second);
    }
    else
    {
        ptt res = split(t->l, pos, cur);
        t->l = res.second;
        update(t);
        return ptt(res.first, t);
    }
}

Tree* mergeTree(Tree *t1, Tree *t2)
{
    if (t1 == NULL)
        return t2;
    if (t2 == NULL)
        return t1;
    push(t1);
    push(t2);

    if (rand() % (t1->sz + t2->sz) < t1->sz)
    {
        t1->r = mergeTree(t1->r, t2);
        update(t1);
        return t1;
    }
    else
    {
        t2->l = mergeTree(t1, t2->l);
        update(t2);
        return t2;
    }
}

Tree* addItem(Tree *t, int key)
{
    return mergeTree(t, new Tree(key));
}

Tree* rev(Tree *t, int l, int r)
{
    ptt sp1 = split(t, r);
    ptt sp2 = split(sp1.first, l - 1);
    sp2.second->rev = true;
    return mergeTree(mergeTree(sp2.first, sp2.second), sp1.second);
}

ll getSum(Tree *&t, int l, int r)
{
    ptt sp1 = split(t, r);
    ptt sp2 = split(sp1.first, l - 1);
    ll res = getSum(sp2.second);
    t = mergeTree(mergeTree(sp2.first, sp2.second), sp1.second);
    return res;
}

void printTree(Tree *t)
{
    if (t == NULL)
        return;
    push(t);
    printTree(t->l);
    //cout << t->key << ' ';
    debug("%i ", t->key);
    printTree(t->r);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    Tree *t = NULL;
    srand(8284);

    cin >> n >> m;
    forn (i, n)
    {
        int num;
        cin >> num;
        t = addItem(t, num);
    }

    forn (i, m)
    {
        int q, l, r;
        cin >> q >> l >> r;
        if (q == 0)
            cout << getSum(t, l, r) << '\n';
        else
        {
            t = rev(t, l, r);
        }
        //printTree(t);
        //debug("\n");
    }

    return 0;
}
