#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

constexpr int Tsize = 1 << 21;

vector<ii> T(Tsize); 

ii _merge(ii p1, ii p2) {
  if (p1.first == p2.first)
    return {p1.first, p1.second+p2.second};
  else if (p1.second > p2.second)
    return {p1.first, p1.second-p2.second};
  else 
    return {p2.first, p2.second-p1.second};
}

void build(int v, int tl, int tr, vector<int> &val) {
  if (tl == tr) {
    T[v] = {val[tl], 1};
    return;
  }
  int tm = (tl+tr)/2;
  build(2*v, tl, tm, val);
  build(2*v+1, tm+1, tr, val);
  T[v] = _merge(T[2*v], T[2*v+1]);
}

ii query(int v, int tl, int tr, int l, int r) {
  if (tr < l || r < tl)
    return {-1, 0};
  if (l <= tl && tr <= r)
    return T[v];
  int tm = (tl+tr)/2;
  return _merge(query(2*v, tl, tm, l, r), 
                query(2*v+1, tm+1, tr, l, r));
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, q; cin >> n >> q;
  vector<int> v(n), sum(q), cand(q), len(q);
  vector<vector<int>> st(n), en(n);
  for (auto &x : v) {
    cin >> x;
    --x;
  }

  build(1, 0, n-1, v);

  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    st[a].push_back(i);
    en[b].push_back(i);
    len[i] = b-a+1;
    cand[i] = query(1, 0, n-1, a, b).first;
  }
  vector<int> fq(n);
  for (int i = 0; i < n; ++i) {
    for (auto qn : st[i]) {
      sum[qn] -= fq[cand[qn]];
    }
    ++fq[v[i]];
    for (auto qn : en[i]) {
      sum[qn] += fq[cand[qn]];
      if (2*sum[qn] > len[qn])
        ++cand[qn];
      else
        cand[qn] = 0;
    }
  }
  for (auto x : cand)
    cout << x << '\n';
}