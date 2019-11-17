#include <bits/stdc++.h>

using namespace std;

const int N = 200000;

typedef long long ll;

map<char, int> edges[2 * N];
int link[2 * N];
int len[2 * N];
int last;
int stateCount;
int cnt[2 * N];
ll res;

void init()
{
    stateCount = 1;
    link[0] = -1;
    cnt[0] = 1;
}

int newState()
{
    len[stateCount] = len[last] + 1;
    cnt[stateCount] = 0;
    return stateCount++;
}

int clone(int q)
{
    for (auto v: edges[q])
        edges[stateCount][v.first] = v.second;
    link[stateCount] = link[q];
    cnt[stateCount] = 0;
    return stateCount++;
}

void addChar(char c)
{
    int cur = newState();
    int p = last;
    while (p >= 0 && edges[p].find(c) == edges[p].end())
    {
        cnt[cur] += cnt[p];
        res += cnt[p];
        edges[p][c] = cur;
        p = link[p];
    }
    if (p >= 0)
    {
        int q = edges[p][c];
        if (len[p] + 1 == len[q])
            link[cur] = q;
        else
        {
            int newS = clone(q);
            len[newS] = len[p] + 1;
            link[cur] = link[q] = newS;
            while (p >= 0 && edges[p][c] == q)
            {
                cnt[q] -= cnt[p];
                cnt[newS] += cnt[p];
                edges[p][c] = newS;
                p = link[p];
            }
        }
    }
    last = cur;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(false);
    cout.tie(false);

    char c;
    init();
    while ((c = getchar()) != '\n')
    {
        addChar(c);
        cout << res << '\n';
    }

    return 0;
}
