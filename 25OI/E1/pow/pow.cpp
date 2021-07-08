#include <bits/stdc++.h>
using namespace std;
const int P = 1e9+7;
const long long INF = 1e10;

vector<int> parent;
vector<pair<long long, int>> dp;
vector<array<int, 3>> edg;

int find(const int &v) {
  return (parent[v] == -1 ? v : parent[v] = find(parent[v]));
}

void union_set(int u, int v, const long long &w) {
  u = find(u), v = find(v);
  if (u == v) {
    dp[v].first += w - dp[v].second;
    dp[v].second = w;
    return;
  }
  parent[u] = v;
  dp[v].first = (dp[v].first + w - dp[v].second)*(dp[u].first + w - dp[u].second) % P;
  dp[v].second = w;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int m, n, h; cin >> m >> n >> h;
  parent.resize(m*n, -1);
  dp.resize(m*n, {INF, 0});
  edg.resize(2*m*n - m - n);

  int t = -1;
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n-1; ++i) {
      long long w; cin >> w;
      const int u = n*j + i, v = u+1;
      edg[++t] = {(int)w, u, v};
      dp[u].first = min(dp[u].first, w+1);
      dp[v].first = min(dp[v].first, w+1);
    }
  }
  for (int j = 0; j < m-1; ++j) {
    for (int i = 0; i < n; ++i) {
      long long w; cin >> w;
      const int u = n*j + i, v = u+n;
      edg[++t] = {(int)w, u, v};
      dp[u].first = min(dp[u].first, w+1);
      dp[v].first = min(dp[v].first, w+1);
    }
  }

  for (auto &x : dp)
    x.second = x.first - 1;

  sort(edg.begin(), edg.end());
  for (auto e : edg) {
    union_set(e[1], e[2], e[0]);
  }
  auto p = dp[find(0)];
  cout << (p.first + h - p.second) % P;
}


// 10 1 4
// 4 3 3 4 3 2 3 2 3