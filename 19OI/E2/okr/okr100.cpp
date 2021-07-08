// Problem Desc.:
// given a string s and q queries
// compute the shortest primitive period of s[a:b]

// Single query complexity: O(logm)
// Full complexity: O(n + nlogn + q*logm)

// Solved using string hashing, kmr solution is also possible
// Used observations:
// 1.
// All primitive periods of s are of length k s.t. s % k == 0
// 2.
// Given a string p, p has a primitive period of length k iff 
// p[1:m-k] == p[k+1:n]
// Using hashing we can check this in O(1)
// 
// Let ex(k) be a boolean function that is true if a period of length k exists for string s
// and per(s) a function that returns the shortest primitive period of string s
// 3. 
// ~ex(a*k) => ~ex(k)
// if length a*k doesn't work, then neither does k, can be proven by contradiction
// 4.
// ex(k) => per(s) == per(s[0:n-k])
// if substring p is a period of s, then the shortest period of s is the shortest of p

// Using this we construct the following algorithm
// let len be the variable holding currently checked length
// k = spf[len]

// ex(len/k) for s[a:a+len] => per(s[a:a+len]) == per(a:a+len/k)
// ~ex(len/k) => k^alfa | per(s[a:a+len]) (alfa s.t. k^alfa | len and k^(alfa+1) ~| len)

// this follows from (3): if len = k^alfa*prod(k_i^alfa_i)
// len/k = k^(alfa-1)*prod(k_i^alfa_i)
// none of the combinations of divisors of len/k can be periods, but one of the combinations of len must be one
// only factor that divides len, but doesn't divide len/k is k^alfa
// Since we assume per(s) = m, instead of multiplying by k^alfa, we divide len by k^alfa
// You can speed this case up with quick exponentiation if you can avoid overflow

// The worst case per query is then O(logm), since we divide by at least 2 with each iteration

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

//smallest prime factor for nums up to n in O(nlogn)
auto spf_sieve(const int &n) {
  vector<int> spf(n+1);
  for (int i = 2; i <= n; ++i)
    spf[i] = i;
  for (int i = 2; i <= n; ++i)
    if (spf[i] == i)
      for (ll j = 1ll*i*i; j <= n; j += i)
        spf[j] = min(spf[j], i);
  return spf;
}

int n, q, m, l, r; 
string s;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> s >> q;

  auto spf = spf_sieve(n);
  
  hashed_string H(s);
  H.hash(BASE);
  H.del_string();
  s.clear();

  while (q--) {
    cin >> l >> r;
    m = r - l + 1;
    int per = m,
        len = m;
    while (len > 1) {
      int k = spf[len];
      if (H.equals(l, l + per/k, m - per/k)) {
        per /= k;
        len /= k;
      }
      else {
        while (spf[len] == k)
          len /= k;
      }
    }
    cout << per << endl;
  }
  return 0;
}