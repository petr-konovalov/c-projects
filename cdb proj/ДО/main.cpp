#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define X first
#define Y second

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

struct Tree
{
    ll value;
    ll dv;

    Tree *l, *r;

    Tree(Tree *l, Tree *r): l(l), r(r)
    {
        value = min(l->value, r->value);
        dv = 0;
    };

    Tree(ll value): value(value)
    {
        dv = 0;
        l = NULL;
        r = NULL;
    };
};

Tree* buildTree(const vector<int> &source, int l, int r)
{
    if (l == r)
        return new Tree(source[l]);
    else
    {
        int mid = (l + r) >> 1;
        return new Tree(buildTree(source, l, mid), buildTree(source, mid + 1, r));
    }
}

Tree* buildTree(const vector<int> &source)
{
    return buildTree(source, 0, source.size() - 1);
}

int n, m;
vector<int> inp;
Tree *t;

ll getValue(Tree *t)
{
    return t->value + t->dv;
}

void update(Tree *t)
{
    t->value = min(getValue(t->l), getValue(t->r));
}

void push(Tree *t)
{
    t->value += t->dv;
    t->l->dv += t->dv;
    t->r->dv += t->dv;
    t->dv = 0;
}

ll getMin(Tree *t, int l, int r, int tl, int tr)
{
    if (l == tl && r == tr)
        return getValue(t);
    else
    {
        push(t);
        int mid = (tl + tr) >> 1;
        if (l > mid)
            return getMin(t->r, l, r, mid + 1, tr);
        else if (r <= mid)
            return getMin(t->l, l, r, tl, mid);
        else
            return min(getMin(t->l, l, mid, tl, mid), getMin(t->r, mid + 1, r, mid + 1, tr));
    }
}

ll getMin(Tree *t, int l, int r)
{
    if (l <= r)
        return getMin(t, l, r, 0, n - 1);
    else
        return min(getMin(t, 0, r, 0, n - 1), getMin(t, l, n - 1, 0, n - 1));
}

void change(Tree *t, int l, int r, int tl, int tr, ll dv)
{
    if (l == tl && r == tr)
        t->dv += dv;
    else
    {
        push(t);
        int mid = (tl + tr) >> 1;
        if (l > mid)
            change(t->r, l, r, mid + 1, tr, dv);
        else if (r <= mid)
            change(t->l, l, r, tl, mid, dv);
        else
        {
            change(t->l, l, mid, tl, mid, dv);
            change(t->r, mid + 1, r, mid + 1, tr, dv);
        }
        update(t);
    }
}

void change(Tree *t, int l, int r, ll dv)
{
    if (l <= r)
        change(t, l, r, 0, n - 1, dv);
    else
    {
        change(t, 0, r, 0, n - 1, dv);
        change(t, l, n - 1, 0, n - 1, dv);
    }
}

/*
void printTree(Tree *t, int l, int r)
{
    if (t == NULL)
        return;
    push(t);
    int mid = (l + r) >> 1;
    printTree(t->l, l, mid);
    debug("%i %i %lli\n", l, r, t->value);
    printTree(t->r, mid + 1, r);
}

void printArr(Tree *t, int l, int r)
{
    if (l == r)
    {
        debug("%lli ", getValue(t));
    }
    else
    {
        push(t);
        int mid = (l + r) >> 1;
        printArr(t->l, l, mid);
        printArr(t->r, mid + 1, r);
    }
}
*/

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    inp.resize(n);
    forn (i, n)
        cin >> inp[i];

    t = buildTree(inp);
    cin >> m;
    forn (i, m)
    {
        string buf;
        while (buf.size() == 0)
            getline(cin, buf);

        int cnt = 0;
        int l = 0;
        int param[3];
        for (int r = 0; r < buf.size(); ++r)
        {
            if (buf[r] == ' ')
            {
                param[cnt++] = atoi(buf.substr(l, r - l + 1).c_str());
                l = r + 1;
            }
        }
        param[cnt++] = atoi(buf.substr(l, buf.size() - l).c_str());

        if (cnt == 2)
            cout << getMin(t, param[0], param[1]) << '\n';
        else
        {
            change(t, param[0], param[1], param[2]);
        }
    }

    return 0;
}
