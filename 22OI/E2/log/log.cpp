#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> ii;

ii operator+(ii const& a, ii const& b) {
  return {a.first+b.first,
          a.second+b.second};
}

struct Query {
  char type;
  int idx, s;
};

vector<ii> T(1 << 22);

void upd(int v, int tl, int tr, int l, int r, ii val) {
  if (tr < l || r < tl) {
    return;
  }
  if (l <= tl && tr <= r) {
    T[v] = T[v] + val;
    return;
  }
  int tm = (tl + tr)/2;
  upd(2*v, tl, tm, l, r, val);
  upd(2*v+1, tm+1, tr, l, r, val);
}

ii query(int v, int tl, int tr, int s) {
  if (tl == tr) {
    return T[v];
  }
  int tm = (tl+tr)/2;
  if (s <= tm)
    return query(2*v, tl, tm, s) + T[v];
  else
    return query(2*v+1, tm+1, tr, s) + T[v];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, q; cin >> n >> q;
  vector<int> vals(q);
  vector<Query> qs(q);
  unordered_map<int, int> M;
  M.max_load_factor(0.25);
  M.reserve(1 << 16);

  for (int i = 0; i < q; ++i) {
    auto &Q = qs[i];
    cin >> Q.type >> Q.idx >> Q.s;
    Q.idx -= Q.type == 'U';
    vals[i] = Q.s;
  }

  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  int t = 0;
  M[0] = 0;
  for (auto x : vals) {
    M[x] = ++t;
  }
  vals.clear();
  
  vector<int> v(n);
  for (auto Q : qs) {
    if (Q.type == 'U') {
      if (v[Q.idx] < Q.s) {
        upd(1, 0, t, M[v[Q.idx]], M[Q.s]-1, {-v[Q.idx], 1});
        upd(1, 0, t, M[Q.s], t, {Q.s-v[Q.idx], 0});
      }
      else {
        upd(1, 0, t, M[Q.s], M[v[Q.idx]]-1, {Q.s, -1});
        upd(1, 0, t, M[v[Q.idx]], t, {Q.s-v[Q.idx], 0});
      }
      v[Q.idx] = Q.s;
    }
    else {
      auto res = query(1, 0, t, M[Q.s]);
      ll sum = res.first/Q.s + res.second;
      cout << (Q.idx <= sum ? "TAK" : "NIE") << '\n';
    }
  }
}