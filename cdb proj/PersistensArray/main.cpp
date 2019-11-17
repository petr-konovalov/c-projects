#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define sqr(x) ((x) * (x))
#define all(x) x.begin(), x.end()

typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

struct Tree
{
    int value;
    Tree *left;
    Tree *right;

    Tree(int value): value(value)
    {
        left = NULL;
        right = NULL;
    }

    Tree(Tree *left, Tree *right): left(left), right(right)
    {
        value = 0;
    }
};

Tree *build(const vector<int> &source, int l, int r)
{
    if (l == r)
        return new Tree(source[l]);
    else
    {
        int mid = (l + r) >> 1;
        return new Tree(build(source, l, mid), build(source, mid + 1, r));
    }
}

Tree *change(Tree *t, int v, int pos, int l, int r)
{
    if (l == r)
        return new Tree(v);
    else
    {
        int mid = (l + r) >> 1;
        if (pos <= mid)
            return new Tree(change(t->left, v, pos, l, mid), t->right);
        else
            return new Tree(t->left, change(t->right, v, pos, mid + 1, r));
    }
}

void printTree(Tree *t)
{
    if (t)
    {
        printTree(t->left);
        if (!t->left)
            debug("%i ", t->value);
        printTree(t->right);
    }
}

struct persistentArray
{
    vector<Tree*> versions;
    int size;

    persistentArray(const vector<int> &source)
    {
        versions.pb(build(source, 0, source.size() - 1));
        size = source.size();
    }

    void changeItem(int vnum, int pos, int v)
    {
        versions.pb(change(versions[vnum], v, pos, 0, size - 1));
    }

    void printArray(int vnum)
    {
        printTree(versions[vnum]);
    }
};

int n;
vector<int> source;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> n;
    source.resize(n);
    forn (i, n)
        cin >> source[i];
    persistentArray arr(source);

    while (true)
    {
        int op, vnum;
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> vnum;
            arr.printArray(vnum);
            debug("\n");
            break;
        case 2:
            int pos, v;
            cin >> vnum >> pos >> v;
            arr.changeItem(vnum, pos, v);
            break;
        }
    }

    return 0;
}
