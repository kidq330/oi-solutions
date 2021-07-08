#include <bits/stdc++.h>
#define INF 1e9
using namespace std;

vector<vector<int>> T, adj;
vector<int> parent, set_rank, t;
const int FREE_HAND = -2,
          UNINITIALIZED = -2,
          NEVER_FALLS = -1;

int set_find(const int &v) {
  int &p = parent[v];
  if (p != v) {
    int r = set_find(p);
    if (t[v] == UNINITIALIZED) {
      t[v] = t[p];
    }
    p = r;
  }
  return parent[v];
}

void set_union(const int &u, const int &v) {
  int root_u = set_find(u),
      root_v = set_find(v);
  
  if (root_u == root_v)
    return;
  
  if (set_rank[u] < set_rank[v]) {
    parent[root_u] = root_v;
  }
  else {
    parent[root_v] = root_u;
    if (set_rank[root_u] == set_rank[root_v])
      ++set_rank[root_u];
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;

  const int root = 0;
  T.resize(n, vector<int>(2, -1));
  parent.resize(n);

  for (int i = 0; i < n; ++i) {
    parent[i] = i;
    int &a = T[i][0], &b = T[i][1];
    cin >> a >> b;
    --a, --b;
  }


  vector<pair<int, int>> queries(m);

  for (int i = 0; i < m; ++i) {
    int v, hand;
    cin >> v >> hand;
    --v, --hand;
    queries[i] = {v, T[v][hand]};
    T[v][hand] = FREE_HAND;
  }

  t.resize(n, UNINITIALIZED);
  set_rank.resize(n);
  for (int i = 0; i < n; ++i) {
    for (auto x : T[i]) {
      if (x != FREE_HAND)
        set_union(i, x);
    }
  }
  
  T.clear();

  t[set_find(root)] = NEVER_FALLS;
  
  while (m--) {
    int u_root = set_find(queries[m].first), 
        v_root = set_find(queries[m].second),
        t_root = set_find(root);
    set_union(u_root, v_root);
    if ((u_root == t_root) == (v_root == t_root))
      continue;
    if (v_root == t_root)
      swap(u_root, v_root);
    
    t[v_root] = m;
  }

  for (int i = 0; i < n; ++i) {
    set_find(i);
    cout << t[i] << endl;
  }
}