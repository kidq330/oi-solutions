#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct bit {
  vector<ll> T;
  int last = 0, n = 0, ins = 0;

  void upd(int i, ll delta) {
    for (; i < n; i |= i+1) {
      T[i] += delta;
    }
  }

  ll query(int r) {
    ll res = 0;
    for (; r >= 0; r = (r & (r+1)) - 1)
      res += T[r];
    return res;
  }
};

bit T;
ll s;

void inicjuj(int m) {
  s = 0;
  T.T.resize(m);
  T.last = 0;
  T.n = m;
}

void dodaj(int k) {
  ll delta = k - (T.query(T.last) - (T.last == 0 ? 0 : T.query(T.last-1)));
  T.upd(T.last++, delta);
  T.last *= T.last != T.n;
  s += delta;
  ++T.ins;
}

void koryguj(int i, int k) {
  s += k;
  T.upd((T.last - i + T.n) % T.n, k);
}

long long suma(int i) {
  if (i > T.ins) return s;
  const int l = (T.last - i + T.n) % T.n, r = T.last-1;
  if (l <= r) {
    return T.query(r) - (l == 0 ? 0 : T.query(l-1));
  }
  else {
    return s - (T.query(l-1) - T.query(r));
  }
}

// int main() {
//   int m, q; cin >> m >> q;
//   inicjuj(m);
//   while (q--) {
//     char c; cin >> c;
//     if (c == 'A') {
//       int k; cin >> k;
//       dodaj(k);
//     }
//     else if (c == 'U') {
//       int i, k; cin >> i >> k;
//       koryguj(i, k);
//     }
//     else {
//       int i; cin >> i;
//       cout << suma(i) << '\n';
//     }
//   }  
// }

