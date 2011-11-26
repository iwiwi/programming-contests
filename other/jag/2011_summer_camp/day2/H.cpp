#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair

const int H = 4;
const int W = 4;
char col[10][10];

int N, w[20], h[20];

int mem[1 << 17];

int getb(int b, int x, int y) {
  return (b >> (y * H + x)) & 1;
}
int setb(int b, int x, int y) {
  return b | (1 << (y * H + x));
}


vector<pair<pair<int, int>, pair<int, int> > > rects;

int search(int b) {
  if (b == (1 << (H * W)) - 1) return 0;
  if (mem[b] != -1) return mem[b];

  int res = 999;
  rep (i, rects.size()) {
    int x1 = rects[i].first.first;
    int x2 = rects[i].first.second;
    int y1 = rects[i].second.first;
    int y2 = rects[i].second.second;

    char c = 0;
    int tb = b;
    rep (y, H) rep (x, W) {
      if (x1 <= x && x < x2 && y1 <= y && y < y2) {
        if (getb(b, x, y) == 1) continue;

        char t = col[y][x];
        if (c == 0) c = t;
        else if (c != t) goto dmp;  // not yet && wrong color

        tb = setb(tb, x, y);
      }
    }

    // recurse!
    if (tb != b) res = min(res, 1 + search(tb));

 dmp:;
  }

  return mem[b] = res;
}

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d%d", &h[i], &w[i]);
    rep (y, H) scanf("%s", col[y]);

    rects.clear();
    rep (i, N) {
      for (int y1 = -H; y1 < H; ++y1) {
        for (int x1 = -W; x1 < W; ++x1) {
          int y2 = min(y1 + h[i], H);
          int x2 = min(x1 + w[i], W);

          if (x2 <= 0 || y2 <= 0) continue;
          rects.push_back(mp(mp(x1, x2), mp(y1, y2)));
        }
      }
    }
    sort(rects.begin(), rects.end());
    rects.erase(unique(rects.begin(), rects.end()), rects.end());

    memset(mem, -1, sizeof(mem));
    printf("%d\n", search(0));
  }
}
