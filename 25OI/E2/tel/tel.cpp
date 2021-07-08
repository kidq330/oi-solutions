#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
#define X first
#define Y second

struct node {
  pll lazy = {0, 0};
  ll s = 0;
  node(){}
};

constexpr int sz = 1 << 21;
vector<node> T(sz);

pll operator+(pll const& a, pll const& b) {
  return {a.X+b.X, a.Y+b.Y};
}

void push(int v, int tl, int tr) {
  int tm = (tl + tr)/2;
  T[2*v].lazy = T[2*v].lazy + T[v].lazy;
  T[2*v].s += (2*T[v].lazy.X + (tm-tl)*T[v].lazy.Y)*(tm-tl+1)/2;
  T[v].lazy.X += (tm-tl+1)*T[v].lazy.Y;
  T[2*v+1].lazy = T[2*v+1].lazy + T[v].lazy;
  T[2*v+1].s += (2*T[v].lazy.X + (tr-tm-1)*T[v].lazy.Y)*(tr-tm)/2;
  T[v].lazy = {0, 0};
}

void upd(int v, int tl, int tr, int l, int r, int a, int q) {
  if (tr < l || r < tl) return;
  if (l <= tl && tr <= r) {
    pll seq = {a + (tl-l)*q, q};
    T[v].s += (2*seq.X + (tr-tl)*q)*(tr-tl+1)/2;
    T[v].lazy = T[v].lazy + seq;
    return;
  }
  push(v, tl, tr);
  int tm = (tl+tr)/2;
  upd(2*v, tl, tm, l, r, a, q);
  upd(2*v+1, tm+1, tr, l, r, a, q);
  T[v].s = T[2*v].s + T[2*v+1].s;
}

ll query(int v, int tl, int tr, int l, int r) {
  if (tr < l || r < tl) return 0;
  if (l <= tl && tr <= r) return T[v].s;
  int tm = (tl+tr)/2;
  push(v, tl, tr);
  ll res = query(2*v, tl, tm, l, r) + 
           query(2*v+1, tm+1, tr, l, r);
  T[v].s = T[2*v].s + T[2*v+1].s;
  return res;
}

void new_sig(int i, int s, int a, int n) {
  int l = max(0, i-s/a), r = i-1;
  if (i != 0)
    upd(1, 0, n-1, l, r, s-(i-l)*a, a);
  l = i, r = min(n-1, i+s/a);
  upd(1, 0, n-1, l, r, s, -a);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, q; cin >> n >> q;
  vector<ii> src(n);
  while (q--) {
    char c; cin >> c;
    if (c == 'P') {
      int i, s, a; cin >> i >> s >> a; --i;
      src[i] = {s, a};
      new_sig(i, s, a, n);
    }
    else if (c == 'U') {
      int i; cin >> i; --i;
      int s = src[i].X, a = src[i].Y;
      int l = max(0, i-s/a), r = i-1;
      if (i != 0)
        upd(1, 0, n-1, l, r, (i-l)*a-s, -a);
      l = i, r = min(n-1, i+s/a);
      upd(1, 0, n-1, l, r, -s, a);
    }
    else {
      int l, r; cin >> l >> r;
      cout << query(1, 0, n-1, l-1, r-1)/(r-l+1) << '\n';
    }
  }
}
