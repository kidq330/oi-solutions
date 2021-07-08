// Treść: Dana gra na planszy 1xm oraz n pionków. Ruch polega na przesunięciu
// pionka w prawo na pierwszą pustą pozycję. Wygrywa gracz, który pierwszy
// przejdzie jakimkolwiek pionkiem na pozycję m. Policzyć dla ilu ruchów po początkowym
// stanie gry następuje stan przegrywający, tzn. taki gdzie jeśli obaj gracze grają
// optymalnie, pierwszy zawsze przegrywa.

// Rozwiązanie: Zauważmy, że stan, gdzie pole m-1 jest niepuste jest zawsze przegrywający.
// Będziemy próbować znaleźć równoważność z pewną wariacją gry Nim, dokładnie
// Nim na schodach, tzn. na m schodach rozstawione stosy kamieni, ruch polega
// na przeniesieniu dowolnej, niezerowej ilości kamieni z jednego stosu na niższy schód.
// Z ostatniego schoda nie można zabierać kamieni. Przegrywa gracz, który nie może wykonać ruchu.
// Zauważmy, że kamienie parzyste nie grają w tej wersji istotnej roli. Załóżmy, że
// gracz jest w pozycji przegrywającej, i postanawia przenieść x kamieni na schód nieparzysty.
// Drugi gracz może przenieść kamienie z powrotem na schód parzysty, wracając do stanu sprzed
// chwili. Takie przenoszenie można powtarzać dopóki kamienie nie znajdą się na
// ostatnim schodzie. Ilość kamieni na parzystych schodach nie wpływa więc na rozgrywkę.
// Dodatkowo przeniesienie kamieni z nieparzystego schoda na parzysty będzie równoważne
// z pozbyciem się go. Gra jest zatem równoważna tradycyjnemu nimowi na stosach
// znajdujących się na pozycjach nieparzystych, który można rozwiązać wykorzystując
// Tw. Sprague'a-Grundy'ego.

// Zauważmy, że pozycję m-2 w naszej oryginalnej grze możemy traktować jako
// ostatni schód, a kilka pionków obok siebie jako stos kilku kamieni.
// Gra jest zatem równoważna do Nim na schodach, który umiemy szybko rozwiązać.
// Wyjątkiem będą pionki na pozycji m-1.
// Wystarczy teraz policzyć, jaka będzie parzystość każdego stosu względem m-2,
// jednak trzeba uważać na pozycje pionków. Pozycja na planszy nie jest równoważna
// pozycji na schodach. Teraz wystarczy policzyć xor wszystkich stosów na schodach
// o parzystości różnej od m-2, a następnie dla każdego stosu policzyć jak zmieni
// się ten xor po wykonaniu jednego ruchu, licząc przy tym, które pozycje będą przegrywające.

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int m, n; cin >> m >> n;
  vector<pair<int, int>> stacks;
  pair<int, int> st = {1, 0}; 
  cin >> st.second;
  for (int i = 1; i < n; ++i) {
    int nxt; cin >> nxt;
    if (st.second+1 == nxt) {
      ++st.first;
      ++st.second;
    }
    else {
      stacks.push_back(st);
      st = {1, nxt};
    }
  }
  stacks.push_back(st);
  if (stacks.back().second == m-1) {
    cout << stacks.back().first;
    return 0;
  }
  if (st.second != m-2) stacks.push_back({0, m-2});

  int sum = 0, x = 0;
  for (int i = stacks.size()-1; i >= 0; --i) {
    auto &s = stacks[i];
    // compute stair index
    s.second += sum;
    sum += s.first;
    // when do we take this stack into account
    if (s.second%2 != m%2) {
      x ^= s.first;
    }
  }
  int ans = 0;
  for (int i = stacks.size()-2; i >= 0; --i) {
    auto &s = stacks[i];
    if (s.second%2 != m%2) {
      x ^= s.first;
      for (int j = 0; j < s.first; ++j)
        ans += (x ^ j) == 0;
      x ^= s.first;
    }
    else {
      int next_cnt = (stacks[i+1].second == s.second+1 ? stacks[i+1].first : 0);
      x ^= next_cnt;
      for (int j = 1; j <= s.first; ++j)
        ans += (x ^ (next_cnt + j)) == 0;
      x ^= next_cnt;
    }
  }

  cout << ans;
}

// 13 6
// 1 4 5 8 9 10