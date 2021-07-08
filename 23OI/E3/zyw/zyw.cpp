#include <bits/stdc++.h>
using namespace std;

vector<array<int, 4>> edg;
vector<int> parent;
vector<bool> ans;

int find(const int &v) {
  return (parent[v] == -1 ? v : parent[v] = find(parent[v]));
}

bool Union(int u, int v) {
  u = find(u), v = find(v);
  if (u == v)
    return false;
  
  parent[u] = v;
  return true;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int m, n; cin >> m >> n;
  
  edg.resize(2*m*n - m - n);
  ans.resize(2*m*n - m - n);
  parent.resize(m*n, -1);

  int t = -1;
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n-1; ++i) {
      char w; cin >> w;
      const int u = n*j + i, v = u+1;
      edg[++t] = {w == 'C', u, v, t};
    }
  }
  for (int j = 0; j < m-1; ++j) {
    for (int i = 0; i < n; ++i) {
      char w; cin >> w;
      const int u = n*j + i, v = u+n;
      edg[++t] = {w == 'C', u, v, t};
    }
  }

  int s = 0, cis = 0;
  sort(edg.begin(), edg.end());
  for (auto e : edg) {
    if (Union(e[1], e[2]))
      ans[e[3]] = true;
    else {
      ++s;
      cis += e[0];
    }
  }

  cout << s << ' ' << cis << '\n';
  t = -1;
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n-1; ++i) {
      cout << (ans[++t] ? '.' : 'Z');
    } cout << '\n';
  }
  for (int j = 0; j < m-1; ++j) {
    for (int i = 0; i < n; ++i) {
      cout << (ans[++t] ? '.' : 'Z');
    } cout << '\n';
  }
}