#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

struct Node
{
    int value;
    int length;
    Node *next;
};

struct List
{
    Node *head;
    Node *tail;
};

struct tree
{
    int value;
    List childs;
};

void addList(List *l, int value, int length)
{
    Node *n = new Node;
    n->next = NULL;
    n->value = value;
    n->length = length;
    if (l->head)
    {
        l->tail->next = n;
        l->tail = n;
    }
    else
    {
        l->tail = n;
        l->head = n;
    }
}

int calc(int *pre, int *order, int preSize, int *first, int *distant, int *levels, int a, int b)
{
    int l = min(first[a], first[b]);
    int r = max(first[a], first[b]);
    int m = order[l];
    int c_l = l / preSize;
    int c_r = r / preSize;

    if (c_l == c_r)
    {
        for (int i = l + 1; i <= r; ++i)
            if (levels[order[i]] < levels[m])
                m = order[i];
    }
    else
    {
        for (int i = l + 1, lr = (c_l + 1) * preSize; i < lr; ++i)
            if (levels[order[i]] < levels[m])
                m = order[i];

        for (int i = c_l + 1; i < c_r; ++i)
            if (levels[pre[i]] < levels[m])
                m = pre[i];

        for (int i = c_r * preSize; i <= r; ++i)
            if (levels[order[i]] < levels[m])
                m = order[i];
    }

    return distant[a] + distant[b] - 2 * distant[m];
}

void getOrder(int *order, int &ordercount, int *first, tree *nodes,
                int *distant, int *levels, int previous, int m)
{
    first[m] = ordercount;
    order[ordercount++] = m;
    if (previous != -1)
        levels[m] = levels[previous] + 1;

    Node *child = nodes[m].childs.head;
    while (child)
    {
        if (child->value != previous)
        {
            distant[child->value] = distant[m] + child->length;
            getOrder(order, ordercount, first, nodes, distant, levels, m, child->value);
            order[ordercount++] = m;
        }
        child = child->next;
    }
}

int main()
{
    tree nodes[50000];

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        nodes[i].childs.head = NULL;

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        addList(&nodes[u].childs, v, w);
        addList(&nodes[v].childs, u, w);
    }

    int distant[50000];
    int levels[50000];
    int order[200000];
    int first[50000];
    int ordercount = 0;

    levels[0] = 0;
    getOrder(order, ordercount, first, nodes, distant, levels, -1, 0);

    int preSize = ceil(sqrt(ordercount));
    int pre[preSize];
    for (int i = 0; i < preSize; ++i)
        pre[i] = -1;

    for (int i = 0; i < ordercount; ++i)
        if (pre[i / preSize] == -1 || levels[order[i]] < levels[pre[i / preSize]])
            pre[i / preSize] = order[i];

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        cout << calc(pre, order, preSize, first, distant, levels, a, b) << endl;
    }

    return 0;
}
