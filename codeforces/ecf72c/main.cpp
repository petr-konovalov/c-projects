#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define sz(x) x.size()
#define all(x) x.begin(), x.end()
#define sqr(x) ((x)*(x))

typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;
typedef pair<ld, ld> pnt;

ll mLen = 2e5 + 1;

void solve(string s)
{
  int rOddPos[mLen];
  int res = 0;
  rOddPos[0] = 0;
  for (int k = 1; k <= s.size(); ++k)
  {
    rOddPos[k] = s[k - 1] == '1' ? k: rOddPos[k - 1];
    int cur = s[k - 1] - '0';
    int l = k;
    int prevLen = 1;
    while (cur <= mLen && l > 0 && prevLen < 20)
    {
      l = rOddPos[l - 1];
      if (prevLen <= cur && cur <= k - l)
        ++res;
      cur += 1 << (k - l);
      prevLen = k - l + 1;
    }
  }

  cout << res << '\n';
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);
  cout.tie(NULL);

  int t;
  cin >> t;
  forn (testNumber, t)
  {
    string s;
    cin >> s;
    solve(s);
  }
}
