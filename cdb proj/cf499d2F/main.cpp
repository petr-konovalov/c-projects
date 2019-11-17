#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define X first
#define Y second

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<db, db> pdd;
typedef pair<ll, ll> pll;

const int N = 1e6 + 10;

struct Node
{
    char type;
    bool value;
    vector<Node*> childs;
};

Node g[N];
bool ans[N];
int n;

bool execOp(Node *v)
{
    switch (v->type)
    {
        case 'i':
            return v->value;
        case '~':
            return !v->childs[0]->value;
        case '&':
            return v->childs[0]->value && v->childs[1]->value;
        case '|':
            return v->childs[0]->value || v->childs[1]->value;
        case '^':
            return v->childs[0]->value ^ v->childs[1]->value;
    }
}

void execTree(Node *v)
{
    for (auto to: v->childs)
        execTree(to);
    v->value = execOp(v);
}

void printTree(Node *v)
{
    debug("[%c %i]", v->type, v->value);
    if (v->type != 'i')
        debug("(");
    for (auto to: v->childs)
        printTree(to);
    if (v->type != 'i')
        debug(")");
}

char getChar(bool b)
{
    return b ? '1': '0';
}

void calcAns(Node *v, char func)
{
    int id = v - g;
    switch (func)
    {
        case '0':
            ans[id] = false;
            break;
        case '1':
            ans[id] = true;
            break;
        case '~':
            ans[id] = !(g + 1)->value;
            break;
    }
    for (auto to: v->childs)
    {
        char newFunc;
        if (func == '0' || func == '1')
            newFunc = func;
        else
        {
            bool oldValue = execOp(v);
            to->value = !to->value;
            bool newValue = execOp(v);
            to->value = !to->value;

            if (oldValue == newValue)
                newFunc = getChar((g + 1)->value);
            else
                newFunc = '~';
        }

        calcAns(to, newFunc);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int u, v;
        string type;
        cin >> type;
        if (type == "IN")
        {
            cin >> u;
            g[i].value = u == 1;
            g[i].type = 'i';
        }
        else if (type == "NOT")
        {
            cin >> u;
            g[i].childs.pb(g + u);
            g[i].type = '~';
        }
        else
        {
            cin >> u >> v;
            g[i].childs.pb(g + u);
            g[i].childs.pb(g + v);
            if (type == "AND")
            {
                g[i].type = '&';
            }
            else if (type == "OR")
            {
                g[i].type = '|';
            }
            else if (type == "XOR")
            {
                g[i].type = '^';
            }
        }
    }

    execTree(g + 1);
    //printTree(g + 1);
    calcAns(g + 1, '=');

    for (int i = 1; i <= n; ++i)
        if (g[i].type == 'i')
            cout << ans[i];
    return 0;
}
