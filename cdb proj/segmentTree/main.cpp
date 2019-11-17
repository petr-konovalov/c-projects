#include <bits/stdc++.h>

using namespace std;

#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define forn(i, n) for(int i = 0; i < n; ++i)

typedef long long ll;

const int INF = 1e9 + 7;
const int seed = 23806598;

mt19937 gen(seed);

struct node
{
    ll dv;
    int minv;

    node *left;
    node *right;

    node(int v): dv(0), minv(v), left(NULL), right(NULL){};
    node(node *left, node *right): left(left), right(right)
    {
        dv = left->dv + right->dv;
        minv = min(left->minv, right->minv);
    };
};

ll getMinv(node *t)
{
    return t->minv + t->dv;
}

void update(node *t)
{
    t->minv = min(getMinv(t->left), getMinv(t->right));
}

void push(node *t)
{
    t->left->dv += t->dv;
    t->right->dv += t->dv;
    t->minv += t->dv;
    t->dv = 0;
}

struct segTree
{
    node *root;
    int size;

    node *buildTree(vector<int> source, int l, int r)
    {
        if (l == r)
            return new node(source[l]);
        else
        {
            int mid = (l + r) >> 1;
            return new node(buildTree(source, l, mid), buildTree(source, mid + 1, r));
        }
    }

    void add(node *t, int d, int l, int r, int tl, int tr)
    {
        if (l == tl && r == tr)
            t->dv += d;
        else
        {
            push(t);
            int mid = (l + r) >> 1;
            if (tr <= mid)
                add(t->left, d, l, mid, tl, tr);
            else if (tl > mid)
                add(t->right, d, mid + 1, r, tl, tr);
            else
            {
                add(t->left, d, l, mid, tl, mid);
                add(t->right, d, mid + 1, r, mid + 1, tr);
            }
            update(t);
        }
    }

    int getMin(node *t, int l, int r, int tl, int tr)
    {
        if (l == tl && r == tr)
            return getMinv(t);
        else
        {
            push(t);
            int mid = (l + r) >> 1;
            if (tr <= mid)
                return getMin(t->left, l, mid, tl, tr);
            else if (tl > mid)
                return getMin(t->right, mid + 1, r, tl, tr);
            else
                return min(getMin(t->left, l, mid, tl, mid),
                           getMin(t->right, mid + 1, r, mid + 1, tr));
            update(t);
        }
    }

    void printTree(node *t)
    {
        if (t->left)
        {
            push(t);
            printTree(t->left);
            printTree(t->right);
            update(t);
        }
        else
            debug("%lli ", getMinv(t));
    }

    void printTree()
    {
        printTree(root);
    }

    void add(int d, int l, int r)
    {
        add(root, d, 0, size - 1, l, r);
    }

    int getMin(int l, int r)
    {
        return getMin(root, 0, size - 1, l, r);
    }

    segTree(vector<int> source)
    {
        size = source.size();
        root = buildTree(source, 0, size - 1);
    }

    void destroyTree(node *t)
    {
        if (t)
        {
            destroyTree(t->left);
            destroyTree(t->right);
            delete t;
        }
    }

    void destroyTree()
    {
        destroyTree(root);
    }
};

void add(vector<int> &a, int d, int l, int r)
{
    for (int i = l; i <= r; ++i)
        a[i] += d;
}

int getMinv(const vector<int> &a, int l, int r)
{
    int res = INF;
    for (int i = l; i <= r; ++i)
        res = min(res, a[i]);
    return res;
}

bool segTreeTest(int size)
{
    const int range = 12873;
    vector<int> source(size);
    forn (i, size)
        source[i] = gen() % range;
    segTree t(source);

    forn (i, 3 * size)
    {
        int op = gen() & 1;
        int d = gen() % range, l = gen() % size, r = gen() % size;
        if (l > r)
            swap(l, r);
        if (op)
        {
            add(source, d, l, r);
            t.add(d, l, r);
        }
        else
        {
            if (t.getMin(l, r) != getMinv(source, l, r))
                return false;
        }
    }
    t.destroyTree();
    return true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int size = 10000; size <= 50000; size += 10000)
    {
        if (segTreeTest(size))
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
