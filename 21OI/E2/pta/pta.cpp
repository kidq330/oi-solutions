#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
const int INF = 0x3f3f3f3f;

#define FOR(i, b, e) for(int i = (b); i < (e); ++i)
#define TRAV(x, a) for(auto &x: (a))
#define SZ(x) ((int)(x).size())
#define PB push_back
#define PR pair
#define X first
#define Y second

vi val, ans;

struct monoqueue {
  deque<int> D;
  // i < j
  bool comp(int i, int j) {
    return ans[i] < ans[j] || (ans[i] == ans[j] && val[i] < val[j]);
  }
  void push(int x) {
    while (!D.empty() && comp(x, D.back())) {
      D.pop_back();
    }
    D.push_back(x);
  }
  void pop(int x) {
    if (!D.empty() && D.front() == x)
      D.pop_front();
  }
  int min() {
    return D.front();
  }

};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n; cin >> n;
  val.resize(n);
  ans.resize(n);
  TRAV(x, val)
    cin >> x;
  
  int q; cin >> q;
  while (q--) {
    fill(ans.begin(), ans.end(), INF);
    ans[n-1] = 0;
    monoqueue Q;
    Q.push(n-1);
    int k; cin >> k;
    for (int i = n-2; i >= 0; --i) {
      int j = Q.min();
      ans[i] = ans[j] + (val[i] <= val[j]);
      Q.push(i);
      if (i < n-k) {
        Q.pop(i+k);
      }
    }
    cout << ans[0] << '\n';
  }
}