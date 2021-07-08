#include <bits/stdc++.h>
using namespace std;

struct triple {
  int st, en, w;
  triple (int _s, int _e, int _w) : st(_s), en(_e), w(_w) {}
  triple () {}
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n; cin >> n;
  typedef pair<int, bool> ic;
  vector<ic> v(n);
  vector<triple> seg(n);

  v.reserve(1e6 + n + 5);

  for (int i = 0; i < n; ++i) {
    int a, b, w; cin >> w >> a >> b;
    v[i] = {i, 0};
    seg[i] = triple(a, b, w);
  }
  int p; cin >> p;
  vector<triple> qs(p);
  int maxk = 0;
  for (int i = 0; i < p; ++i) {
    int a, b, k; cin >> a >> k >> b;
    b += a;
    v.push_back({i, 1});
    qs[i] = triple(a, b, k);
    maxk = max(maxk, k);
  }

  auto f = [&seg, &qs](ic &a){
    if (a.second)
      return qs[a.first].st;
    return seg[a.first].st;
  };
  sort(v.begin(), v.end(), [&f](ic &a, ic &b)->bool{return f(a) < f(b) || (f(a) == f(b) && a.second < b.second);});

  vector<int> knapsack(maxk+1);
  knapsack[0] = 1e9;
  for (auto event : v) {
    if (!event.second) {
      int &w = seg[event.first].w, &r = seg[event.first].en;
      for (int i = maxk-w; i >= 0; --i) {
        knapsack[i+w] = max(knapsack[i+w], min(r, knapsack[i]));
      }
    }
    else qs[event.first].w = knapsack[qs[event.first].w] 
                             > qs[event.first].en;
  }
  for (int i = 0; i < p; ++i) {
    if (qs[i].w)
      cout << "TAK\n";
    else
      cout << "NIE\n";
  }
}