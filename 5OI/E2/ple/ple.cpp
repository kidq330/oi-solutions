#include <bits/stdc++.h>
using namespace std;

int DP[22][80];

int main() {
  int t, a, n;
  cin >> t >> a >> n;
  int ox[n+1] = {}, ni[n+1] = {}, w[n+1] = {};
  for (int i = 0; i < n; ++i) {
    cin >> ox[i] >> ni[i] >> w[i];
  }

  int td, ad = 0;

  for (int i = 0; i <= t; ++i)
    fill(DP[i], DP[i] + a + 1, 1 << 30);
  DP[0][0] = 0;

  for (int i = 0; i < n; ++i) {
    for (int ti = t; ti >= 0; --ti) {
      for (int ai = a; ai >= 0; --ai) {
        td = min(t, ti + ox[i]);
        ad = min(a, ai + ni[i]);

        DP[td][ad] = min(DP[td][ad], DP[ti][ai] + w[i]);
      }
    }
  }
  cout << DP[t][a];
}

