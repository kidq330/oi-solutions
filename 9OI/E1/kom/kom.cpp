#include <bits/stdc++.h>
using namespace std;

vector<list<int>> adj;
vector<vector<int>> ancestor;
vector<int> parent, lg, depth;

void read_tree(const int &n) {
  adj.resize(n);
  for (int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
}

void dfs(const int &v) {
  for (auto x : adj[v]) {
    if (x != parent[v]) {
      parent[x] = v;
      depth[x] = depth[v] + 1;
      dfs(x);
    }
  }
}

void root_tree(const int &root, const int &n) {
  parent.resize(n);
  depth.resize(n);
  parent[root] = root;
  depth[root] = 0;
  dfs(root);
}

void make_ancestor(const int &n) {
  ancestor.resize(lg[n]+1, vector<int>(n));

  for (int i = 0; i < n; ++i) {
    ancestor[0][i] = parent[i];
  }

  for (int k = 1; k < lg[n]; ++k)
    for (int i = 0; i < n; ++i)
      ancestor[k][i] = ancestor[k-1][ancestor[k-1][i]];
}

int walk(const int &v, int k) {
  int u = v;
  while (k > 0) {
    u = ancestor[lg[k]][u];
    k -= 1 << lg[k];
  }
  return u;
}

int lca(int a, int b, const int &n) {
  if (depth[a] > depth[b])
    a = walk(a, depth[a] - depth[b]);
  else
    b = walk(b, depth[b] - depth[a]);
  
  if (a == b)
    return a;

  for (int i = lg[n]; i >= 0; --i) {
    if (ancestor[i][a] != ancestor[i][b]) {
      a = ancestor[i][a];
      b = ancestor[i][b];
    }
  }

  return ancestor[0][a];
}

int main() {
  int n;
  cin >> n;
  read_tree(n);
  root_tree(0, n);

  lg.resize(n+1);
  lg[1] = 0;
  for (int i = 2; i <= n; ++i) {
    lg[i] = lg[i/2] + 1;
  }

  make_ancestor(n);

  int q;
  cin >> q;

  int v;
  cin >> v;
  --v, --q;
  int sum = 0;

  while(q--) {
    int u;
    cin >> u;
    --u;
    int l = lca(u, v, n);
    sum += depth[v] + depth[u] - 2*depth[l];
    v = u;
  }

  cout << sum;
}