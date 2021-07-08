#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef pair<ii, int> wpt;
const int INF = 0x3f3f3f3f;

#define FOR(i, b, e) for(int i = (b); i < (e); i++)
#define TRAV(x, a) for(auto &x: (a))
#define SZ(x) ((int)(x).size())
#define PB push_back
#define PR pair
#define X first
#define Y second


// AB x AC
int cprod(ii &A, ii &B, ii &C) {
  return (B.X - A.X)*(C.Y - A.Y) - (C.X - A.X)*(B.Y - A.Y);
}
// does BC turn clockwise to AB
bool cw(ii &A, ii &B, ii &C) {
  return cprod(A, B, C) < 0;
}
bool ccw(ii &A, ii &B, ii &C) {
  return cprod(A, B, C) > 0;
}

void polar_sort(ii &C, bool no_invert, vector<wpt> &pts) {
  auto cmp = [&C, &no_invert](wpt &A, wpt& B)->bool{
    if (A.X == C) return false;
    if (B.X == C) return true;
    if ((A.X.Y - C.Y > 0) != (B.X.Y - C.Y > 0)) {
      return no_invert ? A.X.Y > B.X.Y : A.X.Y < B.X.Y;
    }
    return cw(C, A.X, B.X);
  };
  sort(pts.begin(), pts.end(), cmp);
}

int sgn(int x) {
  return (x > 0) - (x < 0);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n; cin >> n;
  vector<ii> polygon(n);
  for (auto &A : polygon) {
    cin >> A.X >> A.Y;
  }
  int m; cin >> m;
  vector<wpt> pts(m);
  int S = 0;
  for (auto &[A, w] : pts) {
    cin >> A.X >> A.Y >> w;
    S += w;
  }

  // dp[Ai][Aj] = sum to the left of line AiAj
  vector<vector<int>> dp(n, vector<int>(n));
  
  for (int i = 0; i < n; ++i) {
    // invert: check corner case w/ parallel to OX
    int prev = i ? i-1 : n-1;
    polar_sort(polygon[i], polygon[prev].Y <= polygon[i].Y, pts);
    // sentinel
    pts.push_back({polygon[prev], 0});
    int j = (i+2)%n;
    while (!ccw(polygon[i], polygon[j], pts[0].X)) j = (j+1)%n;
    int s = 0;
    for (int p = 0; p < m; ++p) {
      s += pts[p].Y;
      while (j != prev && 
             sgn(cprod(polygon[i], polygon[j], pts[p].X)) !=
             sgn(cprod(polygon[i], polygon[j], pts[p+1].X))) {
        dp[i][j] = s;
        j = (j+1)%n;
      }
    }
    dp[i][prev] = s;
    pts.pop_back();
  }
  int ans = -INF;
  for (int i = 0; i < n; ++i) {
    for (int j = i+1; j < n; ++j) {
      for (int k = j+1; k < n; ++k) {
        ans = max(ans, S-dp[i][j]-dp[j][k]-dp[k][i]);
      }
    }
  }
  cout << ans;
}

// 5
// 1 4
// 3 9
// 8 4
// 8 0
// 5 0
// 7
// 6 5 -8
// 8 0 -9
// 5 0 -6
// 2 6 5
// 1 4 -9
// 8 4 5
// 3 9 5

// 4
// -2 -2
// -2 2
// 2 2
// 2 -2
// 1
// 0 0 7