#include <bits/stdc++.h>
using namespace std;

const int seg = 1 << 19, Y = 70001;
vector<int> T(seg),
            lazy(seg);
int sum = 0;

void push(int v) {
  T[2*v] += lazy[v];
  T[2*v+1] += lazy[v];
  lazy[2*v] += lazy[v];
  lazy[2*v+1] += lazy[v];
  lazy[v] = 0;
}

void incr(int v, int tl, int tr, int l, int r, int k = 1) {
  if (tr < l || r < tl)
    return;
  if (l <= tl && tr <= r) {
    lazy[v] += k;
    T[v] += k;
    return;
  }
  push(v);
  int tm = (tl + tr)/2;
  incr(2*v, tl, tm, l, r, k);
  incr(2*v+1, tm+1, tr, l, r, k);
  T[v] = max(T[2*v], T[2*v+1]);
}

int maxT() {
  return T[1];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int s, w, n; cin >> s >> w >> n;
  vector<array<int, 2>> v(n);
  for (auto &x : v) {
    cin >> x[0] >> x[1];
    x[1] += 40000;
  }
  
  sort(v.begin(), v.end());
  v.push_back({40001, Y});

  int i = 0;
  array<int, 2> last = {v[i][0]+s, Y};
  int j = upper_bound(v.begin(), v.end(), last) - v.begin();
  
  for (int k = 0; k < j; ++k) {
    incr(1, 0, Y, v[k][1]-w, v[k][1]);
  }

  int res = maxT();
  while (j != n) {
    int col = v[i][0];
    while (v[i][0] == col) {
      incr(1, 0, Y, v[i][1]-w, v[i][1], -1);
      ++i;
    }
    while (v[j][0] <= v[i][0]+s) {
      incr(1, 0, Y, v[j][1]-w, v[j][1], 1);
      ++j;
    }
    res = max(res, maxT());
  }
  
  cout << res;
}