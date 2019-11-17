#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define F first
#define S second

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int M = 6e4 + 10;
const int AL = 95, LS = 32;

string s;
int n;

struct Node
{
    Node *go[AL];
    Node *suflink;
    Node *link;
    int word;

    Node()
    {

    }

    void init(Node* root)
    {
        for (int i = 0; i < AL; ++i)
            go[i] = root;
        suflink = root;
        link = root;
        word = -1;
    }
};

Node g[M];
int cst = 1;

void addWord(string word, int num)
{
    Node* st = g;
    for (char c: word)
    {
        if (st->go[c - LS] == g)
            st->go[c - LS] = g + cst++;
        st = st->go[c - LS];
    }
    st->word = num;
}

void bfs()
{
    queue<Node*> q;
    for (int i = 0; i < AL; ++i)
        if (g->go[i] != g)
        {
            g->go[i]->suflink = g;
            q.push(g->go[i]);
        }
    while (!q.empty())
    {
        Node *cur = q.front();
        q.pop();
        for (int i = 0; i < AL; ++i)
            if (cur->go[i] != g)
                q.push(cur->go[i]);

        for (int i = 0; i < AL; ++i)
        {
            if (cur->go[i] != g)
                cur->go[i]->suflink = cur->suflink->go[i];
            else
                cur->go[i] = cur->suflink->go[i];
        }
        if (cur->suflink->word != -1)
            cur->link = cur->suflink;
        else
            cur->link = cur->suflink->link;
    }
}

bool getRes(string s)
{
    Node *st = g;
    for (char c: s)
    {
        st = st->go[c - LS];
        Node *lst = st;
        while (lst != g)
        {
            if (lst->word != -1)
                return true;
            lst = lst->link;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    string s;
    for (int i = 0; i < M; ++i)
        g[i].init(g);
    getline(cin, s);
    n = atoi(s.c_str());
    for (int i = 0; i < n; ++i)
    {
        getline(cin, s);
        addWord(s, i);
    }
    bfs();
    while (getline(cin, s))
    {
        if (getRes(s))
        {
            cout << s << '\n';
        }
    }

    return 0;
}
