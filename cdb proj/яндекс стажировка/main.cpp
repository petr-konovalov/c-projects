#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define L first
#define R second
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase

typedef unsigned long long ull;
typedef long long ll;
typedef double db;
typedef float fl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1000010;

int n;

struct Node
{
    int next[33];
    int cnt;
    int childCnt;
    Node()
    {
        forn (i, 33)
            next[i] = -1;
        cnt = 0;
    }
};

Node tb[N];
int cst = 1;

bool add(char *s, int dpt = 0, int st = 0)
{
    if (s[dpt] == '\0')
        return false;
    ++tb[st].cnt;
    int next = tb[st].next[s[dpt] - 'a'];
    if (next != -1)
        return add(s, dpt + 1, next);
    else
    {
        ++tb[st].childCnt;
        tb[st].next[s[dpt] - 'a'] = cst;
        ++cst;
        add(s, dpt + 1, cst - 1);
    }

    return true;
}

int check(char *s)
{
    int st = 0;
    for (int i = 0; s[i] != '\0'; ++i)
        st = tb[st].next[s[i] - 'a']
    if (tb[st].childCnt > 0)
        return strlen(s);
    st = 0;
    for (int i = 0; s[i] != '\0'; ++i)
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    int ans = 0;
    forn (i, n)
    {
        char str[1005];
        cin >> str;
        if (!add(str))
        {
            ans += check(str);
        }
        else
            ans += strlen(str);
        //debug("%i\n", ans);
    }
    /*
    forn (i, cst)
        debug("%i\n", tb[i].cnt);
        */
    cout << ans;

    return 0;
}
