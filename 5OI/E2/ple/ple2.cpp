#include <bits/stdc++.h>
using namespace std;
#define MAX 1000
#define INF 1e9

int DP[MAX+1][MAX+1];

int main() {
  int T, A, n;
  cin >> T >> A >> n;
  int ox[n], ni[n], w[n];
  for (int i = 0; i < n; ++i)
    cin >> ox[i] >> ni[i] >> w[i];

  for (int i = 0; i <= T; ++i)
    fill(DP[i], DP[i] + A + 1, -INF);
  DP[0][0] = 0;

  for (int i = 0; i < n; ++i) {
    for (int t = T; t >= 0; --t) {
      for (int a = A; a >= 0; --a) {
        int tbound = min(T, t + ox[i]);
        int abound = min(A, a + ni[i]);

        DP[tbound][abound] = max(DP[tbound][abound], DP[t][a] - w[i]);
      }
    }
  }

  cout << -DP[T][A];
} 