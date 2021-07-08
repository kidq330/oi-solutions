#include <bits/stdc++.h>
using namespace std;

const int seg = 1 << 19;

vector<bitset<4>> T(seg);
vector<array<int,2>> V;

// ja pierdole
void merge_(int v, int tm) {
  array<bool, 4> c = {V[tm][1] <= V[tm+1][1],
                      V[tm][1] <= V[tm+1][0],
                      V[tm][0] <= V[tm+1][1],
                      V[tm][0] <= V[tm+1][0]};
  T[v][0] = (T[2*v][0] && ((c[0] && T[2*v+1][0]) || (c[1] && T[2*v+1][2])))
         || (T[2*v][1] && ((c[2] && T[2*v+1][0]) || (c[3] && T[2*v+1][2])));
  T[v][1] = (T[2*v][0] && ((c[0] && T[2*v+1][1]) || (c[1] && T[2*v+1][3])))
         || (T[2*v][1] && ((c[2] && T[2*v+1][1]) || (c[3] && T[2*v+1][3])));
  T[v][2] = (T[2*v][2] && ((c[0] && T[2*v+1][0]) || (c[1] && T[2*v+1][2])))
         || (T[2*v][3] && ((c[2] && T[2*v+1][0]) || (c[3] && T[2*v+1][2])));
  T[v][3] = (T[2*v][2] && ((c[0] && T[2*v+1][1]) || (c[1] && T[2*v+1][3])))
         || (T[2*v][3] && ((c[2] && T[2*v+1][1]) || (c[3] && T[2*v+1][3])));
}

void build(int v, int tl, int tr) {
  if (tl == tr) {
    T[v] = 13;
    return;
  }
  int tm = (tl + tr)/2;
  build(2*v, tl, tm);
  build(2*v+1, tm+1, tr);
  merge_(v, tm);
}

void upd(int v, int tl, int tr, int idx) {
  if (tl == tr) return;
  int tm = (tl + tr)/2;
  if (idx <= tm)
    upd(2*v, tl, tm, idx);
  else
    upd(2*v+1, tm+1, tr, idx);
  merge_(v, tm);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n; cin >> n;
  V.resize(n);
  for (auto &x : V) {
    cin >> x[0] >> x[1];
    if (x[0] > x[1])
      swap(x[0], x[1]);
  }
  
  build(1, 0, n-1);

  int q; cin >> q;
  while (q--) {
    int a, b; cin >> a >> b; --a, --b;
    auto aux = V[a];
    V[a] = V[b];
    upd(1, 0, n-1, a); 
    V[b] = aux;
    upd(1, 0, n-1, b);
    cout << (T[1].any() ? "TAK" : "NIE") << '\n';
  }
}

// 4
// 44 87
// 13 66
// 9 86
// 42 86
// 3
// 1 3
// 2 4
// 1 1