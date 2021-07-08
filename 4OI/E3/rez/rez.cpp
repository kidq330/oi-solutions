#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
const int maxr = 3e4+1;
vector<int> T(4*maxr);

int query(int v, int tl, int tr, int l, int r) {
  if (tr < l || r < tl) {
    return 0;
  }
  if (l <= tl && tr <= r) {
    return T[v];
  }
  int tm = (tl+tr)/2;
  return max(query(2*v, tl, tm, l, r), query(2*v+1, tm+1, tr, l, r));
}

void upd(int v, int tl, int tr, int a, int val) {
  if (tl == tr) {
    T[v] = max(T[v], val);
    return;
  }
  int tm = (tl+tr)/2;
  if (a <= tm)
    upd(2*v, tl, tm, a, val);
  else
    upd(2*v+1, tm+1, tr, a, val);
  T[v] = max(T[2*v], T[2*v+1]);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n; cin >> n;
  const int maxr = 3e4+1;
  vector<ii> v(n);
  for (auto &p : v)
    cin >> p.first >> p.second;
  sort(v.begin(), v.end());
  vector<int> dp(n);
  int res = v[0].second - v[0].first;
  upd(1, 0, maxr, v[0].second, dp[0] = res);
  for (int i = 1; i < n; ++i) {
    upd(1, 0, maxr, v[i].second, 
        dp[i] = v[i].second - v[i].first + query(1, 0, maxr, 0, v[i].first));
    res = max(res, dp[i]);
  }
  cout << res ;
}