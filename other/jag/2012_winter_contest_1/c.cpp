#include <cstdio>
#include <utility>
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>
#include <stack>
#include <vector>
#include <map>
#include <queue>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define mp make_pair
#define T first
#define F second

typedef long long ll;
typedef pair<ll, ll> pll;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, -1, 0, 1};

int H, W, A;
char F[110][110];
bool vis[110][110][11][11][4];

struct status {
  int x, y, p, q, d;
};

void enque(status s, queue<status> &que) {
  // if (s.x == 2) puts("HELLO1");
  if (s.p < 0 || s.q < 0) return;
  // if (s.x == 2) printf("HELLO2: %d %d\n", s.x, s.y);
  if (F[s.y][s.x] == '#') return;
  // if (s.x == 2) puts("HELLO3");
  bool &v = vis[s.y][s.x][s.p][s.q][s.d];
  if (v) return;
  v = true;
  que.push(s);
}

int pdir(int d) {
  return 3 - d;
}

int qdir(int d) {
  return d ^ 1;
}

int main() {
  while (3 == scanf("%d%d%d", &H, &W, &A)) {
    memset(F, '#', sizeof(F));

    int px = -1, py = -1, gx = -1, gy = -1;
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
	scanf(" %c", &F[y][x]);
	if (F[y][x] == 'S') {
	  px = x;
	  py = y;
	  F[y][x] = '.';
	} else if (F[y][x] == 'G') {
	  gx = x;
	  gy = y;
	  F[y][x] = '.';
	}
      }
    }

    memset(vis, 0, sizeof(vis));
    queue<status> que;
    enque((status){px, py, A, A, 3}, que);
    while (!que.empty()) {
      status s = que.front();
      que.pop();

      if (s.x == px && s.y == py && s.d == 1) continue;
      
      // straight
      enque((status){s.x + dx[s.d], s.y + dy[s.d], s.p, s.q, s.d}, que);
	  
      if (s.x != px || s.y != py) {
	// P
	enque((status){s.x, s.y, s.p - 1, s.q, pdir(s.d)}, que);
	// Q
	enque((status){s.x, s.y, s.p, s.q - 1, qdir(s.d)}, que);
      }
    }

    int ans = INT_MAX;
    rep (p, A + 1) rep (q, A + 1) rep (d, 4) {
      if (vis[gy][gx][A - p][A - q][d]) {
	ans = min(ans, p + q);
      }
    }
    if (ans == INT_MAX) puts("-1");
    else printf("%d\n", ans);

    // return 0;
  }
}
