#include <bits/stdc++.h>
#define INF INT32_MAX
using namespace std;

const int alpha = 26;

// Problem Desc.:
// Find the maximum of the function f(S) = fq(c1, j) - fq(c2, j) - (fq(c1, i) - fq(c2, j))
// So just the substring where the difference between most and least common chars is greatest

// Complexity: O(n*alfa)
// \Sum_{c1} \Sum_{c2} (occ(c1) + occ(c2)) = O(2*(\Sum_{c1} \Sum_{c2} occ(c2))) =
// = O(2*alfa*\Sum_{c2} occ(c2)) = O(2*alfa*n)

int subarr_sum(const int &n, list<int> &occ1, list<int> &occ2) {
  int sum = 0, prev_sum = 0, res = 0;
  int mn = INF;
  auto it1 = occ1.begin();
  auto it2 = occ2.begin();

  while (*it1 != n || *it2 != n) {
    if (*it1 < *it2) {
      ++sum;
      ++it1;
    }
    else {
      --sum;
      ++it2;
      mn = min(mn, prev_sum);
      prev_sum = sum;
    }
    res = max(res, sum - mn);
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  string s;
  cin >> n >> s;

  vector< list<int> > occ(alpha);

  for (int i = 0; i < n; ++i)
    occ[s[i] - 'a'].push_back(i);
    
  for (int i = 0; i < alpha; ++i)
    if (!occ[i].empty())
      occ[i].push_back(n);
      
  int diff = 0;

  for (int c1 = 0; c1 < alpha; ++c1) {
    if (!occ[c1].empty()) {
      for (int c2 = 0; c2 < alpha; ++c2) {
        if (!occ[c2].empty() && c1 != c2) {
          diff = max(diff, subarr_sum(n, occ[c1], occ[c2]));
        }
      }
    }
  }

  cout << diff;
}