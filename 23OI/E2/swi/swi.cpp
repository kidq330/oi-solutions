// Problem Desc.:
// In a sequence of length n, q pairs of segments are identical.
// Calculate the maximum possible number of distinct values this sequence can have.

// Preprocessing: O(nlogn)
// Single query: O(alpha(n))  where alpha(n) is the inverse ackermann function.
// Total complexity: O(nlogn) assuming DSU operations in O(1)

// Solved using a combination of Divide & Conquer and the Disjoint Set structure, or D&C DSU (because it sounds cool).
// The problem is made for KMR, but using just the 2^k length subsegment heuristic of KMR/sparse tables, 
// information about all length 2^k subsegments can be pushed down to 2^(k-1) subsegments.

// For all subsegments of length 2^k we construct log(n) parent arrays for DSU.
// When two subsegments are equal, we unionize them.
// Since it's not possible to explicitly unionize both subsegments, one can unionize them character by character (in O(n^2)),
// or for a subsegment of length k, unionize 2 subsegments of length log(k) that fully cover the subsegment (kinda like KMR comparison) 
// with 2 corresponding subsegments from the subsegment meant to be identical.

// Now after all query handling we start pushing information from bigger to smaller subsegments. 
// KMR[k][a] == KMR[k][b] => KMR[k-1][a] == KMR[k-1][b] && KMR[k-1][a + 2^(k-1)] == KMR[k-1][b + 2^(k-1)]
// Similarily here we find the root of a subsegment and its smaller components and unionize them
// with the components of the subsegment.

// Thus, without linear scans during queries we have sucessfully updated the parent array of length 1 subsegments,
// and can now iterate over it to count distinct elements.

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> parent, set_rank;
vector<int> lg;

int find_set(const int &a, const int &lg) {
  if (parent[lg][a] == a)
    return a;
  parent[lg][a] = find_set(parent[lg][a], lg);
  return parent[lg][a];
}

void unionize(const int &a, const int &b, const int &lg) {
  int a_root = find_set(a, lg),
      b_root = find_set(b, lg);
  
  if (a_root == b_root)
    return;
  
  if (set_rank[lg][a_root] > set_rank[lg][b_root])
    parent[lg][b_root] = a_root;
  else {
    parent[lg][a_root] = b_root;
    if (set_rank[lg][a_root] == set_rank[lg][b_root])
      ++set_rank[lg][b_root];
  }
}

int main() {
  int n, q;
  cin >> n >> q;
  
  lg.resize(n+1);
  lg[1] = 0;
  for (int i = 2; i <= n; ++i)
    lg[i] = lg[i/2] + 1;

  parent.resize(lg[n]+1);
  set_rank.resize(lg[n]+1);

  for (int i = 0; i <= lg[n]; ++i) {
    int sz = n - (1 << i) + 1;
    parent[i].resize(sz);
    set_rank[i].resize(sz);
    for (int j = 0; j < sz; ++j)
      parent[i][j] = j;
  }

  while (q--) {
    int a, b, l;
    cin >> a >> b >> l;
    --a, --b;
    unionize(a, b, lg[l]);
    unionize(a + l - (1 << lg[l]), b + l - (1 << lg[l]), lg[l]);
  }

  for (int t = lg[n]; t > 0; --t) {
    for (int i = 0; i < parent[t].size(); ++i) {
      int root = find_set(i, t);
      unionize(i, root, t-1);
      unionize(i + (1 << (t-1)), root + (1 << (t-1)), t-1);
    }
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (i == find_set(i, 0))
      ++ans;
  }
  cout << ans;
}
