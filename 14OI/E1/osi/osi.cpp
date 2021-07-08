// Problem: Osie symetrii
// Given a set of points forming an n-gon, count its axes of symmetry
// Complexity: O(n), hashes the polygon as a sequence of alternating side lengths and angle measures
// Turns out the determinant of the vectors making the angle is enough to represent it
// the polygon has an axis of symmetry if the corresponding substrings in the sequence
// are reverses of each other

#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
constexpr ll b = 1e5+3, p = 1e9+696969, 
             binv = 632081285; // == b^(p-2)

ll sq(const ll &x) {
  return x*x;
}

ii operator+(ii const& a, ii const& b) {
  return {a.X+b.X, a.Y+b.Y};
}

ii operator/(ii const& a, int d) {
  return {a.X/d, a.Y/d};
}

pll operator*(pll const& a, int d) {
  return {a.X*d, a.Y*d};
}

pll vec(pll const& a, pll const& b) {
  return {b.X-a.X, b.Y-a.Y};
}

ll det(pll const& u, pll const& v) {
  return u.X*v.Y - u.Y*v.X;
}

ll magnitude2(pll const& u) {
  return sq(u.X) + sq(u.Y);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int Z; cin >> Z;
  while (Z--) {

    int n; cin >> n;
    vector<ii> pts(2*n);

    cin >> pts[0].X >> pts[0].Y;
    pts[0] = pts[0]*2;

    for (int i = 1; i < n; ++i) {
      cin >> pts[2*i].X >> pts[2*i].Y;
      pts[2*i] = pts[2*i]*2;
      pts[2*i-1] = (pts[2*i-2] + pts[2*i])/2;
    }
    pts[2*n-1] = (pts[2*n-2] + pts[0])/2;

    // This holds codings of side lengths squared & angle determinants
    unordered_map<ll, int> M;
    M.reserve(1 << 19);
    M.max_load_factor(0.25);
    int t = 0;

    vector<int> s;
    s.reserve(n << 3);

    pll u = vec(pts[0], pts.back()), v;
    pts.push_back(pts[0]);

    for (int i = 0; i < 2*n; ++i) {
      v = vec(pts[i], pts[i+1]);

      ll angle_code = det(u, v),
         side_code = magnitude2(u);
      
      if (M[side_code] == 0) {
        M[side_code] = ++t;
      }
      if (M[angle_code] == 0) {
        M[angle_code] = ++t;
      }

      s.push_back(M[side_code]);
      s.push_back(M[angle_code]);
      u = v*(-1);
    }

    // duplicating s
    copy_n(s.begin(), n << 2, back_inserter(s));
    ll h1 = 0, h2 = 0, b2n = 1;
    // computing 2 windows of length 2n-1
    for (int i = 0; i < 2*n-1; ++i, b2n = b2n*b%p) {
      h1 = (h1 + s[i]*b2n % p) % p;
      h2 = (h2*b % p + s[2*n+i]) % p;
    }
    // b2n == b^(2n-2)
    b2n = b2n*binv % p;

    auto roll1 = [s, n, b2n](ll &h, int i){return h = ((((h - s[i] + p) % p)*binv % p) + s[i+2*n-1]*b2n%p) % p;};
    auto roll2 = [s, n, b2n](ll &h, int i){return h = (((h - (b2n*s[i] % p) + p) % p)*b % p + s[i+2*n-1]) % p;};

    int cnt = 0;
    for (int i = 0; i < 2*n; i += 2) {
      cnt += h1 == h2;
      roll1(h1, i);
      roll1(h1, i+1);
      roll2(h2, 2*n+i); 
      roll2(h2, 2*n+i+1);
    }
    cout << cnt << '\n';
  }
}