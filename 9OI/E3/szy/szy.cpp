#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n; cin >> n;
  const int n1 = (n+1)/2, n2 = n/2;
  vector<int> v1(n1), v2(n2);
  for (auto &x : v1)
    cin >> x;
  for (auto &x : v2)
    cin >> x;
  int S; cin >> S;

  vector<pair<int, int>> s1(1 << n1), s2(1 << n2);
  for (int X = 0; X < (1 << n1); ++X) {
    s1[X].second = X;
    for (int i = 0; i < n1; ++i)
      s1[X].first += (bool)((1 << i) & X)*v1[i];
  }
  for (int X = 0; X < (1 << n2); ++X) {
    s2[X].second = X;
    for (int i = 0; i < n2; ++i)
      s2[X].first += (bool)((1 << i) & X)*v2[i];
  }

  sort(s1.begin(), s1.end());
  sort(s2.begin(), s2.end());

  int I = 0, J = s2.size()-1;
  while (I < (1 << n1) && J >= 0) {
    if (s1[I].first + s2[J].first == S)
      break;
    else if (s1[I].first + s2[J].first < S)
      ++I;
    else
      --J;
  }

  I = s1[I].second, J = s2[J].second;
  for (int i = 0; i < n1; ++i) {
    cout << (bool)((1 << i) & I);
  }
  for (int i = 0; i < n2; ++i) {
    cout << (bool)((1 << i) & J);
  }
}