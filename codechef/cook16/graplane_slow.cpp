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

int pop_pre[1 << 20];

void init_pop(int n) {  // n bits
  for (int b = 1; b < 1 << n; ++b) {
    pop_pre[b] = pop_pre[b & (b - 1)] + 1;
  }
}

inline int pop(int b) {
  return pop_pre[b];
}



int mem[1 << 18];
int nxt[1 << 18];

int N, M;
int adj[20], num2step[20], step2sel[10];

int loopcnt = 0;

int search(int b) {
  if (b == (1 << N) - 1) return 0;
  // int crr = __builtin_popcount(b);
  int crr = pop(b);

  if (mem[b] != -1) return mem[b];

  // int step = crr / max(1, (N / 4));
  // int sel = max(1, (N - crr) / (4 - step));
  int step = num2step[crr];
  int sel = step2sel[step];

  int tz = b == 0 ? 0 : __builtin_ctz(b);
  // printf("%d: %d\n", b, tz);

  int rem[20], rem_n = 0;
  rep (v, N) if (0 == (b & (1 << v))) {
    if (step > 0 && step2sel[step - 1] == step2sel[step] && v < tz) {   // Pruning
      // printf(" %d %d\n", b, v);
      continue;
    }
    rem[rem_n++] = v;
  }
  // rep (i, rem_n) printf(" %d", rem[i]); puts("");

  int res = 987654321, bst;

  // int n = rem_n - 1, k = sel - 1;
  int n = rem_n, k = sel;
  for (int m = (1 << k) - 1; m < (1 << n); ) {
    ++loopcnt;

    int d = 0;
    // d |= 1 << rem[0];
    // rep (i, n) d |= ((m >> i) & 1) << rem[i + 1];
    rep (i, n) d |= ((m >> i) & 1) << rem[i];

    int inc = 0;
    rep (i, n) if (m & (1 << i)) {
      // inc += __builtin_popcount(b & adj[rem[i]]);
      inc += pop(b & adj[rem[i]]);
    }
    int tmp = inc + search(b | d);
    if (tmp < res) {
      res = tmp;
      bst = d;
    }

    if (k == 0) break;
    int x = m & -m;
    int y = m + x;
    m = ((m & ~y) / x >> 1) | y;
  }

  nxt[b] = bst;
  return mem[b] = res;
}

int main() {
  int T;
  scanf("%d", &T);

  init_pop(18);

  rep (ca, T) {
    if (ca) puts("");

    scanf("%d%d", &N, &M);

    memset(adj, 0, sizeof(adj));
    rep (i, M) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;
      adj[a] |= 1 << b;
      adj[b] |= 1 << a;
    }

    {
      num2step[0] = 0;
      int n = N, s = 0;
      rep (i, 4) {
        num2step[s] = i;
        int t = max(1, n / (4 - i));
        step2sel[i] = t;
        s += t;
        n -= t;
        if (n == 0) break;
      }
    }

    loopcnt = 0;
    memset(mem, -1, sizeof(mem));

    printf("%d\n", search(0));
    // fprintf(stderr, "loop: %d\n", loopcnt);

    int x[20], y[20], q = 0;
    for (int b = 0; b < (1 << N) - 1; b |= nxt[b]) {
      int d = nxt[b];
      rep (v, N) if (d & (1 << v)) {
        x[v] = (v + 1) * (q & 1 ? -1 : 1);
        y[v] = (v + 1) * (q & 2 ? -1 : 1);
      }

      ++q;
    }

    rep (i, N) printf("%d %d\n", x[i], y[i]);
  }

  return 0;
}

