// Drogi zmiennokierunkowe, Cosaraju
// Problem Desc.: Given a directed graph G, find all strongly connected vertices,
// meaning it's possible to get from v to any other vertex either in G or G^T, where G^T is the transpose of G.

// Complexity: O(|V| + |E|)

// Solution: If a vertex is strongly connected, then so are all vertices from its SCC.
// We can perform an SCC reduction of G to a DAG which we can then sort topologically.
// Now we need to find all v such that for all u < v there is a path(u, v) and for all u > v there is a path(v, u)
// Let r = [min(adj[v], lambda u_i : i) for v in DAG]

// v is not backwards connected (there exists a vertex u < v which has no path to v)
// iff there exists a vertex u < v s.t. u < v < r[u]
// We perform this check linearly by iterating over the sorted DAG and keeping track of the max current r
// If i < r_max, i is not backwards connected.

// We transpose the DAG to check forward connectivity of the vertices.
// Now, if a DAG vertex is both forwards and backwards connected, then it is strongly connected,
// and so are the vertices that make up the SCC it represents.
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj, adjT, dagj, dagjT;
vector<int> component, topo_dag;

void read_graph(const int &V, int E) {
  adj.resize(V);
  adjT.resize(V);
  while (E--) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    adj[a].push_back(b);
    adjT[b].push_back(a);
  }
}

void topo_dfs(const int &v, int &t, vector<int> &tpsort, vector<bool> &vis, vector<vector<int>> &adj) {
  vis[v] = true;
  for (auto x : adj[v]) {
    if (!vis[x])
      topo_dfs(x, t, tpsort, vis, adj);
  }
  tpsort[t++] = v;
}

void toposort(vector<vector<int>> &adj, vector<int> &tpsort) {
  int V = adj.size(), t = 0;
  vector<bool> vis(adj.size());
  for (int i = 0; i < V; ++i) {
    if (!vis[i])
      topo_dfs(i, t, tpsort, vis, adj);
  }
  reverse(tpsort.begin(), tpsort.end());
}

void scc_dfs(const int &v, const int &c, vector<bool> &vis, vector<vector<int>> &adj) {
  vis[v] = true;
  component[v] = c;
  for (auto x : adj[v]) {
    if (!vis[x])
      scc_dfs(x, c, vis, adj);
  }
}

int SCC_reduce(const int &V) {
  vector<int> tpsort(V);
  toposort(adj, tpsort);
  vector<bool> vis(V);
  int c = 0;
  for (auto v : tpsort) {
    if (!vis[v]) {
      scc_dfs(v, c++, vis, adjT);
    }
  }
  return c;
}

void convert_adj(vector<vector<int>> &adj, vector<vector<int>> &dagj) {
  for (int i = 0; i < adj.size(); ++i) {
    int &c = component[i];
    for (auto x : adj[i]) {
      if (component[x] != c)
        dagj[c].push_back(component[x]);
    }
  }
}

int main() {
  int V, E;
  cin >> V >> E;

  read_graph(V, E);

  component.resize(V);
  int dagsize = SCC_reduce(V);

  
  dagj.resize(dagsize);
  convert_adj(adj, dagj);
  adj.clear();

  dagjT.resize(dagsize);
  convert_adj(adjT, dagjT);
  adjT.clear();

  topo_dag.resize(dagsize);
  toposort(dagj, topo_dag);
  // topo_dag[i] = v && inv_tp[v] = i 
  vector<int> inv_tp(dagsize);
  for (int i = 0; i < dagsize; ++i)
    inv_tp[topo_dag[i]] = i;

  vector<int> r(dagsize);
  for (int i = 0; i < dagsize; ++i) {
    int &v = topo_dag[i],
         r_min = dagsize;
    for (auto x : dagj[v]) {
      r_min = min(r_min, inv_tp[x]);
    }
    r[i] = r_min;
  }

  vector<bool> connected(dagsize, 1);
  int r_max = 0;
  for (int i = 1; i < dagsize; ++i) {
    r_max = max(r_max, r[i-1]);
    if (i < r_max)
      connected[topo_dag[i]] = false;
  }

  for (int i = dagsize-1; i >= 0; --i) {
    int &v = topo_dag[i],
         r_max = -1;
    for (auto x : dagjT[v])
      r_max = max(r_max, inv_tp[x]);
    r[i] = r_max;
  }

  int r_min = dagsize+1;
  for (int i = dagsize-2; i >= 0; --i) {
    r_min = min(r_min, r[i+1]);
    if (i > r_min)
      connected[topo_dag[i]] = false;
  }

  r.clear();
  dagj.clear();
  dagjT.clear();

  vector<int> ans;
  for (int v = 0; v < V; ++v) {
    if (connected[component[v]])
      ans.push_back(v+1);
  }

  cout << ans.size() << endl;
  for (auto v : ans)
    cout << v << ' ';
}