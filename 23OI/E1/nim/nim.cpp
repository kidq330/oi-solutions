// Treść: Dana gra Nim na n stosach z modyfikacją, oraz liczba d. Gracz który nie 
// zaczyna może przed rozpoczęciem gry wybrać k stosów i zabrać z nich wszystkie
// kamienie, z tym że k musi być wielokrotnością d. Policzyć na ile sposobów
// może to zrobić, aby gracz rozpoczynający był w pozycji przegrywającej.
// n <= 5*10^5, d <= 10, wysokość pojedynczego stosu <= 10^6, suma stosów = S <= 10^7

// Rozwiązanie: Problem sprowadza się do policzenia podzbiorów ciągu z wejścia takich,
// których rozmiar jest wielokrotnością d, a xor równy xorowi całego ciągu,
// ponieważ ciąg bez rozpatrywanego podzbioru będzie miał wtedy xor = 0, czyli przegrywający.
// Użyjemy programowania dynamicznego, a konkretnie zmodyfikowanego algorytmu plecakowego.
// Oprócz tego przyda się parę oszacowań na temat xorowanych wartości.
// 1. xor podzbioru nie może być większy niż 2^20 - 1. Jest tak dlatego, że
// dla podanych wartości (do 10^6) największy zapalony w reprezentacji binarnej
// jest bit 19. Da się skonstruować taki ciąg, którego pewien podzbiór będzie
// miał zapalone wszystkie bity aż do 19, osiągając wartość 2^20 - 1.
// Większej nie może mieć, ponieważ pewien element musiałby mieć zapalony co najmniej
// 20 bit, na co nie pozwalają limity w zadaniu.
// 2. Dany posortowany niemalejąco ciąg (a1, a2, ... an) i 2^(k-1) <= an < 2^k. 
// Wiemy że xor całego ciągu X < 2^k z faktu 1. 
// 2^(k-1) <= an < 2^k \*2
// 2^k <= 2an
// X < 2^k <= 2an
// Indukcyjnie wynika z tego, że dla każdego prefiksu tak posortowanego ciągu
// żaden xor nie przekroczy podwojonej wartości największego elementu.

// dp[n][r][x] - ilość podzbiorów n-tego prefiksu podanego ciągu o liczbie elementów = r mod d
// oraz xorze równym x. 
// Odpowiedź do zadania znajdzie się w komórce dp[n][0][X], gdzie X jest xorem całego ciągu.
// Zachodzi relacja rekurencyjna:
// dp[n][r][x] = dp[n-1][r][x] + dp[n-1][r-1][x ^ a_n]
// Jest to relacja niemal identyczna do tej z problemu plecakowego. Możemy od razu
// zastosować optymalizację pamięci wyrzucając wymiar odpowiedzialny za prefiks.
// Należy przy tym uważać aby nie aktualizować żadnej komórki więcej niż raz
// przy jednym przejściu i uważać na cykliczność wymiaru odpowiedzialnego za wartość mod d
// Otrzymujemy tablicę dp[r][x], z faktu 1 wiemy że wymiar [x] możemy zainicjalizować do rozmiaru 2^20.
// Całkowity rozmiar wyniesie zatem int*d*X = 4*10*2^20 ~ 42MB < 64MB

// Pozostaje problem szybkiego liczenia tablicy dp.
// Z faktu 2 można zauważyć, że jeśli posortujemy ciąg, to przy liczeniu i-tego 
// elementu wystarczy iterować po możliwych wartościach xora do min(2*a_i, 2^20)
// Liczba operacji wyniesie zatem d*2a_1 + d*2a_2 ... + d*2a_n = d*2S = 10*2*10^7 = 2*10^8
// W treści zaznaczono, że nie można wybrać całego zbioru, co może się stać jeśli n = 0 mod d

// Złożoność: O(nlogn + d*X + d*S)

#include <bits/stdc++.h>
using namespace std;

constexpr int p = 1e9+7, p20 = 1 << 20;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, d, mx = 0, ax = 0; cin >> n >> d;
  vector<int> stacks(n);
  for (auto &x : stacks) {
    cin >> x;
    mx = max(mx, x);
    ax ^= x;
  }
  int msd = 0;
  while (mx) {
    ++msd;
    mx >>= 1;
  }
  int gx = (1 << (msd+1));

  sort(stacks.begin(), stacks.end());

  vector<vector<int>> dp(d, vector<int>(1 << 20));
  dp[0][0] = 1;
  for (auto x : stacks) {
    const int r = min(2*x, p20);
    auto old1 = vector<int>(dp[d-1].begin(), dp[d-1].begin()+r);
    for (int dx = d-2; dx >= 0; --dx) {
      for (int xval = 0; xval < r; ++xval) {
        auto &dpi = dp[(dx+1)%d][xval^x];
        dpi = (dpi + dp[dx][xval]) % p;
      }
    }
    for (int xval = 0; xval < r; ++xval) {
      dp[0][xval^x] = (dp[0][xval^x] + old1[xval]) % p;
    }
  }

  cout << (dp[0][ax] - (n%d == 0) + p) % p;
}