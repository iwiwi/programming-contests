#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <numeric>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

int H, Q;
map<int, int> val, sum;

void add(int v, int e) {
  val[v] += e;
  sum[v] += e;
  while (v > 1) {
    int p = v / 2;
    sum[p] += e;
    v = p;
  }
}

double calc() {
  double res = 0.0, prb = 0.5;
  int v = 1, psum = 0;
  rep (h, H) {
    int lch = v * 2, rch = v * 2 + 1;
    int lsum = val[v] + sum[lch], rsum = val[v] + sum[rch];
    res += prb * max(max(lsum, rsum), psum);

    v = lsum > rsum ? lch : rch;
    psum = max(psum, min(lsum, rsum));
    if (h + 1 < H) prb *= 0.5;
  }
  res += prb * max(val[v], psum);
  return res;
}

int main() {
  scanf("%d%d", &H, &Q);
  rep (q, Q) {
    char str[256];
    scanf("%s", str);
    if (str[0] == 'a') {
      int v, e;
      scanf("%d%d", &v, &e);
      add(v, e);
    }
    else {
      printf("%f\n", calc());
    }
  }

  return 0;
}

