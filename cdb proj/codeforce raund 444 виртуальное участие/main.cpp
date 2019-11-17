#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)

const int INF = 2000000000;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int t[300000];
int q[300000];
ll sum[300000];

int main()
{
    int n, a, b, c, d, start, len;
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> a >> b >> c >> d >> start >> len;
    sum[0] = start;
    forn(i, n)
    {
        cin >> t[i] >> q[i];
        sum[i + 1] = q[i] ? sum[i] + a: sum[i] - b;
    }
    int T = 1;
    int curl = 0;
    int curr = 0;
    int r = T + len;
    ll curv = start;
    set<ll> st;
    st.insert(start);
    while (curr < n && t[curr] < r)
    {
        if (q[curr])
            curv += c;
        else
            curv -= d;
        st.insert(curv);
        ++curr;
    }
    while (true)
    {
        r = T + len;
        cout << curl << ' ' << curr << ' ' << *st.begin() << endl;
        /*
        if (*st.begin() >= 0)
        {
            cout << T;
            return 0;
        }
        */
        int dl = curl >= n ? INF: t[curl] - T + 1;
        int dr = curr >= n ? INF: r - t[curr] + 1;
        if (dl == INF)
            break;
        if (dl <= dr)
        {
            if (q[curl])
                curv += a - c;
            else
                curv += d - b;
            cout << sum[curl] + (q[curl] ? a - c: d - b) << endl;
            st.erase(sum[curl] + (q[curl] ? a - c: d - b));
            ++curl;
        }
        if (dr <= dl)
        {
            if (q[curr])
                curv += c;
            else
                curv -= d;
            st.insert(curv);
            ++curr;
        }
        T += min(dl, dr);
    }
    cout << -1;
    return 0;
}
