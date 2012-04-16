#include <cstdio>
#include <set>
#include <map>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define iter(c) __typeof((c).begin())
#define mp make_pair

int N, W, H;
int A[20];
int sum[1 << 16];

map<int, bool> mem[110][110];

bool search(int w, int h, int b) {
  int s = sum[b];
  if (w * h != s) return false;

  if ((b & (b - 1)) == 0) return true;  // done

  pair<iter(mem[w][h]), bool> ins = mem[w][h].insert(mp(b, false));  // temporarily insert
  if (ins.second == false) return ins.first->second;

  int tb = b;
  do {
    int ts = sum[tb];
    if (ts % h == 0) {
      int tw = ts / h;
      if (search(tw, h, tb) && search(w - tw, h, b - tb)) goto ok;
    }
    if (ts % w == 0) {
      int th = ts / w;
      if (search(w, th, tb) && search(w, h - th, b - tb)) goto ok;
    }

    // for (int tw = 1; tw < w; ++tw) if (search(tw, h, tb) && search(w - tw, h, b - tb)) goto ok;
    // for (int th = 1; th < h; ++th) if (search(w, th, tb) && search(w, h - th, b - tb)) goto ok;
    tb = (tb - 1) & b;
  } while (tb != b);

  return ins.first->second = false;
ok:
  // printf("%d %d %x: true\n", w, h, b);
  return ins.first->second = true;
}

int main() {
  for (int ca = 0; ; ++ca) {
    scanf("%d", &N);
    if (N == 0) return 0;

    scanf("%d%d", &W, &H);
    rep (i, N) scanf("%d", &A[i]);

    rep (b, 1 << N) {
      int s = 0;
      rep (i, N) if (b & (1 << i)) s += A[i];
      sum[b] = s;
    }

    for (int w = 0; w <= W; ++w) for (int h = 0; h <= H; ++h) mem[w][h].clear();

    printf("Case %d: ", ca + 1);
    if (search(W, H, (1 << N) - 1)) puts("Yes");
    else puts("No");
  }
}
