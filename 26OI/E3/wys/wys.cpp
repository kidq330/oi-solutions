// Treść: Dany ciąg liczb całkowitych dodatnich S : |S| = n <= 3e5
// Zaprojektować strukturę umożliwiającą poniższe operacje:
// 1: B x y - dodaj y do każdego elementu >= x
// 2: K x y - odejmij y od każdego elementu <= x
// 3: Z - Rozważmy zbiór funkcji F, które do każdego elementu z S dodają
//        osobną wartość ze zbioru {1, 2 ... n}, np. f(S) = (S_1+1, S_2+2 ... S_n+n). 
//        Policzyć ile jest elementów S_i takich że istnieje funkcja f w F
//        w której wynikowym ciągu f(S)_i jest największym elementem.
// Rozwiązanie: 

// Obserwacja 1: jeśli ciąg jest posortowany niemalejąco, operacje 1 i 2
// nie naruszają kolejności. Można zatem posortować ciąg i zbudować na nim drzewo przedziałowe.
// Pierwszy element >= x znajdujemy wyszukiwaniem binarnym pytając o wartość
// i-tego elementu przy każdej iteracji w sumarycznym czasie O(log^2n).
// Następnie wykonujemy operację zwiększenia o y znalezionego sufiksu. Analogicznie operacja 2

// Obserwacja 2: aby zmaksymalizować szansę na zmaksymalizowanie elementu S_i
// wskutek transformacji w operacji 3, można przyjąć f(S) = (S_1+n-1, S_2+n-2, ... S_i+n, ... S_n+1)
// Znalezienie największego elementu w tym ciągu jest nietrywialne, dlatego
// drzewo przedziałowe zbudujemy na ciągu dla którego została już zastosowana powyższa funkcja,
// i przy okazji obliczymy maksymalne wartości dla przedziałów bazowych.

// Do obliczenia operacji 3 również można wykorzystać wyszukiwanie binarne
// i znaleźć pierwszy element, który może stać się maximum.

// Złożoność: O(nlogn + qlog^2n)
// Możliwe było osiągnięcie złożoności O(qlogn) wykorzystując technikę schodzenia po drzewie

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
constexpr int Tsize = 1 << 21;
constexpr ll INF = 1e18;

vector<pll> T(Tsize);
vector<ll> U(Tsize);

void build(int v, int tl, int tr, vector<int> const&vals) {
  if (tl == tr) {
    T[v] = {vals[tl]+vals.size()-1-tl, tl};
    return;
  }
  int tm = (tl+tr)/2;
  build(2*v, tl, tm, vals);
  build(2*v+1, tm+1, tr, vals);
  if (T[2*v].first >= T[2*v+1].first) {
    T[v] = T[2*v];
  }
  else
    T[v] = T[2*v+1];
}

void push(int v) {
  auto &u = U[v];
  T[2*v].first += u;
  T[2*v+1].first += u;
  U[2*v] += u;
  U[2*v+1] += u;
  u = 0;
}

void upd(int v, int tl, int tr, int l, int r, ll val) {
  if (tr < l || r < tl) {
    return;
  }
  if (l <= tl && tr <= r) {
    T[v].first += val;
    U[v] += val;
    return;
  }
  push(v);
  int tm = (tl+tr)/2;
  upd(2*v, tl, tm, l, r, val);
  upd(2*v+1, tm+1, tr, l, r, val);
  if (T[2*v].first >= T[2*v+1].first) {
    T[v] = T[2*v];
  }
  else
    T[v] = T[2*v+1];
}

ll query_val(int v, int tl, int tr, int a) {
  if (tl == tr) {
    return T[v].first;
  }
  int tm = (tl+tr)/2;
  push(v);
  if (a <= tm)
    return query_val(2*v, tl, tm, a);
  return query_val(2*v+1, tm+1, tr, a);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, q; cin >> n >> q;
  vector<int> v(n);
  for (auto &x : v)
    cin >> x;

  sort(v.begin(), v.end());
  build(1, 0, n-1, v);
  v.clear();

  while (q--) {
    char c; cin >> c;

    if (c == 'Z') {
      int l = -1, r = n;
      while (l+1 < r) {
        int m = (l+r)/2;
        if (query_val(1, 0, n-1, m)+m+1 >= T[1].first+(T[1].second>m)) {
          r = m;
        }
        else {
          l = m;
        }
      }
      cout << n-r << '\n';
    }
    else if (c == 'B') {
      ll x, y; cin >> x >> y;
      int l = -1, r = n;
      while (l+1 < r) {
        int m = (l+r)/2;
        if (query_val(1, 0, n-1, m)-n+m+1 >= x)
          r = m;
        else
          l = m;
      }
      if (r < n) {
        upd(1, 0, n-1, r, n-1, y);
      }
    }
    else {
      ll x, y; cin >> x >> y;
      int l = -1, r = n;
      while (l+1 < r) {
        int m = (l+r)/2;
        if (query_val(1, 0, n-1, m)-n+m+1 <= x)
          l = m;
        else
          r = m;
      }
      if (l >= 0) {
        upd(1, 0, n-1, 0, l, -y);
      }
    }
  }
}

// 6 9
// 6 6 1 3 7 3 
// K 10 4
// B 7 9
// Z
// B 1 1
// Z
// B 7 5
// B 10 4
// Z
// K 4 4

// 6 7
// 2 4 5 7 4 8 
// Z
// B 9 6
// K 5 5
// K 4 5
// B 2 2
// K 8 5
// Z

// 6 8
// 6 6 1 3 7 3 
// K 10 4
// B 7 9
// Z
// B 1 1
// Z
// B 7 5
// B 10 4
// Z