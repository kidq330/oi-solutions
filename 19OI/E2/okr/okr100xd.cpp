// Problem Desc.:
// given a string s and q queries
// compute the shortest primitive period of s[a:b]

// Single query complexity: O(m^(1/3)) using the divisor approximation
// Full complexity: O(n + nlogn + q*m^(1/3))

// Solved using string hashing, kmr solution is also possible
// Used observations:
// 1.
// All primitive periods of s are of length k s.t. s % k == 0
// 2.
// Given a string p, p has a primitive period of lenght k iff 
// p[1:m-k] == p[k+1:n]
// Using hashing we can check this in O(1)

// Divisors of all numbers up to n are computed with a sieve in O(nlogn)
// This precomputation proves to be much faster than computing divisors independent of queries

// Both take asymptotic O(sqrt(m)) time, but independent computation has a far worse constant
// worsened further by the q multiplier

// For the most efficient solution using a D&C paradigm in O(logm), see okr100.cpp

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int BASE = 31;

class hashed_string{
  public:
    int len;
    string s;
    vector<int> ph,
                pw;
  
    hashed_string(string &sx) {
      s = sx;
      len = s.size();
    }

    void hash(const int &base, const int &mod) {
      ph.resize(len+1);
      pw.resize(len+1);
      pw[0] = 1;
      ph[0] = 0;
      for (int i = 1; i <= len; ++i) {
        pw[i] = pw[i-1]*base % mod;
        ph[i] = (ph[i-1] + pw[i]*(s[i-1] - 'a' + 1) % mod) % mod; 
      }
    }

    void hash(const int &base) {
      ph.resize(len+1);
      pw.resize(len+1);
      pw[0] = 1;
      ph[0] = 0;
      for (int i = 1; i <= len; ++i) {
        pw[i] = pw[i-1]*base;
        ph[i] = ph[i-1] + pw[i]*(s[i-1] - 'a' + 1); 
      } 
    }

    //makes original string empty to free memory
    void del_string() {
      s.clear();
    }

    //returns p^i*s[i] + p^(i+1)*s[i+1] ... + p^(i + len - 1)*s[i + len - 1]
    int get_substring(int i, int len) {
      return ph[i + len - 1] - ph[i - 1];
    }

    //checks if two substring of lenght len starting from indices a, b are equal
    bool equals(int a, int b, int len) {
      return get_substring(a, len)*pw[b] == get_substring(b, len)*pw[a];
    }
};

bool operator==(const hashed_string& s, const hashed_string& p) {
  return s.ph[s.len] == p.ph[p.len];
}

auto div_sieve(const int &n) {
  vector< vector<int> > divs(n+1);
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      divs[j].push_back(i);
    }
  }
  return divs;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, q, m, a, b; 
  string s;
  
  cin >> n >> s >> q;

  auto divs = div_sieve(n);

  hashed_string H(s);
  H.hash(BASE);
  H.del_string();
  s.clear();

  while (q--) {
    cin >> a >> b;
    m = b - a + 1;

    for (int k : divs[m]) {
      if (H.equals(a, a + k, m - k)) {
        cout << k << endl;
        break;
      }
    }
  }
  return 0;
}

