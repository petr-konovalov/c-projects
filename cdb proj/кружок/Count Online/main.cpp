#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define X first
#define Y second
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);

typedef long long ll;
typedef float fl;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 5e4 + 5, B = 1300;

bool xcomp(pii f, pii s)
{
    return f.X < s.X;
}

bool ycomp(pii f, pii s)
{
    return f.Y < s.Y;
}

struct Block
{
    vector<pii> pnt;
    int rig;
    Block(vector<pii> pnt, int rig): pnt(pnt), rig(rig){}
};

list<Block> t;

pii arr[N + 100000];
int n, m;

void split(list<Block>::iterator &it, list<Block> &l)
{
    sort(it->pnt.begin(), it->pnt.end(), xcomp);
    vector<pii> nBlock(it->pnt.begin() + B, it->pnt.end());
    it->pnt.resize(B);
    it->rig = it->pnt.back().X;
    sort(it->pnt.begin(), it->pnt.end(), ycomp);
    ++it;
    int rig = nBlock.back().X;
    sort(nBlock.begin(), nBlock.end(), ycomp);
    l.insert(it, Block(nBlock, rig));
}

list<Block>::iterator getFBlock(int x)
{
    list<Block>::iterator pos = t.begin();
    while (pos != t.end() && pos->rig < x)
        ++pos;
    if (pos == t.end())
        --pos;
    return pos;
}

list<Block>::iterator getLBlock(int x)
{
    list<Block>::iterator pos = getFBlock(x);
    while (pos != t.end() && pos->rig == x)
        ++pos;
    if (pos == t.end())
        --pos;
    return pos;
}

void add(pii pnt)
{
    list<Block>::iterator pos = getFBlock(pnt.X);
    pos->pnt.pb(pnt);
    if (pnt.X > pos->rig)
        pos->rig = pnt.X;
    for (int i = pos->pnt.size() - 1; i > 0 && pos->pnt[i].Y < pos->pnt[i - 1].Y; --i)
        swap(pos->pnt[i], pos->pnt[i - 1]);
    if (pos->pnt.size() >= 2 * B)
        split(pos, t);
}

int cnt(int x1, int y1, int x2, int y2)
{
    auto b1 = getFBlock(x1), b2 = getLBlock(x2);
    int res = 0;
    if (b1 == b2)
    {
        for (pii item: b1->pnt)
            if (x1 <= item.X && item.X <= x2 && y1 <= item.Y && item.Y <= y2)
                ++res;
    }
    else
    {
        for (pii item: b1->pnt)
            if (x1 <= item.X && item.X <= x2 && y1 <= item.Y && item.Y <= y2)
                ++res;
        for (pii item: b2->pnt)
            if (x1 <= item.X && item.X <= x2 && y1 <= item.Y && item.Y <= y2)
                ++res;
        ++b1;
        while (b1 != b2)
        {
            res += upper_bound(b1->pnt.begin(), b1->pnt.end(), mp(0, y2), ycomp) -
                lower_bound(b1->pnt.begin(), b1->pnt.end(), mp(0, y1), ycomp);
            ++b1;
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i].X >> arr[i].Y;

    sort(arr, arr + n, xcomp);

    for (int i = 0, e = (n - 1) / B; i <= e; ++i)
    {
        vector<pii> block;
        for (int j = i * B, ej = min(n, (i + 1) * B); j < ej; ++j)
            block.pb(arr[j]);
        t.pb(Block(block, block.back().X));
    }

    for (auto &block: t)
        sort(block.pnt.begin(), block.pnt.end(), ycomp);

    cin >> m;

    int res = 0;
    forn (i, m)
    {
        char c;
        cin >> c;
        if (c == '?')
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << (res = cnt(x1, y1, x2, y2)) << '\n';
        }
        else
        {
            int x, y;
            cin >> x >> y;
            add(arr[n++] = mp(x + res % 100, y + res % 101));
        }
    }

    return 0;
}
