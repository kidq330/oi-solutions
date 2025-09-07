#include <bits/stdc++.h>
using namespace std;
const int N = 4;
typedef array<int, N> arr;

vector<int> d(6250000);

void insert(const int &x, const int &st, queue<int> &Q) {
  if (d[x] == 0) {
    d[x] = d[st] + 1;
    Q.push(x);
  }
}

int factor(int x, arr &st) {
  int s = 0;
  for (int i = 0; i < N; ++i) {
    st[i] = x % 50;
    s += st[i];
    x /= 50;
  }
  return s;
}

int bfs(const int &n, arr const &cont, arr const &res) {
  queue<int> Q;
  arr pow = {1, 50, 2500, 125000};
  int cont_50 = 0, res_50 = 0, res_s = 0;

  for (int i = 0; i < n; ++i) {
    cont_50 += cont[i] * pow[i];
    res_50 += res[i] * pow[i];
    res_s += res[i];
  }
  d[cont_50] = 1;

  d[cont_50] = 1;
  Q.push(cont_50);

  while (!Q.empty()) {
    auto st_50 = Q.front();
    Q.pop();
    if (st_50 == res_50)
      return d[st_50] - 1;

    arr st;
    int s = factor(st_50, st);

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        // op1.
        // i -> j
        if (st[i] + st[j] <= cont[j]) {
          insert(st_50 + st[i] * (pow[j] - pow[i]), st_50, Q);
        }
        // j -> i
        if (st[i] + st[j] <= cont[i]) {
          insert(st_50 + st[j] * (pow[i] - pow[j]), st_50, Q);
        }
        // op2.
        // fill i
        if (st[j] >= cont[i] - st[i] && st[i] != cont[i]) {
          insert(st_50 - (pow[j] - pow[i]) * (cont[i] - st[i]), st_50, Q);
        }
        // fill j
        if (st[i] >= cont[j] - st[j] && st[j] != cont[j]) {
          insert(st_50 + (pow[j] - pow[i]) * (cont[j] - st[j]), st_50, Q);
        }
      }
      // op3.
      if (s - st[i] >= res_s) {
        insert(st_50 - st[i] * pow[i], st_50, Q);
      }
    }
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  arr cont = {0, 0, 0, 0}, res = cont;
  for (int i = 0; i < n; ++i)
    cin >> cont[i];
  for (int i = 0; i < n; ++i)
    cin >> res[i];

  int ans = bfs(n, cont, res);
  if (ans == -1)
    cout << "NIE";
  else
    cout << ans;
}

// 3
// 5 7 7
// 0 0 6