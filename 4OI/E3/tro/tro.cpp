#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, m; cin >> n >> m;
  vector<int> red(n);
  while (m--) {
    int a, b; cin >> a >> b;
    ++red[a-1], ++red[b-1];
  }

  int tr2 = 0;
  for (int i = 0; i < n; ++i) {
    tr2 += (n-1-red[i])*red[i];
  }

  cout << n*(n-1)*(n-2)/6 - (tr2 >> 1);
}