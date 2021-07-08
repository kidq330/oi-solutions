#include <bits/stdc++.h>
#define INF INT32_MAX
using namespace std;

const int alpha = 26;

int subarr_sum(string &s, const char &c) {
  vector<int> fq(alpha, 0), mn(alpha, INF), prev_sum(alpha, 0), res(alpha, 0);

  for (int i = 0; i < s.size(); ++i) {
    int s_i = s[i] - 'a';
    ++fq[s_i];
    if (s[i] == c) {
      // the complexity is cheated because this actually makes the algo O(n*alfa^2)
      for (int ci = 0; ci < alpha; ++ci) {
        res[ci] = max(res[ci], fq[c - 'a'] - fq[ci] - mn[ci]);
      }
    }
    else {
      mn[s_i] = min(mn[s_i], prev_sum[s_i]);
      prev_sum[s_i] = fq[c - 'a'] - fq[s_i];
      res[s_i] = max(res[s_i], fq[c - 'a'] - fq[s_i] - mn[s_i]);
    }
  }

  return *max_element(res.begin(), res.end());
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  string s;
  cin >> n >> s;

  vector<int> fq(alpha, 0);
  for (auto c : s)
    ++fq[c - 'a'];
  int diff = 0;

  for (char c = 'a'; c <= 'z'; ++c) {
    if (fq[c - 'a'])
      diff = max(diff, subarr_sum(s, c));
  }

  cout << diff;
}