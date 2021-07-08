#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

struct max_queue {
  deque<pii> Q;
  void push_back(const pii &x) {
    while (!Q.empty() && Q.back() < x) {
      Q.pop_back();
    }
    Q.emplace_back(x);
  }

  void pop_front(const pii &x) {
    if (!Q.empty() && Q.front() == x) {
      Q.pop_front();
    }
  }

  int extract() {
    return Q.front().first;
  }

  bool empty() {
    return Q.empty();
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;

  max_queue Q;
  deque<pii> seq;
  int a, b;
  cin >> a >> b;
  Q.push_back({a, b});
  seq.push_back({a, b});
  cin >> a >> b;

  int ans = 1, g_ans = 1,
      i = 1;
  while (true) {
    if (b >= Q.extract() || Q.empty()) {
      Q.push_back({a, b});
      seq.push_back({a, b});
      ++ans, ++i;
      g_ans = max(g_ans, ans);
      if (i < n)
        cin >> a >> b;
      else break;
    }
    else {
      Q.pop_front(seq.front());
      seq.pop_front();
      --ans;
    }
  }

  cout << g_ans;

}