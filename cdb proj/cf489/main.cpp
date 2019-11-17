#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
//#define pb push_back
#define X first
#define Y second

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 2e5 + 9, M = 2e5 + 3, SH = 5e4 + 21, B = 600, INF = 1e9 + 7;
//const int N = 203, M = 2e5 + 3, SH = 1e4 + 7, B = 6;
const ll INF64 = (ll)1e18 + 3;
const ll seed = 98374853;

struct segTree
{
    int maxV;
    ll sum;
    segTree *l, *r;

    segTree(int v)
    {
        maxV = v;
        sum = v;
        l = NULL;
        r = NULL;
    }

    segTree(segTree *l, segTree *r): l(l), r(r)
    {
        maxV = max(l->maxV, r->maxV);
        sum = l->sum + r->sum;
    }
};

int inp[N];
int n, q;
segTree *tree;

void update(segTree *t)
{
    t->maxV = max(t->l->maxV, t->r->maxV);
    t->sum = t->l->sum + t->r->sum;
}

segTree* buildTree(int l, int r)
{
    if (l == r)
        return new segTree(inp[l]);
    else
    {
        int mid = (l + r) >> 1;
        return new segTree(buildTree(l, mid), buildTree(mid + 1, r));
    }
}

void changeItem(segTree *t, int pos, int v, int l, int r)
{
    if (l == r)
    {
        t->maxV = v;
        t->sum = v;
    }
    else
    {
        int mid = (l + r) >> 1;
        if (pos <= mid)
            changeItem(t->l, pos, v, l, mid);
        else
            changeItem(t->r, pos, v, mid + 1, r);
        update(t);
    }
}

ll getSum(segTree *t, int tl, int tr, int l, int r)
{
    if (l == tl && r == tr)
        return t->sum;
    else
    {
        int mid = (l + r) >> 1;
        if (tr <= mid)
            return getSum(t->l, tl, tr, l, mid);
        else if (tl > mid)
            return getSum(t->r, tl, tr, mid + 1, r);
        else
            return getSum(t->l, tl, mid, l, mid) + getSum(t->r, mid + 1, tr, mid + 1, r);
    }
}

int getMax(segTree *t, int tl, int tr, int l, int r)
{
    if (l == tl && r == tr)
        return t->maxV;
    else
    {
        int mid = (l + r) >> 1;
        if (tr <= mid)
            return getMax(t->l, tl, tr, l, mid);
        else if (tl > mid)
            return getMax(t->r, tl, tr, mid + 1, r);
        else
            return max(getMax(t->l, tl, mid, l, mid), getMax(t->r, mid + 1, tr, mid + 1, r));
    }
}

int findPos(segTree *t, int v, int pos, int l, int r)
{
    if (t->maxV < v)
        return r;
    if (l == r)
        return l;
    else
    {
        int mid = (l + r) >> 1;
        if (mid > pos)
        {
            int pl = findPos(t->l, v, pos, l, mid);
            if (inp[pl] < v)
                return findPos(t->r, v, pos, mid + 1, r);
            return pl;
        }
        else
            return findPos(t->r, v, pos, mid + 1, r);
    }
}

int getAns()
{
    int pos = 0;
    ll sum = inp[0];
    if (sum == 0)
        return 0;
    else
    {
        while (inp[pos = findPos(tree, sum, pos, 0, n - 1)] >= sum)
        {
            if (2 * inp[pos] == (sum = getSum(tree, 0, pos, 0, n - 1)))
                return pos;
        }
    }
    return -2;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> q;
    forn (i, n)
        cin >> inp[i];
    tree = buildTree(0, n - 1);
    forn (i, q)
    {
        int p, x;
        cin >> p >> x;
        changeItem(tree, p - 1, x, 0, n - 1);
        inp[p - 1] = x;
        cout << getAns() + 1 << '\n';
    }

    return 0;
}
