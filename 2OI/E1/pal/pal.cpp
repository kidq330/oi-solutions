#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int p = 1e9 + 696969, b = 31, INF = 1 << 30;

bool is_palindrome(int i, int j, vector<int> const&h1, vector<int> const&h2, vector<int> const&pw) {
  return ((j-1+1)%2 == 0) && (h1[j] - h1[i-1] + p)%p == (ll)pw[i-1]*(p + h2[j] - (ll)pw[j-i+1]*h2[i-1] % p)%p;
}

void answer(vector<int> const&pred, stack<int> &jmp, string &s) {
  const int n = pred.size();
  int it = n-1;
  while (it != -1) {
    jmp.push(it);
    it = pred[it];
  }
  jmp.pop();
  it = 0;
  while (!jmp.empty()) {
    cout << s.substr(it, jmp.top()-it) << ' ';
    it = jmp.top();
    jmp.pop();
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  string s; cin >> s;
  const int n = s.size();
  vector<int> h1(n+1), h2(n+1), pw(n+1);
  
  pw[0] = 1;
  for (int i = 0; i < n; ++i) {
    h1[i+1] = (h1[i] + (ll)pw[i]*(s[i]-'a')%p) % p;
    h2[i+1] = ((ll)h2[i]*b%p + (s[i] - 'a')) % p;
    pw[i+1] = (ll)pw[i]*b % p;
  }

  vector<vector<bool>> M(n+1, vector<bool>(n+1));
  // M[i][j] iff s[i:j-1] is a palindrome
  // need to find longest & shortest path from 0 to n
  for (int i = 0; i < n; ++i) {
    for (int j = i+2; j <= n; ++j) {
      M[i][j] = is_palindrome(i+1, j, h1, h2, pw);
    }
  }

  h1.clear(); h2.clear();
  vector<int> dp1(n+1, -INF), dp2(n+1, INF), pred1(n+1, -1), pred2(n+1, -1);
  dp1[0] = 0; dp2[0] = 0; 
  for (int i = 0; i < n; ++i) {
    for (int j = i+1; j <= n; ++j) {
      if (M[i][j]) {
        if (dp1[j] < dp1[i]+1) {
          dp1[j] = dp1[i]+1;
          pred1[j] = i;
        }
        if (dp2[j] > dp2[i]+1) {
          dp2[j] = dp2[i]+1;
          pred2[j] = i;
        }
      }
    } 
  }
  pred1[n-1] = pred1[n];
  pred2[n-1] = pred2[n];
  int it = n-1;
  if (pred1[n-1] == -1 || pred2[n-1] == -1) {
    cout << "NIE";
    return 0;
  }
  stack<int> jmp;
  answer(pred2, jmp, s);
  cout << '\n';
  answer(pred1, jmp, s);
}