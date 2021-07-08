#include <bits/stdc++.h>
using namespace std;

const int INF = 1<<30;
typedef pair<int, int> ii;


int main() {
  ios::sync_with_stdio(0);
  
  int n; cin >> n;
  vector<int> v(n+1), s(n+1);
  for (int i = 1; i <= n; ++i) {
    cin >> v[i];
    s[i] = i;
  }
  v.push_back(INF);
  
  sort(s.begin()+1, s.end(), [v](int i, int j){return i-v[i] < j-v[j] || (i-v[i] == j-v[j] && v[i] < v[j]);});
  vector<int> d(n+2, n+1), p(n+1, -1);
  d[0] = 0;

  for (int j = 1; j <= n; ++j) {
    if (s[j]-v[s[j]] < 0) continue;
    int i = s[j], l = -1, r = n+1;
    while (l+1 < r) {
      int m = (l+r)/2;
      if (v[d[m]] < v[i])
        l = m;
      else
        r = m;
    }
    if (v[d[l]] < v[i] && v[i] < v[d[r]]) {
      d[r] = i;
      p[i] = d[l];
    }
  }
  
  vector<int> seq;
  int last = n;
  for (; d[last] == n+1; --last);
  last = d[last];
  while (last != 0) {
    seq.push_back(last);
    last = p[last];
  }

  last = 0;
  vector<int> del;
  while (!seq.empty()) {
    int i = seq.back();
    seq.pop_back();
    for (int j = 1; j <= i-last-v[i]+v[last]; ++j)
      del.push_back(last+j);
    last = i;
  }
  cout << del.size() << '\n';
  for (auto x : del) cout << x << ' ';
}

