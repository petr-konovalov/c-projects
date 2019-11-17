#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Seg
{
    int l, r;
    int id;
    Seg(){};
    Seg(int l, int r, int id): l(l), r(r), id(id){};
};

bool operator< (Seg a, Seg b)
{
    return (a.l < b.l) || (a.l == b.l && a.r > b.r);
}

int main()
{
    vector<Seg> seg;
    vector<Seg> levels[500];
    int p[500];
    int clevels = 1;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int l, r;
        cin >> l >> r;
        seg.push_back(Seg(l, r, i));
    }
    sort(seg.begin(), seg.end());
    for (int i = 0; i < n; ++i)
    {
        int j = clevels;
        int id = -1;
        while (j > 0 && id == -1)
        {
            --j;
            for (int k = (int)levels[j].size() - 1; k >= 0 && id == -1; --k)
            {
                int l = levels[j][k].l, r = levels[j][k].r, cid = levels[j][k].id;
                if (l < seg[i].l && seg[i].r < r)
                    id = cid;
            }
        }
        if (id == -1)
        {
            levels[0].push_back(seg[i]);
            p[seg[i].id] = -1;
        }
        else
        {
            if (j + 1 == clevels)
                ++clevels;
            levels[j + 1].push_back(seg[i]);
            p[seg[i].id] = id;
        }
    }
    int id = levels[clevels - 1][0].id;
    cout << clevels << endl;
    while (id != -1)
    {
        cout << id + 1 << " ";
        id = p[id];
    }
    return 0;
}
