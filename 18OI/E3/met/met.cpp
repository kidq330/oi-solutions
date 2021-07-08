#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1 << 30;

struct triple {
  int l, r, val;
  triple(int _l, int _r, int _v) : l(_l), r(_r), val(_v) {}
  triple() {}
};


int middle(const triple& a) {
  return (a.l + a.r)/2;
}

ll query(int i, vector<ll> &T) {
  ll res = 0;
  while (i >= 0) {
    res += T[i];
    i = (i&(i+1)) - 1;
  }
  return res;
}

void increment(int i, int val, vector<ll> &T) {
  while (i < T.size()) {
    T[i] += val;
    i |= i+1;
  }
}

void update(const triple& u, vector<ll> &T) {
  if (u.l > u.r)
    increment(0, u.val, T);
  increment(u.l, u.val, T);
  if (u.r+1 < T.size())
    increment(u.r+1, -u.val, T);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, m, k;
  cin >> n >> m;
  vector<int> owner(m), lim(n);
  vector<vector<int>> owned(n);
  for (int i = 0; i < m; ++i) {
    cin >> owner[i]; --owner[i];
    owned[owner[i]].push_back(i);
  }
  for (auto &x : lim) 
    cin >> x;
  
  cin >> k;
  vector<triple> upd(k);

  for (auto &x : upd) {
    cin >> x.l >> x.r >> x.val;
    --x.l, --x.r;
  }
  upd.push_back(triple(0, k-1, INF));

  int lg = (int)log2(k+1) + 1;
  
  vector<triple> w(n);
  for (int i = 0; i < n; ++i) {
    w[i] = triple(0, k, i);
  }

  vector<ll> T(m);

  while (lg--) {
    int i = 0, t = -1;
    for (int i = 0; i < n; ++i) {
      int mid = middle(w[i]);
      while (t < mid) {
        update(upd[++t], T); 
      }
      unsigned long long sum = 0;
      for (auto x : owned[w[i].val])
        sum += query(x, T);
      if (sum < lim[w[i].val])
        w[i].l = mid+1;
      else
        w[i].r = mid;
    }

    sort(w.begin(), w.end(), 
    [](triple a, triple b){return middle(a) < middle(b);});

    fill(T.begin(), T.end(), 0);
  }

  vector<int> ans(n);
  for (auto x : w) {
    ans[x.val] = middle(x);
  }
  for (auto x : ans) {
    if (x == k) cout << "NIE";
    else cout << x+1;
    cout << '\n';
  }

}