#include <bits/stdc++.h>
using namespace std;

void calc_prev(vector<int> &s, vector<int> &prev) {
  int n = s.size();
  for (int i = 2; i <= n; ++i) {
    int j = i-1;
    while (j > 0) {
      if (s[j] == s[i]) {
        prev[i] = j;
        break;
      }
      else j--;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;
  vector<int> s(n+1), t(m+1);
  for (int i = 1; i <= n; ++i)
    cin >> s[i];
  for (int i = 1; i <= m; ++i)
    cin >> t[i];

  s[0] = t[0] = -1;

  if (m > n) {
    swap(s, t);
    swap(n, m);
  }

  vector<int> prevs(n+1), prevt(m+1);
  calc_prev(s, prevs);
  calc_prev(t, prevt);

  
  vector<int> A(m +1), B(m+1), aux(m+1);
  // for (auto x : A)
  //   cout << x << ' ';
  // cout << endl;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (s[i] == t[j] && prevs[i] > 0 && prevt[j] > 0) {
        B[j] = aux[prevt[j]] + 2;
      }
      B[j] = max({B[j], A[j], B[j-1]});
    }
    for (int j = 1; j <= m; ++j) {
      if (s[i] == t[j])
        aux[j] = A[j-1];
    }
    // for (auto x : B)
    //   cout << x << ' ';
    // cout << endl;
    swap(A, B);
  }

  cout << A[m];
}

// 9 7 
// 1 4 1 4 1 3 3 4 3 
//   1 4 4 4 1 4 4