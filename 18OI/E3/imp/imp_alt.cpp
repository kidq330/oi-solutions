// Just takes the 2 steps from the solution and throws them in a while loop
// Gets a 100 too for some reason lol
// O(n^3)
#include <bits/stdc++.h>
using namespace std;

vector< vector<bool> > adj;
vector<int> res;
vector<bool> del;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;

  adj.resize(n, vector<bool>(n));
  del.resize(n, false);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    adj[a][b] = 1;
    adj[b][a] = 1;
  }

  while (true) {
    bool deleted = false;
    for (int i = 0; i < n; ++i) {
      if (del[i]) continue;
      for (int j = i+1; j < n; ++j) {
        if (del[j]) continue;
        if (!adj[i][j]) {
          del[i] = true;
          del[j] = true;
          deleted = true;
          break;
        }
      }
      if (deleted)
        break;
    }
    if (!deleted)
      break;
  }

  int i = 0, k = 0;
  while (k != n/3) {
    if (!del[i]) {
      cout << i + 1 << ' ';
      ++k;
    }
    ++i;
  }
}

// 9 15
// 1 3
// 3 2
// 2 1
// 4 6
// 6 5
// 5 4
// 9 7
// 8 7
// 9 8
// 4 3
// 2 9
// 2 7
// 7 4
// 3 6
// 5 7