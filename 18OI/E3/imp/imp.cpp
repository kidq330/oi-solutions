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

  for (int i = 0; i < n; ++i) {
    if (del[i]) continue;
    for (int j = i+1; j < n; ++j) {
      if (!adj[i][j] && !del[j]) {
        del[i] = true;
        del[j] = true;
        break;
      }
    }
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

// 9 24
// 1 6
// 1 5
// 1 4
// 1 3
// 1 2
// 6 2
// 6 3
// 6 4
// 6 5
// 5 2
// 5 3
// 5 4
// 4 2
// 4 3
// 3 2
// 7 4
// 7 3
// 7 5
// 8 1
// 8 3
// 8 2
// 9 1
// 9 2
// 9 5

// 12 42
// 1 2
// 1 3
// 1 4
// 1 5
// 1 6
// 1 7
// 1 8
// 2 3
// 2 4
// 2 5
// 2 6
// 2 7
// 2 8
// 3 4
// 3 5
// 3 6
// 3 7
// 3 8
// 4 5
// 4 6
// 4 7
// 4 8
// 5 6
// 5 7
// 5 8
// 6 7
// 6 8
// 7 8
// 12 5
// 12 4
// 12 1
// 12 8
// 11 2
// 11 3
// 11 4
// 10 1
// 10 4
// 10 6
// 9 2
// 9 7
// 9 8
// 6 9
