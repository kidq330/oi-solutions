// Treść: Dany graf nieskierowany o dwóch wagach na krawędź:
// l - długość, s - wartość.
// Cykl "dobry" definiujemy jako taki, który każdą krawędź odwiedza co najmniej raz,
// odwiedzając krawędź dodajemy jej wartość s tylko jeśli odwiedzamy ją pierwszy raz,
// ale zawsze odejmujemy długość.
// Dodatkowo cykl "dobry" musi zaczynać się w środku krawędzi, tzn.
// zaczynamy dodając wartość s i odejmując połowę długości l/2 krawędzi startowej.
// Znaleźć ciąg krawędzi tworzący cykl dobry, lub stwierdzić, że nie istnieje.
// Dodatkowo wiemy, że stopień każdego wierzchołka == 4

// Rozwiązanie: Należy najpierw zauważyć, że jeśli rozwiązania istnieją,
// to jednym z nich będzie jakikolwiek cykl Eulera. Dowód jest analogiczny,
// do dowodu na istnienie cyklu Eulera. Do każdego wierzchołka wejdziemy
// tyle razy, ile z niego wyjdziemy, a odwiedzenie jakiejkolwiek krawędzi dwukrotnie
// dodaje do trasy pewien prosty cykl, który w jakiś sposób zmniejszy sumę.

// Zastanówmy się, kiedy rozwiązanie nie istnieje. Jest tak na pewno wtedy,
// kiedy suma wszystkich wartości - suma wszystkich długości jest ujemna, 
// ponieważ każdy cykl dojdzie do momentu, w którym odwiedzi wszystkie krawędzie.
// Okazuje się, że jest to wystarczający warunek. Załóżmy bowiem, że suma jest dodatnia.
// Cykl sprowadza się do ciągu pewnych wartości (s1, -l1/2, -l2/2, s2, -l2/2, -l3/2, s3 ..., s2n, -l2n/2, -l1/2)
// Zauważmy, że możemy dowolnie wybierać początek tego ciągu, jest to równoważne
// ze zmienianiem krawędzi startowej. Musimy tak przesunąć ciąg, aby wszystkie
// jego sumy prefiksowe były dodatnie. Wystarczy zatem znaleźć prefiks o najmniejszej
// sumie, i jako punkt startowy wybrać kolejną pozycję.
// Dowód pozostawiam czytelnikowi.

// Złożoność: O(|V| + |E|)

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
struct quad {
  int u, v, l, s;
  quad(int _u, int _v, int _l, int _s) : u(_u), v(_v), l(_l), s(_s) {}
  quad(){}
};

vector<vector<ii>> adj;
vector<bool> delet;
vector<quad> edg;

void euler(int v, vector<int> &path) {
  for (auto p : adj[v]) {
    if (delet[p.second])
      continue;
    delet[p.second] = true;
    euler(p.first, path);
    path.push_back(p.second);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n; cin >> n;
  adj.resize(n);
  edg.resize(n << 1);
  delet.resize(n << 1);
  for (int i = 0; i < (n << 1); ++i) {
    int a, b, l, s; cin >> a >> b >> l >> s; --a, --b;
    adj[a].push_back({b, i});
    adj[b].push_back({a, i});
    edg[i] = quad(a, b, l, s);
  }

  vector<int> path; path.reserve(n << 1);
  euler(0, path);


  ii min_pref = {1<<30, -1};
  int s = 0;
  for (int i = 0; i < (n << 1); ++i) {
    auto &e = edg[path[i]];
    min_pref = min(min_pref, {s-e.l/2, i});
    s += e.s - e.l;
  }

  if (s < 0) {
    cout << "NIE";
    return 0;
  }

  int st = min_pref.second, nxt = st+1 == n << 1 ? 0 : st+1,
      stv = (edg[path[st]].u == edg[path[nxt]].u || edg[path[st]].u == edg[path[nxt]].v) ?
             edg[path[st]].u : edg[path[st]].v;



  cout << "TAK\n" << (n << 1) << '\n' << path[st]+1 << ' ' << stv+1 << '\n';
  for (int i = 1; i < (n << 1); ++i) {
    cout << path[(i+st)%(n << 1)]+1 << '\n';
  }
}