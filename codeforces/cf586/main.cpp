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

const int N = 2e5 + 1;

int n, m;
int w[N];


int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;
  forn (k, n)
    cin >> w[k];
  return 0;
}
