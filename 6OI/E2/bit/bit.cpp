#include <bits/stdc++.h>
#define INF INT32_MAX
using namespace std;

//separator character
const char X = 'X';

//bitmap holding pixels
vector<string> bmap;
//dist[i][j] is the distance to the nearest white pixel
vector< vector<int> > dist;
vector< vector<bool> > vis;

struct point {
  int x, y;
  point(){}
  point(int _x, int _y) : x(_x), y(_y) {}
};

vector<point> get_neighbours(const point& A) {
  vector<point> adj = {point(A.x+1, A.y),
                       point(A.x-1, A.y),
                       point(A.x, A.y+1),
                       point(A.x, A.y-1),
                      };
  return adj;
}

void bfs(queue<point>& Q) {
  while (!Q.empty()) {
    auto B = Q.front();
    Q.pop();

    auto adj = get_neighbours(B);
    for (auto C : adj) {
      if (!vis[C.x][C.y] && bmap[C.x][C.y] != X) {
        vis[C.x][C.y] = true;
        if (dist[C.x][C.y] > dist[B.x][B.y] + 1) {
          dist[C.x][C.y] = dist[B.x][B.y] + 1;
          Q.push(C);
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int w, h;
  cin >> h >> w;

  bmap.resize(h+2);
  dist.resize(h+2);
  vis.resize(h+2);
  for (int i = 0; i < h+2; ++i) {
    bmap[i].resize(w+2);
    vis[i].resize(w+2);
    dist[i].resize(w+2);
    fill(dist[i].begin(), dist[i].end(), INF);
  }


  queue<point> Q;

  bmap[0] = string(w+2, X);
  bmap[h+1] = string(w+2, X);

  for (int i = 1; i <= h; ++i) {
    string s;
    cin >> s;
    bmap[i] = X + s + X;
    for (int j = 1; j <= w; ++j) {
      if (bmap[i][j] == '1') {
        Q.push(point(i, j));
        dist[i][j] = 0;
        vis[i][j] = true;
      }
    }
  }

  bfs(Q);

  for (int i = 1; i <= h; ++i) {
    for (int j = 1; j <= w; ++j) {
      cout << dist[i][j] << ' ';
    } cout << endl;
  }
}