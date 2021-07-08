// Treść: Dany pusty ciąg (v_n) = (0, 0, ... 0) długości n i k operacji.
// Operacja składa się z trójki liczb (a, l, d), co oznacza zwiększenie o 1
// pozycji v_a, v_(a+d), v_(a+2d), ... v_(a+(l-1)d).
// Wypisać ciąg (v_n) po k operacjach

// Rozwiązanie: Wykorzystamy trik dzielenia po pierwiastku.
// Operacje w których d >= sqrt(n) będziemy wykonywać normalnie, ponieważ wystarczy
// zaktualizować n/d = O(n/(sqrt(n))) = O(sqrt(n)) pozycji.
// Operacje w których d < sqrt(n) zachowamy w tablicy q[d]
// q[d] będzie trzymać parę (a, l) każdej operacji o skoku wartości d
// Sumarycznie tablica q będzie wymagała O(sqrt(n) + k) pamięci

// Dalsza część rozwiązania korzysta z triku rozwiązującego poniższy problem:
// Dany ciąg pusty (v_n) i k operacji "zwiększ przedział [l;r] o 1"
// Definiujemy nowy ciąg (s_n), i dla każdej operacji (l, r) wykonujemy:
// s[l] += 1, s[r+1] -= 1         Trik ten nazywa się często "malowaniem przedziałów"
// Teraz iterujemy po s, trzymając jednocześnie sumę prefiksową
// sum += s[i], v[i] += sum
// Ciąg v[] jest wynikiem tych k operacji.

// Wracając do oryginalnego problemu: Będziemy wykonywać poniższy algorytm
// dla każdego d < sqrt(n):
// Definiujemy pusty ciąg (s_n)
// dla każdej pary (a, l) w q[d]:
//  s[a] += 1
//  s[a + l*d] -= 1
// Teraz musimy przejść po każdym indeksie i < n, skacząc zawsze o d
// Zaczynamy więc najpierw z a = 0 skacząc po indeksach 0, d, 2d, 3d ... floor(n/d)*d
// Następnie 1, 1+d, 1+2d ... I tak dalej.
// Podczas tej iteracji w nietradycyjnej kolejności korzystamy z tablicy s podobnie
// jak w zadaniu powyżej, trzymając dotychczasową sumę i dodając ją do ciągu v.
// Po wykonaniu algorytmu dla każdego 1 <= d < sqrt(n) nasz ciąg v będzie gotowy.

// Złożoność: O((n + k)sqrt(n))
// Złożoność pamięciowa: O(n + k)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, k; cin >> n >> k;
  const int B = sqrt(n);
  vector<int> v(n);
  vector<vector<ii>> q(B+1);
  while (k--) {
    int a, l, d; cin >> a >> l >> d; --a;
    if (d >= B) {
      for (int i = a; i < n && l; i += d, --l) {
        ++v[i];
      }
    }
    else {
      q[d].push_back({a, l});
    }
  }

  for (int d = 1; d < B; ++d) {
    vector<int> s(n);
    for (auto p : q[d]) {
      ++s[p.first];
      if (p.first+p.second*d < n)
        --s[p.first+p.second*d];
    }
    for (int a = 0; a < d; ++a) {
      int sum = 0;
      for (int i = a; i < n; i += d) {
        sum += s[i];
        v[i] += sum;
      }
    }
  }

  for (auto x : v)
    cout << x << ' ';
}
