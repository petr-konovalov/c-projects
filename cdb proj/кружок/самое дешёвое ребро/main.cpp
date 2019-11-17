#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define pb push_back

const int N = 50010;
const int INF = 1000000000;

typedef struct segTree
{
    segTree *left;
    segTree *right;
    int value;
} segTree;

int tin[N], tout[N];
int timer;
int p[N];
int c[N];
bool heav[N];
int size[N];
vector<int> g[N];
vector<int> lNode;
int n;

int num[N];
int pos[N];
vector<int> comp[N];
vector<segTree*> tree;

segTree* makeTree(int n, int l, int r)
{
    segTree *v = new segTree;
    if (l == r)
        v->value = c[comp[n][l]];
    else
    {
        int mid = (l + r) >> 1;
        v->left = makeTree(n, l, mid);
        v->right = makeTree(n, mid + 1, r);
        v->value = min(v->left->value, v->right->value);
    }
    return v;
}

int getMin(const segTree *t, int l, int r, int tl, int tr)
{
    if (r < l)
        return INF;
    if (tl == l && tr == r)
        return t->value;
    else
    {
        int mid = (tl + tr) >> 1;
        if (r <= mid)
            return getMin(t->left, l, r, tl, mid);
        else if (l > mid)
            return getMin(t->right, l, r, mid + 1, tr);
        else
            return min(getMin(t->left, l, mid, tl, mid), getMin(t->right, mid + 1, r, mid + 1, tr));
    }
}

void destroyTree(segTree *&v, int l, int r)
{
    if (l != r)
    {
        int mid = (l + r) >> 1;
        destroyTree(v->left, l, mid);
        destroyTree(v->right, mid + 1, r);
    }
    delete v;
}

void dfs(int v = 1)
{
    tin[v] = timer++;
    size[v] = 1;
    for (int to: g[v])
    {
        dfs(to);
        size[v] += size[to];
    }
    for (int to: g[v])
        if (2 * size[to] >= size[v])
        {
            heav[to] = true;
            tout[v] = timer++;
            return;
        }
    lNode.pb(v);
    tout[v] = timer++;
}

void getComp()
{
    tree.reserve(lNode.size());
    for (int i = 0; i < lNode.size(); ++i)
    {
        int cur = lNode[i];
        while (heav[cur])
        {
            pos[cur] = comp[i].size();
            comp[i].pb(cur);
            num[cur] = i;
            cur = p[cur];
        }
        pos[cur] = comp[i].size();
        comp[i].pb(cur);
        num[cur] = i;
        tree.pb(makeTree(i, 0, comp[i].size() - 1));
    }
}

bool isAncestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int findNode(int n, int child)
{
    int l = -1, r = comp[n].size() - 1;
    while (r - l > 1)
    {
        int mid = (l + r) >> 1;
        if (isAncestor(comp[n][mid], child))
            r = mid;
        else
            l = mid;
    }
    return comp[n][r];
}

int getAns(int a, int b)
{
    if (num[a] == num[b])
    {
        if (pos[a] > pos[b])
            swap(a, b);
        return getMin(tree[num[a]], pos[a], pos[b] - 1, 0, comp[num[a]].size() - 1);
    }
    else if (isAncestor(a, b) || isAncestor(b, a))
    {
        if (isAncestor(a, b))
            swap(a, b);
        int ans = getMin(tree[num[a]], pos[a], comp[num[a]].size() - 1, 0, comp[num[a]].size() - 1);
        int cur;
        for (cur = p[comp[num[a]].back()]; num[cur] != num[b]; cur = p[comp[num[cur]].back()])
            ans = min(ans, getMin(tree[num[cur]], pos[cur], comp[num[cur]].size() - 1, 0, comp[num[cur]].size() - 1));
        ans = min(ans, getMin(tree[num[b]], pos[cur], pos[b] - 1, 0, comp[num[b]].size() - 1));
        return ans;
    }
    else
    {
        int cur = a;
        while (!isAncestor(comp[num[cur]].back(), b))
            cur = p[comp[num[cur]].back()];
        int lca = findNode(num[cur], b);
        if (isAncestor(cur, lca))
            lca = cur;
        return min(getAns(a, lca), getAns(b, lca));
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(false);
    cout.tie(false);

    cin >> n;
    for (int i = 2; i <= n; ++i)
    {
        cin >> p[i] >> c[i];
        g[p[i]].pb(i);
    }
    dfs();
    getComp();
    int m;
    cin >> m;
    forn (i, m)
    {
        int a, b;
        cin >> a >> b;
        cout << getAns(a, b) << '\n';
    }
    for (int i = 0; i < tree.size(); ++i)
        destroyTree(tree[i], 0, comp[i].size() - 1);
    return 0;
}
