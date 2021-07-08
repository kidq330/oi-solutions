// Treść: Dane drzewo na n wierzchołkach i ciąg g liczb (m_1, m_2, ... m_g). Z każdego liścia
// do drzewa wchodzić będzie grupa m_i mrówek, odwiedzając całe drzewo spacerem BFS.
// Przy każdym rozwidleniu ścieżki na x gałęzi grupa dzieli się na równoliczne grupy
// o rozmiarze floor(m_i/x). W drzewie wyróżniona jedna krawędź, policzyć ile
// przejdzie przez nią grup rozmiaru dokładnie k.

// Rozwiązanie: Należy najpierw podzielić drzewo na dwa poddrzewa, których
// korzeniami będą końce wyróżnionej krawędzi. Rozwiązanie dla obu drzew będzie symetryczne.
// Będziemy chcieli policzyć dla każdej ścieżki z liścia do korzenia 
// ciąg (a_1, a_2, ... a_r), oznaczający przez jakie liczby dzielimy grupy 
// mrówek idące tą ścieżką.
// Zauważmy, że nie obchodzą nas ścieżki nie idące do korzenia.
// Ponieważ obliczanie całego ciągu nie byłoby wydajne, a dzielenie całkowite jest
// przechodnie, tj. floor(floor(a/b))/c == floor(a/(b*c)), wystarczy policzyć
// iloczyn ciągu.
// Liczyć iloczyny dla poszczególnych liści można w następujący sposób:
// Zaczynamy algorytm DFS z korzenia i przy każdym wywołaniu rekurencyjnym
// mnożymy iloczyn przez stopień wierzchołka - 1. Iloczyn łatwo może przekroczyć
// zakres inta, jednak wtedy wiemy, że jakakolwiek grupa podzielona przez ten iloczyn
// nie będzie równa k, więc można go wyrzucić.
// DFS wywołany na liściu dodaje obliczony iloczyn do vectora, który po skończeniu
// całego spaceru sortujemy. Ostatnia faza zadania jest symetryczna.
// Można posortować liczności grup i dla każdego iloczynu znaleźć wyszukiwaniem
// binarnym ile jest grup które są równe k po podzieleniu przez ten iloczyn, 
// lub posortować iloczyny, a następnie znaleźć (również wyszukiwaniem binarnym)
// dla każdej grupy ile jest iloczynów, które dzielą ją dokładnie na k.
// Poniższe rozwiązanie korzysta z drugiego sposobu.

// Złożoność: O((n+g)logn)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
constexpr int P = 1e9 + 7;

vector<vector<int>> adj;
vector<int> p, prod;

void dfs(int v, int pr) {
  if (adj[v].size() == 1) {
    prod.push_back(pr);
    return;
  }
  ll prx = (ll)pr*(adj[v].size()-1);
  if (prx > P) return;
  pr = prx;
  for (auto x : adj[v]) {
    if (x == p[v]) continue;
    p[x] = v;
    dfs(x, pr);
  }
}


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, g, k; cin >> n >> g >> k;
  vector<int> teams(g);
  adj.resize(n);
  p.resize(n);
  for (auto &x : teams) cin >> x;
  int r1, r2;
  cin >> r1 >> r2;
  --r1, --r2;
  adj[r1].push_back(r2);
  adj[r2].push_back(r1);
  p[r1] = r2;
  p[r2] = r1;
  for (int i = 2; i < n; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(r1, 1); dfs(r2, 1);
  sort(prod.begin(), prod.end());

  ll sum = 0;
  for (auto x : teams) {
    int l = -1, r = prod.size();
    while (l+1 < r) {
      int mid = (l+r)/2;
      if (x/prod[mid] < k)
        r = mid;
      else 
        l = mid;
    }
    int rx = r; l = -1, r = prod.size();
    while (l+1 < r) {
      int mid = (l+r)/2;
      if (x/prod[mid] <= k)
        r = mid;
      else 
        l = mid;
    }
    sum += rx - r;
  }

  cout << (ll)k*sum;
}