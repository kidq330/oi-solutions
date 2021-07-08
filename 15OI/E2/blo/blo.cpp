#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<vector<int>> adj;
vector<ll> f;
vector<int> sub, in, low, p;

void dfs(int v, int &t, int n) {
  in[v] = ++t;
  low[v] = v;
  int s = 0;
  for (auto x : adj[v]) {
    if (in[x] == -1) {
      p[x] = v;
      dfs(x, t, n);
      sub[v] += sub[x];
      if (in[low[x]] < in[low[v]]) {
        low[v] = low[x];
      }
      if (in[low[x]] >= in[v])
        f[v] += (ll)sub[x]*(sub[x]-1);
      else
        s += sub[x];
    }
    else if (p[v] != x) {
      if (in[low[x]] < in[low[v]]) {
        low[v] = low[x];
      }
    }
  }
  s += n-sub[v];
  f[v] += (ll)s*(s-1);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  constexpr int r = 0;
  int n, m; cin >> n >> m;
  adj.resize(n);
  f.resize(n);
  sub.resize(n, 1);
  in.resize(n, -1);
  low.resize(n);
  p.resize(n);

  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int t = -1;
  dfs(r, t, n);

  for (int i = 0; i < n; ++i) {
    cout << (ll)n*(n-1) - f[i] << '\n';
  }
}