#include <bits/stdc++.h>

using namespace std;

vector<int> g[200001];

bool mod[800100];
int t[800100];
int pos[200001];
int sz[200001];
int cnt;

void topSort(int v = 1)
{
    pos[v] = cnt++;
    sz[v] = 1;
    for (int i = 0; i < g[v].size(); ++i)
    {
        topSort(g[v][i]);
        sz[v] += sz[g[v][i]];
    }
}

bool a[200001];
void make(int v, int tl, int tr)
{
    if (tl == tr)
        t[v] = a[tl] ? 1 : 0;
    else
    {
        int mid = (tl + tr) >> 1;
        make(v * 2, tl, mid);
        make(v * 2 + 1, mid + 1, tr);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

void push(int v, int tl, int mid, int tr)
{
    if (mod[v])
    {
        t[v * 2] = mid - tl + 1 - t[v * 2];
        t[v * 2 + 1] = tr - mid - t[v * 2 + 1];
        mod[v * 2] ^= mod[v];
        mod[v * 2 + 1] ^= mod[v];
        mod[v] = false;
    }
}

void modify(int v, int tl, int tr, int l, int r)
{
    if (tl == l && tr == r)
    {
        mod[v] ^= true;
        t[v] = tr - tl + 1 - t[v];
    }
    else
    {
        int mid = (tl + tr) >> 1;
        push(v, tl, mid, tr);
        if (r <= mid)
            modify(v * 2, tl, mid, l, r);
        else if (l > mid)
            modify(v * 2 + 1, mid + 1, tr, l, r);
        else
        {
            modify(v * 2, tl, mid, l, mid);
            modify(v * 2 + 1, mid + 1, tr, mid + 1, r);
        }
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

int get(int v, int tl, int tr, int l, int r)
{
    if (tl == l && tr == r)
        return t[v];
    else
    {
        int mid = (tl + tr) >> 1;
        push(v, tl, mid, tr);
        int res;
        if (r <= mid)
            res = get(v * 2, tl, mid, l, r);
        else if (l > mid)
            res = get(v * 2 + 1, mid + 1, tr, l, r);
        else
            res = get(v * 2, tl, mid, l, mid) + get(v * 2 + 1, mid + 1, tr, mid + 1, r);
        t[v] = t[v * 2] + t[v * 2 + 1];
        return res;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    for (int i = 2; i <= n; ++i)
    {
        int t;
        cin >> t;
        g[t].push_back(i);
    }
    topSort();
    for (int i = 1; i <= n; ++i)
    {
        int val;
        cin >> val;
        a[pos[i]] = val == 1;
    }
    make(1, 0, n - 1);
    cout.flush();
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        char command[5];
        int v;
        cin >> command >> v;
        if (command[0] == 'g')
            cout << get(1, 0, n - 1, pos[v], pos[v] + sz[v] - 1) << endl;
        else
            modify(1, 0, n - 1, pos[v], pos[v] + sz[v] - 1);
    }
    return 0;
}
