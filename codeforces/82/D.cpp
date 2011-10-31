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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

int N, A[1010];

int mem[1010][1010];
pair<int, int> nxt[1010][1010];

int search(int r, int k) {
  vector<int> frt;
  frt.pb(r);
  if (k     < N) frt.pb(k);
  if (k + 1 < N) frt.pb(k + 1);

  if (mem[r][k] != -1) return mem[r][k];

  if (frt.size() <= 2) {
    int ma = 0;
    rep (i, frt.size()) ma = max(ma, A[frt[i]]);
    return mem[r][k] = ma;
  }
  else {
    int ret = INT_MAX;
    pair<int, int> net = mp(-1, -1);
    rep (i, frt.size()) {
      int ma = 0;
      rep (j, frt.size()) if (i != j) ma = max(ma, A[frt[j]]);
      int tmp = ma + search(frt[i], k + 2);
      // printf(" %d->%d + %d\n", i, ma, search(frt[i], k + 2));
      if (tmp < ret) {
        ret = tmp;
        net = mp(frt[i], k + 2);
      }
    }
    // printf("%d %d: %d\n", r, k, ret);
    mem[r][k] = ret;
    nxt[r][k] = net;
    return ret;
  }
}

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d", A + i);

    memset(mem, -1, sizeof(mem));
    printf("%d\n", search(0, 1));

    int r = 0, k = 1;
    for (;;) {
      if (k + 1 < N) {
        int tr = nxt[r][k].first;
        int tk = nxt[r][k].second;
        if (tr == r) {
          printf("%d %d\n", k + 1, k + 2);
        } else {
          printf("%d %d\n", r + 1, tr == k ? k + 2 : k + 1);
        }
        r = tr;
        k = tk;
      }
      else {
        vector<int> frt;
        frt.pb(r);
        if (k     < N) frt.pb(k);
        if (k + 1 < N) frt.pb(k + 1);
        if (!frt.empty()) {
          rep (i, frt.size()) {
            if (i) putchar(' ');
            printf("%d", frt[i] + 1);
          }
          puts("");
        }
        break;
      }
    }
  }

  return 0;
}

