#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll b1 = 2e5 + 3,
          b2 = 213737,
          p = 1e9 + 696969;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n; cin >> n;

  // inv[b][i] = (x^i)^(-1) mod p
  array<vector<ll>, 2> inv = {vector<ll>(n), vector<ll>(n)};
  array<vector<ll>, 2> pow = {vector<ll>(n), vector<ll>(n)};
  array<ll,2> invs;

  // invs[i] = exp(bi, p-2);
  invs[0] = 666484205;
  invs[1] = 726262250;
  inv[0][0] = 1;
  inv[1][0] = 1;
  pow[0][0] = 1;
  pow[1][0] = 1;
  for (int i = 0; i < 2; ++i) {
    for (int j = 1; j < n; ++j) {
      pow[i][j] = (pow[i][j-1]*(i == 0 ? b1 : b2)) % p;
      inv[i][j] = (inv[i][j-1]*invs[i]) % p;
    }
  }

  vector<vector<ll>> H1(2, vector<ll>(n)),
                      H2(2, vector<ll>(n));

  cin >> H1[0][0];
  H1[1][0] = H1[0][0];
  H2[0][0] = H1[0][0];
  H2[1][0] = H1[0][0];  

  ll bp1 = b1, bp2 = b2;
  for (int i = 1; i < n; ++i) {
    ll a; cin >> a;
    H1[0][i] = (H1[0][i-1] + a*bp1) % p;
    H2[0][i] = (H2[0][i-1] + a*bp2) % p;
    H1[1][i] = (H1[1][i-1]*b1 + a) % p;
    H2[1][i] = (H2[1][i-1]*b2 + a) % p;
    bp1 = (bp1*b1)%p, bp2 = (bp2*b2)%p;
  }

  int res = 0;
  vector<int> appropriate;
  for (int k = 1; k <= n; ++k) {
    set<array<int, 2>> S;
    int pal = 0;
    for (int i = 0; i <= n-k; i += k) {
      int h1 = (H1[1][i+k-1] - ((i == 0 ? 0 : H1[1][i-1])*pow[0][k])%p + p) % p, 
          h1r = (((H1[0][i+k-1] - (i == 0 ? 0 : H1[0][i-1]) + p) % p)*inv[0][i]) % p,
          h2 = (H2[1][i+k-1] - ((i == 0 ? 0 : H2[1][i-1])*pow[1][k])%p + p) % p, 
          h2r = (((H2[0][i+k-1] - (i == 0 ? 0 : H2[0][i-1]) + p) % p)*inv[1][i]) % p;
      pal += S.insert({h1, h2}).second && h1 == h1r && h2 == h2r;
      S.insert({h1r, h2r});
    }
    int uniq = (S.size() - pal)/2 + pal;
    if (uniq > res) {
      res = uniq;
      appropriate = {k};
    }
    else if (uniq == res) appropriate.push_back(k);
  }

  cout << res << ' ' << appropriate.size() << '\n';
  for (auto x : appropriate)
    cout << x << ' ';
}