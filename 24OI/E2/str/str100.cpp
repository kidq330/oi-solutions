#include <bits/stdc++.h>
using namespace std;

vector<list<int>> adj;
vector<bool> del;
vector<int> parent, deg;

void dfs(const int &v) {
  for (auto x : adj[v]) {
    if (x != parent[v]) {
      parent[x] = v;
      deg[x] = adj[x].size()-1;
      dfs(x);
    }
  }
}

void root_tree(const int &root) {
  parent[root] = root;
  deg[root] = adj[root].size();
  dfs(root);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int V;
  cin >> V;

  adj.resize(V);
  del.resize(V);
  deg.resize(V);
  parent.resize(V);

  for (int i = 1; i < V; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  const int root = 0;
  root_tree(0);

  int q, components = 1;
  cin >> q;

  while (q--) {
    int a;
    cin >> a;

    int sign = 1;
    if (a < 0) {
      sign = -1;
      a = -a;
    }
    --a;
    del[a] = !del[a];
    
    if (a == root) {
      components += sign*(deg[a] - 1);
    }
    else {
      deg[parent[a]] -= sign;
      components += sign*(deg[a] - del[parent[a]]);
    }

    cout << components << endl;
  }
}

// 7
// 1 7
// 7 3
// 1 6
// 1 5
// 6 2
// 2 4
// 13
// 4
// -4
// 1
// 5
// -1
// 4
// -4
// 6
// 4
// -6
// 2
// -5
// 5