#include <bits/stdc++.h>
using namespace std;

const int BASE = 31;
vector<int> pw;

int char_value(const char &c) {
  return c - 'a' + 1;
}

void add_digit(int &n, const char &c) {
  n *= BASE;
  n += char_value(c);
}

void roll(int &n, const char &prev, const char &next, const int &bp) {
  n = BASE*(n - char_value(prev)*bp) + char_value(next); 
}

// fills the pw vector with pw[i] = BASE^i
void compute_powers(const int &n) {
  pw.resize(n+1);
  pw[0] = 1;
  for (int i = 1; i <= n; ++i)
    pw[i] = pw[i-1]*BASE;
}

// returns vector of hashes of all substrings of length k
vector<int> gen_hashes(string &s, const int &k) {
  const int n = s.size();
  vector<int> subs(n - k + 1);

  int hash = 0;
  for (int i = 0; i < k; ++i)
    add_digit(hash, s[i]);
  subs[0] = hash;

  for (int i = 1; i < n - k + 1; ++i) {
    roll(hash, s[i-1], s[i+k-1], pw[k-1]);
    subs[i] = hash;
  }

  return subs;
}

bool sub_exists(vector<string> &v, const int &k) {

  const int n = v.size();
  string &s = v[n-1];

  auto subs = gen_hashes(s, k);
  vector<int> common;
  
  for (int i = 0; i < n-1; ++i) {
    auto sorted_subs = gen_hashes(v[i], k);
    sort(sorted_subs.begin(), sorted_subs.end());

    for (auto x : subs) {
      if (binary_search(sorted_subs.begin(), sorted_subs.end(), x)) {
        common.push_back(x);
      }
    }
    if (common.size() == 0)
      return 0;
    subs.swap(common);
    common.clear();
  }

  return 1;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  vector<string> V(n);
  cin >> V[0];

  for (int i = 1; i < n; ++i) {
    cin >> V[i];
    if (V[i].size() < V[0].size())
      V[0].swap(V[i]);
  }

  V[0].swap(V[n-1]);
  compute_powers(V[n-1].size());


  //when writing a binsearch over possible answers like this
  //make sure hi is 1 outside the answer range, otherwise if the answer = max
  //the lo var will never reach it
  int lo = 0, hi = V[n-1].size() + 1;
  while (lo + 1 < hi) {
    int k = (lo + hi) / 2;
    if (sub_exists(V, k))
      lo = k;
    else
      hi = k;
  }

  cout << lo << endl;
}