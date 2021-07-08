// Treść: Dany słownik D, w nim n słów różnych długości. Znaleźć długość najkrótszego
// słowa takiego że występuje w nim dokładnie m słów z D. W szczególności słowo
// s \in D może pojawić się kilka razy lub wcale. Można założyć że nie ma dwóch
// takich słów w D, że jedno jest podsłowem drugiego.

// n <= 200, m <= 1e9, (suma długości słow w D) = S <= 1e5

// Rozwiązanie: Zadanie można modelować za pomocą pełnego grafu skierowanego ważonego,
// tj. Wszystkie słowa są ze sobą połączone, a koszt przejścia ze słowa s do słowa t
// można zdefiniować jako |t| - |f(s, t)|, gdzie f(s, t) jest najdłuższym słowem,
// które jest zarówno sufiksem s i prefiksem t.
// Wtedy problem sprowadza się do znalezienia spaceru po m wierzchołkach o minimalnej
// sumie wag. Rozwiązanie dzieli się na fazę obliczenia wag, i długości spaceru.

// Faza 1: Obliczanie |f(s, t)| dla każdej pary (s, t) \in D^2
// Do trzymania słów w pamięci użyjemy techniki hashowania.
// Słowo możemy opisać jako wielomian którego współczynniki są literami słowa.
// Technika ta jest niedeterministyczna, tzn. istnieją sytuacje (nazywane kolizjami) 
// w których hashe dwóch różnych słów mają tę samą wartość. Prawdopodobieństwo
// wystąpienia kolizji jest w praktyce bardzo małe.
// Hashowanie pozwala również na sprawdzenie czy dwa słowa są równe w O(1),
// normalnie musielibyśmy iterować po obu słowach i sprawdzać czy są równe literka po literce.

// Po obliczeniu hashów każdego sufiksu i prefiksu każdego słowa z D, możemy
// przeiterować po wszystkich parach słów i sprawdzić brutalnie gdzie najbardziej
// na siebie nachodzą. Na oko zajmie to O(S*n^2) czasu, jednak jedyne co robimy
// to iterujemy po każdym słowie n razy, a więc tak jakbyśmy iterowali n razy po całym
// słowniku, czyli O(Sn)

// Faza 2: Liczenie najkrótszego spaceru po m wierzchołkach
// Zdefiniujmy M[k][u][v] - długość najkrótszego spaceru od u do v po k wierzchołkach.
// Widzimy że zachodzi relacja: 
// M[k][u][v] = min(M[k-1][u][w]+M[1][w][v], M[1][u][w]+M[k-1][w][v]), 1<=w<=n.
// Ponieważ możemy najpierw przejść po k-1 wierzchołkach do wierzchołka pośredniego w,
// a następnie z w do v. Drugi przypadek jest symetryczny.

// Jeżeli k jest parzyste, zachodzi też relacja:
// M[k][u][v] = min(M[k/2][u][w]+M[k/2][w][v]), 1<=w<=n

// Policzenie M za pomocą pierwszej relacji wykonamy w czasie O(m*n^3)
// Można skorzystać z drugiej relacji i zaprojektować algorytm bardzo zbliżony
// do algorytmu potęgowania macierzy.

// Złożoność: O(Sn + logm*n^3)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
constexpr int b = 31, p = 1e9+7;
constexpr ll INF = 1e18;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m; cin >> n >> m;
  // suf[i][j] - hash of j-th suffix of i-th string
  vector<vector<int>> pref(n), suf(n);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    const int len = s.size();
    pref[i].resize(len+1);
    suf[i].resize(len+1);
    
    suf[i].back() = 0;
    for (int j = len-1; j >= 0; --j) {
      suf[i][j] = ((ll)suf[i][j+1]*b%p + (s[j]-'a'))%p;
    }
    int bn = 1;
    for (int j = 1; j <= len; ++j) {
      pref[i][j] = ((ll)(s[j-1]-'a')*bn%p + pref[i][j-1])%p;
      bn = (ll)bn*b%p;
    }
  }

  vector<vector<ll>> M(n, vector<ll>(n, INF));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      const int l1 = pref[i].size()-1, l2 = pref[j].size()-1;
      for (int k = (i == j ? 1 : max(0, l1-l2)); k <= l1; ++k) {
        if (suf[i][k] == pref[j][l1-k]) {
          M[i][j] = min(M[i][j], (ll)(l2-l1+k));
        }
      }
    }
  }

  vector<vector<ll>> M1(n, vector<ll>(n, INF)), M2(n);
  for (int i = 0; i < n; ++i)
    M1[i][i] = 0;

  --m;
  while (m) {
    fill(M2.begin(), M2.end(), vector<ll>(n, INF));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          if (m%2)
            M2[i][j] = min({M2[i][j], M[i][k]+M1[k][j], M1[i][k]+M[k][j]});
          else
            M2[i][j] = min(M2[i][j], M[i][k]+M[k][j]);
        }
      }
    }
    if (m%2) {
      swap(M1, M2);
      --m;
    }
    else {
      m >>= 1;
      swap(M, M2);
    }
  }

  ll res = INF;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      res = min(res, (ll)pref[i].size()-1+M1[i][j]);
    }
  }
  cout << res;
}