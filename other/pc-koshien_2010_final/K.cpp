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
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

int W, H;
int fld[10][10];



const int pow3[] = {
  1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441
};

const int MAX_B = 177147;  // 3^(W+1)

int v[20];

inline int get3(int b, int k) {
  return b / pow3[k] % 3;
}

inline int set3(int b, int k, int a) {
  return (b - b % pow3[k + 1]) + a * pow3[k] + b % pow3[k];
}

void show(int b) {
  rep (i, W + 1) printf("%d ", get3(b, i)); puts("");
}

int end(int k) {
  if (v[k] == 1) {
    int lev = 1;
    for (int x = k + 1; x <= W; ++x) {
      if (v[x] == 1) ++lev;
      if (v[x] == 2) --lev;
      if (lev == 0) return x;
    }
  }
  else if (v[k] == 2) {
    int lev = 1;
    for (int x = k - 1; x >= 0; --x) {
      if (v[x] == 1) --lev;
      if (v[x] == 2) ++lev;
      if (lev == 0) return x;
    }
  }
  assert(false);
}

ll dp[2][MAX_B];
int que[2][MAX_B], que_n[2];

inline void add(int t, int b, ll c) {
  if (dp[t][b] == 0) que[t][que_n[t]++] = b;
  dp[t][b] += c;
}

bool solve() {
  memset(dp, 0, sizeof(dp));
  int crr = 0, nxt = 1;
  dp[crr][0] = 1;
  que[crr][0] = 0;
  que_n[crr] = 1;

  rep (y, H) rep (x, W) {
    memset(dp[nxt], 0, sizeof(ll) * pow3[W + 1]);
    que_n[nxt] = 0;

    rep (i, que_n[crr]) {
      int b = que[crr][i];
      ll c = dp[crr][b];

      rep (i, W + 1) v[i] = get3(b, i);
      if (x == 0) {
        rotate(v, v + W, v + W + 1);
        if (v[0] != 0) continue;
        b *= 3;
      }

      // Place
      if (!fld[y][x]) {
        if (v[x] && v[x + 1]) {
          int e1 = end(x), e2 = end(x + 1);
          if (e1 != x + 1) {
            int tb = set3(set3(b, x, 0), x + 1, 0);
            tb = set3(set3(tb, min(e1, e2), 1), max(e1, e2), 2);
            add(nxt, tb, c);
          }
        } else if (v[x]) {
          add(nxt, b, c);
          add(nxt, set3(set3(b, x, 0), x + 1, v[x]), c);
        } else if (v[x + 1]) {
          add(nxt, b, c);
          add(nxt, set3(set3(b, x, v[x + 1]), x + 1, 0), c);
        } else {
          add(nxt, set3(set3(b, x, 1), x + 1, 2), c);
        }
      }

      // Don't place
      if (fld[y][x]) {
        if (v[x] || v[x + 1]);  // NG
        else add(nxt, b, c);
      }
    }
    swap(nxt, crr);
  }

  // cout << dp[crr][set3(set3(0, 0, 1), W - 1, 2)] << endl;
  rep (x, W - 1) {
    if (fld[H - 1][x] == 0) {
      if (fld[H - 1][x + 1] != 0) return false;
      else return dp[crr][set3(set3(0, x, 1), x + 1, 2)] > 0;
    }
  }
  return false;
}




int main() {
  for (;;) {
    scanf("%d%d", &W, &H);
    if (W == 0 && H == 0) return 0;

    rep (y, H) rep (x, W) scanf("%d", &fld[y][x]);

    while (H > 0) {
      if (count(fld[H - 1], fld[H - 1] + W, 0) == 0) --H;
      else break;
    }

    if (H == 0) puts("No");  // !!?!?!???!?!?!?
    else if (H == 1) puts("No");  // I think so
    else {
      if (solve()) puts("Yes");
      else puts("No");
    }
  }

  return 0;
}

