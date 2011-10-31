#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define pb push_back
#define mp make_pair
#define all(v) v.begin(), v.end()

const int INF = 999999999;

int H, W;
char fld[20][20];

map<vector<int>, int> mem[20][20];

void normalize(vector<int> &v) {
  // rep (i, W) printf("%d ", v[i]); printf(" --- ");
  int color_n = 0;
  int color[30];
  rep (i, 21) color[i] = -1;
  rep (i, W) {
    if (v[i] < 0) continue;
    if (color[v[i]] == -1) color[v[i]] = color_n++;
    v[i] = color[v[i]];
  }
  // rep (i, W) printf("%d ", v[i]); puts("");
}

int search(int x, int y, const vector<int> &v) {
  if (x == W) return search(0, y + 1, v);
  if (y == H) {
    if (*max_element(all(v)) <= 0) return 0;
    else return -INF;
  }
  if (mem[y][x].count(v)) return mem[y][x][v];

  // printf("%d %d :", x, y); rep (i, W) printf(" %d", v[i]); puts("");

  int res = -INF;

  // Place
  {
    if (x > 0 && v[x - 1] >= 0 && v[x - 1] == v[x]) goto dmp1;
    if (fld[y][x] == '.') goto dmp1;

    vector<int> tv(v);
    if (x > 0 && tv[x - 1] >= 0 && tv[x] >= 0) {
      int fc = tv[x];
      rep (i, W) if (tv[i] == fc) tv[i] = tv[x - 1];
    }
    else if (x > 0 && tv[x - 1] >= 0) tv[x] = tv[x - 1];
    else if (tv[x]     >= 0)          tv[x] = tv[x];
    else                              tv[x] = 20;
    normalize(tv);

    res = max(res, 1 + search(x + 1, y, tv));
    // printf(" place search: %d\n", search(x + 1, y, tv));
  }
dmp1:;

  // Don't place
  {
    if (x > 0 && v[x - 1] == -1) goto dmp2;
    if (v[x] == -1) goto dmp2;
    if (fld[y][x] == '#') goto dmp2;

    if (v[x] >= 0 && count(all(v), v[x]) == 1) {
      // End?
      if (*max_element(all(v)) != 0) goto dmp2;
      rep (tx, W) rep (ty, H) if (mp(ty, tx) > mp(y, x) && fld[ty][tx] == '#') goto dmp2;
      res = max(res, 0);
    }
    else {
      // Continue
      vector<int> tv(v);
      tv[x] = -1;
      normalize(tv);
      res = max(res, search(x + 1, y, tv));
    }
  }
dmp2:;

  return mem[y][x][v] = res;
}

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    rep (y, H) scanf("%s", fld[y]);

    rep (y, H) rep (x, W) {
      if (fld[y][x] != '.') goto hoge;
    }
    puts("-1");
    continue;
 hoge:

    rep (y, H) rep (x, W) mem[y][x].clear();
    vector<int> v(W, -2);
    int res = search(0, 0, v);
    if (res < 0) puts("-1");
    else printf("%d\n", res);
  }

  return 0;
}
