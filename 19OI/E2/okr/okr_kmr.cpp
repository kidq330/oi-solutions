#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// okr100.cpp using kmr instead of hashing

class KMR {
  public:
    int len;
    std::string s;
    std::vector<int> lg;
    std::vector< std::vector<int> > kmr;

    KMR(std::string& _s) {
      s = _s;
      len = s.size();
    }

    KMR(){}

    void calc_logs() {
      lg.resize(len+1);
      lg[1] = 0;
      for (int i = 2; i <= len; ++i) {
        lg[i] = lg[i/2] + 1;
      }
    }

    void make_kmr() {
      int l = (int)floor(log2(len));
      kmr.resize(l+1);
      kmr[0].resize(len);
      for (int i = 0; i < len; ++i) {
        kmr[0][i] = s[i] - 'a' + 1;
      }

      struct triple {
        int a, b, index;
        triple(int _a, int _b, int _i) : a(_a), b(_b), index(_i) {}
        triple(){}
      };
      auto comp = [](const triple& x, const triple& y) {
        return x.a < y.a || (x.a == y.a && x.b < y.b);
      };

      std::vector<triple> aux;
      for (int t = 1; t <= l; ++t) {
        int d = 1 << (t - 1);
        aux.resize(len - 2*d + 1);
        kmr[t].resize(len - 2*d + 1);

        for (int i = 0; i + 2*d <= len; ++i)
          aux[i] = triple(kmr[t-1][i], kmr[t-1][i + d], i);
        sort(aux.begin(), aux.end(), comp);

        int j = 1;
        kmr[t][aux[0].index] = 1;
        for (int i = 1; i + 2*d <= len; ++i) {
          int s = aux[i].index;
          if (comp(aux[i-1], aux[i]))
            kmr[t][s] = ++j;
          else
            kmr[t][s] = j;
        }
      }
    }

    bool comp_subs(int a, int b, int len) {
      int l = lg[len];
      int d = 1 << l;
      return kmr[l][a] < kmr[l][b] || 
            (kmr[l][a] == kmr[l][b] && kmr[l][a + len - d] < kmr[l][b + len - d]);
    }

    bool equal_subs(int a, int b, int len) {
      int l = lg[len];
      int d = 1 << l;
      return kmr[l][a] == kmr[l][b] && 
             kmr[l][a + len - d] == kmr[l][b + len - d];
    }
};

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
  cin >> n >> s >> q;

  auto spf = spf_sieve(n);

  KMR K(s);
  K.calc_logs();
  K.make_kmr();
  
  while (q--) {
    cin >> l >> r;
    --l, --r;
    m = r - l + 1;
    int per = m,
        len = m;
    while (len > 1) {
      int k = spf[len];
      if (K.equal_subs(l, l + per/k, m - per/k)) {
        per /= k;
        len /= k;
      }
      else
        while (spf[len] == k)
          len /= k;
    }
    cout << per << endl;
  }
}

// 9
// bbaacbaaa
// 1
// 1 7