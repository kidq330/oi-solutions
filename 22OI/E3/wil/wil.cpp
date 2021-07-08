#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// S[i:j)
ll sum(int i, int j, vector<ll> const& pref) {
  return pref[j-1] - pref[i-1];
}

struct monoqueue {
  deque<int> Q;
  int d;

  monoqueue(int _d) : d(_d) {}
  monoqueue(){}

  void push(int x, vector<ll> const& pref) {
    while (!Q.empty() && sum(Q.back(), Q.back()+d, pref) < sum(x, x+d, pref))
      Q.pop_back();
    Q.push_back(x);
  }

  void pop(int x) {
    if (!Q.empty() && Q.front() == x)
      Q.pop_front();
  }

  int get_max() {
    return Q.front();
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, d; 
  ll p;
  cin >> n >> p >> d;

  vector<int> v(n+1);
  vector<ll> pref(n+1);
  for (int i = 1; i <= n; ++i) {
    cin >> v[i];
    pref[i] = v[i] + pref[i-1];
  }
  
  int i = 1, j = d+1, len = d;
  // 2ptr on [i;j)
  monoqueue Q(d);
  Q.push(i, pref);
  while (i <= n) {
    int m = Q.get_max();
    ll s = pref[j-1] - pref[i-1] - sum(m, m+d, pref);
    if (s <= p && j <= n+1) {
      len = max(len, j-i);
      ++j;
      Q.push(j-d, pref);
    }
    else {
      Q.pop(i);
      ++i;
    }
  }

  cout << len;
}