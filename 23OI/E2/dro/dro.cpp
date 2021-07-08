// Treść: Dany graf skierowany który jest <sprawiedliwy>, tzn
// Jeśli nie istnieje ścieżka z u do v, to z v do u może istnieć
// co najwyżej jedna ścieżka
// Dla każdego wierzchołka policzyć do ilu innych wierzchołków może dojść

// Rozwiązanie: silnie spójna składowa to taki podgraf grafu skierowanego,
// gdzie z każdego wierzchołka można dojść do każdego innego.
// Do znalezienia SSS można użyć algorytmu Tarjana lub Kosaraju w czasie O(|V|+|E|)

// Kondensacją grafu skierowanego jest graf, którego każdy wierzchołek
// reprezentuje pewną SSS oryginalnego grafu. Krawędzie pomiędzy
// spójnymi są zachowane. Mając dany podział na SSS można łatwo
// zbudować graf skondensowany.
// Jedną z cech kondensacji grafu jest to, że zawsze będzie grafem skierowanym acyklicznym.
// Wiemy jeszcze, że graf jest <sprawiedliwy> - pomoże to w dalszej części rozwiązania.

// Zdefiniujmy funkcję f(v) = |{u : istnieje ścieżka z v do u}|
// Wiedząc że graf jest <sprawiedliwy>, widzimy że zachodzą własności:
// 1. f(u) == f(v) dla każdej pary u, v należącej do tej samej SSS
// 2. Niech scc(v) oznacza SSS w której jest v. Wtedy z v da się również
// dojść do wszystkich SSS sąsiadujących z scc(v). Ze względu na specyficzną
// topologię grafu da się je policzyć prostą rekurencją.

// Złożoność: O(|V| + |E|)

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj, adj2;
vector<int> scc, low, in;
vector<bool> on_stack;
stack<int> S;
auto &sub = low;
auto &vis = on_stack;
int scccnt = 0;

void tarjan(int v, int &t) {
  S.push(v);
  on_stack[v] = true;
  in[v] = ++t;
  low[v] = v;
  for (auto x : adj[v]) {
    if (in[x] == -1)
      tarjan(x, t);
    if (on_stack[x] && in[low[x]] < in[low[v]])
      low[v] = low[x];  
  }
  if (v == low[v]) {
    while (true) {
      auto u = S.top();
      S.pop();
      scc[u] = scccnt;
      on_stack[u] = false;
      low[u] = v;
      if (u == v) break;
    }
    ++scccnt;
  }
}

void dfs(int v) {
  vis[v] = true;
  for (auto x : adj2[v]) {
    if (!vis[x]) {
      dfs(x);
    }
    sub[v] += sub[x];
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m; cin >> n >> m;
  adj.resize(n);
  scc.resize(n);
  low.resize(n);
  in.resize(n, -1);
  on_stack.resize(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b;
    adj[a-1].push_back(b-1);
  }

  int t = -1;
  for (int i = 0; i < n; ++i) {
    if (in[i] == -1) {
      tarjan(i, t);
    }
  }

  in.clear();

  adj2.resize(scccnt);
  vis.resize(scccnt);
  sub.resize(scccnt);
  fill(vis.begin(), vis.end(), false);
  fill(sub.begin(), sub.end(), 0);
  for (int i = 0; i < n; ++i) {
    ++sub[scc[i]];
    for (auto x : adj[i]) {
      if (scc[i] != scc[x]) {
        adj2[scc[i]].push_back(scc[x]);
      }
    }
  }

  for (int i = 0; i < scccnt; ++i) {
    adj2[i].erase(unique(adj2[i].begin(), adj2[i].end()), adj2[i].end());
  }

  for (int i = 0; i < scccnt; ++i) {
    if (!vis[i])
      dfs(i);
  }

  for (int i = 0; i < n; ++i) {
    cout << sub[scc[i]]-1 << '\n';
  }
}

