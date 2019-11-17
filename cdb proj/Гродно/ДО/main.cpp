#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back
#define mp make_pair

typedef int T;

T op(T a, T b)
{
    return a + b;
}

struct Tree
{
    T value;
    Tree *l, *r;

    Tree(T value): value(value)
    {
        l = NULL;
        r = NULL;
    }

    Tree(Tree *l, Tree *r): l(l), r(r)
    {
        value = op(l->value, r->value);
    }
};

vector<T> arr;

void update(Tree *t)
{
    t->value = op(t->l->value, t->r->value);
}

Tree* buildTree(int l, int r)
{
    Tree *t;
    if (l == r)
    {
        return new Tree(arr[l]);
    }
    else
    {
        int mid = (l + r) >> 1;
        return new Tree(buildTree(l, mid), buildTree(mid + 1, r));
    }
}

void destroyTree(Tree *t)
{
    if (t)
    {
        destroyTree(t->l);
        destroyTree(t->r);
        delete t;
    }
}

void printTree(Tree *t, int l, int r)
{
    if (t)
    {
        int mid = (l + r) >> 1;
        printTree(t->l, l, mid);
        printTree(t->r, mid + 1, r);
        debug("%i %i %i\n", l, r, t->value);
    }
}

T getOp(Tree *t, int l, int r, int tl, int tr)
{
    if (l == tl && r == tr)
        return t->value;
    else
    {
        int mid = (tl + tr) >> 1;
        if (r <= mid)
            return getOp(t->l, l, r, tl, mid);
        else if (l > mid)
            return getOp(t->r, l, r, mid + 1, tr);
        else
            return op(getOp(t->l, l, mid, tl, mid), getOp(t->r, mid + 1, r, mid + 1, tr));
    }
}

void changeTree(Tree *t, int pos, int value, int l, int r)
{
    if (l == pos && r == pos)
    {
        t->value = value;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        changeTree(t->l, pos, value, l, mid);
    else
        changeTree(t->r, pos, value, mid + 1, r);
    update(t);
}

void debugTree()
{
    int n;
    cin >> n;
    forn (i, n)
    {
        int t;
        cin >> t;
        arr.pb(t);
    }
    Tree *t = buildTree(0, n - 1);
    while (true)
    {
        int type;
        cin >> type;
        if (type == 0)
        {
            int l, r;
            cin >> l >> r;
            debug("%i\n", getOp(t, l, r, 0, n - 1));
        }
        else if (type == 1)
        {
            int pos, value;
            cin >> pos >> value;
            changeTree(t, pos, value, 0, n - 1);
        } else if (type == 2)
        {
            printTree(t, 0, n - 1);
        } else if (type = 1000)
            break;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);



    return 0;
}
