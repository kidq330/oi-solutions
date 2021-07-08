#include <bits/stdc++.h>
#define DLEN 200
#define INF 1000000000000000000
using namespace std;
typedef long long ll;

vector<int> p(200);
ll DP[DLEN + 1][DLEN + 1][DLEN + 1];
//    ^digits ^sum of dig.^mod m

int mod(const int &n, const int &c, const int &k, const int &m) {
  return ((n - p[k]*c) + 99*m) % m;  
}

void calcDP(const int &s, const int &m) {
  for (int i = 0; i <= 9; ++i)
    ++DP[1][i][i%m];
  for (int i = 0; i < m; ++i)
    ++DP[0][0][i];

  for (int k = 2; k <= DLEN; ++k) {
    for (int n = 0; n < m; ++n) {
      for (int z = 0; z <= s; ++z) {
        for (int c = 0; c <= min(9, z); ++c) {
          DP[k][z][n] += DP[k-1][z - c][mod(n, c, k-1, m)];
          DP[k][z][n] = min(DP[k][z][n], 1ll*INF);
        }
      }
    }
  }
}


int main() {
  int s, m, q;
  cin >> s >> m >> q;

  p[0] = 1;
  for (int i = 1; i <= 200; ++i)
    p[i] = (p[i-1]*10)%m;

  calcDP(s, m);
  while (q--) {
    ll k;
    cin >> k;

    if (DP[200][s][0] < k) {
      cout << "NIE" << endl;
      continue;
    }

    vector<int> ans;
    int sum = s, md = 0;

    for (int i = DLEN; i > 0; --i) {
      for (int c = 0; c < 10; ++c) {
        int nmd = mod(md, c, i-1, m);
        ll &ways = DP[i-1][sum - c][nmd];

        if (ways >= k) {
          ans.push_back(c);
          sum -= c;
          md = nmd;
          break;
        }
        k -= ways;
      }
    }

    int pos = 0;

    while (ans[pos] == 0)
      ++pos;

    while (pos < ans.size())
      cout << ans[pos++];
    cout << endl;
  }
}