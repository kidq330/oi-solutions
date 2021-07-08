// Treść: Definiujemy grę dla dwóch graczy, w której dana plansza 1xm
// oraz 3 rodzaje pasków o długościach c1, c2 i c3. Ruch polega na położeniu
// jednego paska na planszy, przy czym kładzie się tak, aby nie przykryć
// żadnego wcześniej położonego paska. Pasek o długości c musi przykrywać
// pola i, i+1, i+2... i+c-1 dla pewnego 1 <= i <= m wybranego przez gracza.
// Dwoje graczy wykonuje ruchy jeden po drugim, przegrywa ten, który nie może już
// wykonać ruchu.
// Dane rozmiary pasków, oraz p zapytań rodzaju: czy pierwszy gracz ma
// strategię wygrywającą dla planszy o rozmiarze 1xm?

// Rozwiązanie: użyjemy programowania dynamicznego oraz kilku konceptów
// nt. teorii gier, np. nimbery oraz Tw. Sprague'a-Grundy'ego.
// Niech dp[i] będzie nimberem dla pustej planszy o rozmiarze 1xi.
// Widzimy że położenie na planszy jakiegokolwiek paska dzieli ją
// na dwie mniejsze plansze o różnych rozmiarach. Nasza gra dzieli
// się w ten sposób na dwie <niezależne> gry o mniejszych rozmiarach,
// których nimbery możemy policzyć rekurencyjnie. Mając nimbery wszystkich
// stanów do których możemy dojść przez każdy możliwy ruch możemy policzyć
// ich funkcję mex(), która będzie wartością nimbera obecnego stanu.

// Obsługiwanie zapytań polega jedynie na stwierdzeniu czy wartość
// dp[m] == 0

// Złożoność: O(n^2logn), gdzie n jest maksymalnym rozmiarem tablicy.

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  const int n = 1000;
  array<int, 3> c;
  int m; cin >> c[0] >> c[1] >> c[2] >> m;
  vector<int> dp(n+1);
  for (int l = 1; l <= n; ++l) {
    set<int> S;
    for (auto col : c) {
      for (int i = 0; i+col-1 < l; ++i) {
        S.insert(dp[i] ^ dp[l-col-i]);
      }
    }
    int &mex = dp[l];
    for (auto it : S) {
      if (it == mex) ++mex;
      else break;
    }
  }

  while (m--) {
    int p; cin >> p;
    if (dp[p] == 0) {
      cout << 2 << '\n';
    }
    else {
      cout << 1 << '\n';
    }
  }
}