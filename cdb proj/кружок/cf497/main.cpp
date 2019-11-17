#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define ins insert
#define ers erase

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;

const int N = 1e5 + 7, INF = 1e9 + 7;
const ll INF64 = 1e18;

int t;
int ans;
vector<int> dl[N];
int cnt[3];
int pcnt[3][3];
int tcnt;
bitset<N> used[3];

void init()
{
    for (int d = 1; d < N; ++d)
    {
        for (int num = d; num < N; num += d)
            dl[num].pb(d);
    }
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void solve(int A, int B, int C)
{
    ans = 0;
    int sz[] = {dl[A].size(), dl[B].size(), dl[C].size()};

    for (int i: dl[A])
        used[0][i] = true;
    for (int i: dl[B])
        used[1][i] = true;
    for (int i: dl[C])
        used[2][i] = true;

    vector<int> m1(dl[A].size() + dl[B].size());
    vector<int> m(dl[A].size() + dl[B].size() + dl[C].size());
    merge(dl[A].begin(), dl[A].end(), dl[B].begin(), dl[B].end(), m1.begin());
    merge(m1.begin(), m1.end(), dl[C].begin(), dl[C].end(), m.begin());
    m.resize(unique(m.begin(), m.end()) - m.begin());

    int s = m.size();

    forn (i, s)
    {
        int c = 0;
        int F, S, T;
        forn (k, 3)
            c += used[k][m[i]];
        if (c == 3)
        {
            ans += s;
            ++tcnt;
        }
        if (c == 2)
        {
            forn (k, 3)
            {
                if (!used[k][m[i]])
                    F = k;
            }
            S = (F + 1) % 3;
            T = (S + 1) % 3;
            ans += sz[F] - 1;
            ++pcnt[S][T];
            ++pcnt[T][S];
        }
        for (int j = 0; j < i; ++j)
        {

        }
        forn (k, 3)
            cnt[k] += used[k][m[i]];
    }
    cout << ans << '\n';

    forn (k, 3)
        cnt[k] = 0;

    tcnt = 0;

    for (int i: dl[A])
        used[0][i] = false;
    for (int i: dl[B])
        used[1][i] = false;
    for (int i: dl[C])
        used[2][i] = false;
}

bool pused[1000][1000];

int f(int a, int b)
{
    int d = gcd(a, b);
    int D = dl[d].size();
    int a1 = a / d;
    int b1 = b / d;
    int sa1 = dl[a1].size();
    int sb1 = dl[b1].size();
    return sa1 * sb1 + sa1 * D + sb1 * D + D * (D - 1) / 2 - 2;
}

int per(int a, int b)
{
    int res = 0;
    forn (i, 1000)
        forn (j, 1000)
            pused[i][j] = false;
    for (int da: dl[a])
        for (int db: dl[b])
        {
            int a = min(da, db);
            int b = max(da, db);
            if (!pused[a][b])
            {
                ++res;
                pused[a][b] = true;
            }
        }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    init();
    debug("init\n");
    cin >> t;
    srand(time(0));
    while (t--)
    {
        int A = rand() % 1000 + 1, B = rand() % 1000 + 1, C;
        //cin >> A >> B; //>> C;
        //solve(A, B, C);
        debug("%i %i\n", per(A, B), f(A, B));
    }

    return 0;
}
