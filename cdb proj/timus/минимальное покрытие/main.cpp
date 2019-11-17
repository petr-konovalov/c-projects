#include <iostream>

using namespace std;

int l[100000];
int r[100000];
int res[1000000];

void qSort(int *l, int *r, int m, int n)
{
    int p = l[(m + n) / 2];
    int i = m;
    int j = n;
    while (i < j)
    {
        while (l[i] < p)
            ++i;
        while (l[j] > p)
            --j;
        if (i <= j)
        {
            swap(l[i], l[j]);
            swap(r[i], r[j]);
            ++i;
            --j;
        }
    }
    if (i < n)
        qSort(l, r, i, n);
    if (m < j)
        qSort(l, r, m, j);
}

void delRep(int *l, int *r, int &len)
{
    int c = 0;
    for (int i = 1; i < len; ++i)
    {
        if (l[i] != l[c])
        {
            l[++c] = l[i];
            r[c] = r[i];
        }
        else
        {
            if (r[i] > r[c])
                r[c] = r[i];
        }
    }
    len = c + 1;
}

int main()
{
    int M = 0;
    cin >> M;
    int s, t, c = 0;
    cin >> s >> t;
    while (s != 0 || t != 0)
    {
        if (s < M && t > 0)
        {
            l[c] = s;
            r[c] = t;
            ++c;
        }
        cin >> s >> t;
    }
    if (c == 0)
    {
         cout << "No solution";
         return 0;
    }
    qSort(l, r, 0, c - 1);
    delRep(l, r, c);
    if (l[0] > 0)
    {
        cout << "No solution";
        return 0;
    }
    else
    {
        int cnt = 0;
        res[0] = 0;
        int next = 1;
        while (l[next] <= 0)
        {
            if (r[next] > r[res[0]])
                res[0] = next;
            ++next;
        }
        for (int i = res[0]; r[i] < M && next < c; i = res[cnt])
        {
            res[++cnt] = next;
            if (l[next] > r[i])
            {
                cout << "No solution";
                return 0;
            }
            while (next < c && l[next] <= r[i])
            {
                if (r[next] > r[res[cnt]])
                    res[cnt] = next;
                ++next;
            }
        }
        if (r[res[cnt]] < M)
            cout << "No solution";
        else
        {
            cout << cnt + 1 << '\n';
            for (int i = 0; i <= cnt; ++i)
                cout << l[res[i]] << ' ' << r[res[i]] << '\n';
        }
    }
    cin.get();
    return 0;
}
