#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second
typedef pair<int, int> ii;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, k; cin >> n >> k;
  vector<ii> seg(n);
  vector<int> st(n);
  for (int i = 0; i < n; ++i) {
    cin >> seg[i].X >> seg[i].Y;
    st[i] = i;
  }
  sort(st.begin(), st.end(), [&seg](int const&i, int const&j){return seg[i] < seg[j];});

  auto cmp = [&seg](int i, int j){return !(seg[i].Y < seg[j].Y || (seg[i].Y == seg[j].Y && seg[i].X < seg[j].X));};
  priority_queue<int, vector<int>, decltype(cmp)> Q(cmp);
  for (int i = 0; i < k-1; ++i) {
    Q.push(st[i]);
  }

  int res = 0; ii ans;
  for (int i = k-1; i < n; ++i) {
    Q.push(st[i]);
    int d = seg[Q.top()].Y - seg[st[i]].X;
    if (res < d) {
      res = d;
      ans = {seg[st[i]].X, seg[Q.top()].Y};
    }
    Q.pop();
  }
  cout << res << '\n';
  for (int i = 0; k; ++i) {
    if (seg[i].X <= ans.X && ans.Y <= seg[i].Y) {
      cout << i+1 << ' ';
      --k;
    }
  }
}