#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1e6;
int nxt[MAXN+1];
bool Bs[MAXN+1], del[MAXN+1];
queue<long long> bought;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int m; cin >> m;
  for (int i = 0; i < m; ++i) {
    int a; cin >> a;
    Bs[a] = true;
  }

  int n; long long t = 0; cin >> n;
  while (n--) {
    int a; cin >> a;
    auto tx = t;
    if (!nxt[a])
      nxt[a] = a;
    for (int &i = nxt[a]; tx < t+a && i <= MAXN; i += a) {
      tx += !del[i];
      if (Bs[i]) {
        bought.push(tx);
      }
      Bs[i] = false;
      del[i] = true;
    }
    t += a;
  }
  cout << bought.size() << '\n';
  while (!bought.empty()) {
    cout << bought.front() << '\n';
    bought.pop();
  }
}