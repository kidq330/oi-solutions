// Treść: Dane dwa zbiory punktów o rozmiarze n. Punkt ze zbioru 1
// można połączyć z punktem ze zbioru 2 jeśli jego współrzędna x jest mniejsza,
// a współrzędna y większa. Obliczyć wartości funkcji różnowartościowej f : S1 -> S2 która 
// każdemu punktowi z S1 przypisuje własny punkt ze zbioru S2, minimalizując
// przy tym sumę odległości wszystkich par według metryki Manhattan.
// Jest gwarantowane, że poprawne sparowanie zawsze istnieje.

// Rozwiązanie: Należy zauważyć, że każde poprawne sparowanie będzie
// mieć taką samą sumę odległości. Wystarczy więc znaleźć to sparowanie.
// Użyjemy techniki zamiatania bardzo popularnej w geometrii obliczeniowej.
// Najpierw posortujemy wszystkie punkty według x-ów. Następnie będziemy
// iterować po nich według tej kolejności, wrzucając punkty z pierwszego
// zbioru do struktury Set, sortując je jednocześnie po y-ach.
// Jeśli podczas zamiatania napotkamy punkt z drugiego zbioru, możemy
// wyszukać binarnie w Secie punkt z pierwszego zbioru o najmniejszym y,
// sparować je, i usunąć ten punkt z Seta, ponieważ nie będzie można użyć
// go drugi raz. Jeśli wiemy, że rozwiązanie istnieje, 
// algorytm w którym zawsze wybieramy punkt o najmniejszym y okazuje się 
// być poprawnym algorytmem zachłannym, dowód pozostawiam czytelnikowi.

// Złożoność: O(nlogn)

#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second 
typedef pair<int, int> ii;

struct point {
  ii P;
  int id;
  point() {}
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n; cin >> n;
  vector<point> pts(n << 1);
  vector<int> link(n << 1);
  for (int i = 0; i < (n << 1); ++i) {
    cin >> pts[i].P.X >> pts[i].P.Y;
    pts[i].id = i;
  }
  sort(pts.begin(), pts.end(), [](point &A, point &B){return A.P.X < B.P.X || (A.P.X == B.P.X && A.P.Y > B.P.Y);});
  set<ii> S;
  const int r = 0;
  S.insert({pts[0].P.Y, pts[0].id});
  for (int i = 1; i < (n << 1); ++i) {
    if (pts[i].id < n) S.insert({pts[i].P.Y, pts[i].id});
    else {
      auto it = S.lower_bound({pts[i].P.Y, -1});
      link[(*it).Y] = i;
      S.erase(it);
    }
  }

  long long cost = 0;
  for (int i = 0; i < (n << 1); ++i) {
    if (pts[i].id < n) {
      cost += abs(pts[i].P.X - pts[link[pts[i].id]].P.X) 
            + abs(pts[i].P.Y - pts[link[pts[i].id]].P.Y);
    }
  }
  cout << cost << '\n';
  for (int i = 0; i < n; ++i) {
    cout << i+1 << ' ' << pts[link[i]].id+1-n << '\n';
  }
}