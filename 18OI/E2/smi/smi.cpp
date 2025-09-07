#include <bits/stdc++.h>

struct edge {
  int id, cross_id;
  edge() {}
  edge(int _id, int _cid) : id(_id), cross_id(_cid) {}
};

// adjacency list
std::vector<std::list<edge>> adj;

// `adj[v][u].cross_id` indexes an iterator in `links` to `adj[u][v]` for
// bidirectional edge deletion in O(1)
std::vector<std::list<edge>::iterator> links;

// placeholder vector used by dfs and cycle decomposer
std::vector<int> path;

std::vector<bool> vis;

void read(const int &E, const int &V) {
  adj.resize(V + 1);
  vis.resize(V + 1);
  links.resize(2 * E);

  int cnt = 0;

  for (int i = 0; i < E; ++i) {
    int a, b;
    bool before, after;

    std::cin >> a >> b >> before >> after;

    if (before != after) {
      adj[a].push_back(edge(b, cnt));
      adj[b].push_back(edge(a, cnt + 1));

      links[cnt] = adj[b].end();
      links[cnt + 1] = adj[a].end();
      --links[cnt], --links[cnt + 1];

      cnt += 2;
    }
  }
}

// Hierholzer's algo for finding eulerian path/cycle in an undirected connected
// graph deletes edges when run
void HHdfs(int node) {
  vis[node] = true;

  while (!adj[node].empty()) {
    edge next = adj[node].back();

    adj[node].pop_back();
    adj[next.id].erase(links[next.cross_id]);

    HHdfs(next.id);
  }

  path.push_back(node);
}

void decompose(std::vector<std::vector<int>> &eulerian_cycles,
               std::vector<std::vector<int>> &cycles) {
  for (auto cycle : eulerian_cycles) {

    for (auto x : cycle) {

      // once we revisit a vertex, we backtrack and add the vertices to res
      if (vis[x]) {
        cycles.push_back({x});
        auto &res = cycles.back();

        while (vis[x]) {
          int v = path.back();
          path.pop_back();
          res.push_back(v);
          vis[v] = false;
        }
      }

      path.push_back(x);
      vis[x] = true;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  int E, V;
  std::cin >> V >> E;
  read(E, V);

  // check if eulerian cycle exists
  for (auto x : adj) {
    if (x.size() % 2) {
      std::cout << "NIE";
      return 0;
    }
  }

  std::vector<std::vector<int>> euler_cycles;
  // loops over vertices in case of a disconnected graph
  for (int i = 1; i <= V; ++i) {
    if (!vis[i]) {
      HHdfs(i);
      euler_cycles.emplace_back(path);
      path.clear();
    }
  }

  // stores final res.
  std::vector<std::vector<int>> cycles;

  fill(vis.begin(), vis.end(), false);

  decompose(euler_cycles, cycles);

  std::cout << cycles.size() << std::endl;
  for (auto cycle : cycles) {
    std::cout << cycle.size() - 1 << ' ';
    for (auto x : cycle) {
      std::cout << x << ' ';
    }
    std::cout << std::endl;
  }
}