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

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, -1, 0, 1};

int N;
char fld[60][60];

vector<pair<bool, int> > T;  // (forced, size)

pair<bool, int> search(int x, int y, int d) {

  vector<int> tds;
  pair<bool, int> tps[4];
  for (int dd = -1; dd <= 1; ++dd) {
    int td = (d + dd + 4) % 4;
    if (fld[y + dy[td]][x + dx[td]] != '#') {
      tds.pb(td);
      tps[td] = search(x + dx[td], y + dy[td], td);
    }
  }

  if (tds.size() == 0) {
    return mp(fld[y][x] == 'G', 1);
  }
  else if (tds.size() == 1) {
    pair<bool, int> tp = tps[tds[0]];
    return mp(tp.first, tp.second + 1);
  }
  else {
    bool goal = false;
    rep (i, tds.size()) goal |= tps[tds[i]].first;

    if (!goal) {
      int tot = 1;
      rep (i, tds.size()) tot += tps[tds[i]].second;
      return mp(false, tot);
    }
    else {
      vector<pair<bool, int> > tt;

      if (cpresent(tds, d)) {
        if (tps[d].first) return mp(true, 1 + tps[d].second);
        else tt.pb(mp(true, tps[d].second));

        tds.erase(find(all(tds), d));
        if (tds.size() == 1) {
          T.insert(T.end(), tt.rbegin(), tt.rend());
          return mp(true, tps[tds[0]].second + 1);
        }
      }

      assert(tds.size() == 2);
      if (tps[tds[0]].first == false) swap(tds[0], tds[1]);
      assert(tps[tds[0]].first == true && tps[tds[1]].first == false);

      tt.pb(mp(false, tps[tds[1]].second));
      T.insert(T.end(), tt.rbegin(), tt.rend());
      return mp(true, tps[tds[0]].second + 1);
    }
  }

  assert(false);
}

double cmb[2510][2510];

void init_cmb(int N) {
  cmb[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    cmb[i][0] = cmb[i - 1][0] * 0.5;
    for (int j = 1; j <= i; ++j) cmb[i][j] = (cmb[i-1][j-1] + cmb[i-1][j]) / 2;
  }
}


int main() {
  while (1 == scanf("%d", &N)) {
    memset(fld, '#', sizeof(fld));
    for (int y = 1; y <= N; ++y) {
      char buf[60];
      scanf("%s", buf);
      for (int x = 1; x <= N; ++x) {
        fld[y][x] = buf[x - 1];
      }
    }

    T.clear();
    search(1, 1, 0);

    // printf("E = %d, T =", E); rep (i, T.size()) printf(" (%c, %d)", "FT"[T[i].first], T[i].second); puts("");

    int A = 1;
    rep (i, T.size()) A += T[i].second;
    init_cmb(A);

    vector<double> dp(A + 1, 0);
    dp[1] = 1.0;
    int tot = 1;
    rep (i, T.size()) {
      vector<double> nxt(A + 1);
      int t = T[i].second;
      tot += t;
      for (int come = 1; come <= tot; ++come) {
        if (T[i].first) {
          if (t > come) nxt[come] = 0.0;
          else nxt[come] = dp[come - t];
        }
        else {
          nxt[come] = 0.0;
          // here < t
          for (int here = 0; here < t && here <= come - 1; ++here) {
            nxt[come] += dp[come - here] * cmb[come - 1][here] * 0.5;
          }
          // here == t
          if (t <= come - 1) {
            for (int end = t; end <= come - 1; ++end) {
              nxt[come] += dp[come - t] * cmb[end - 1][t - 1] * 0.5;
            }
          }
        }
      }

      swap(dp, nxt);
    }

    double e = 0;
    for (int a = 1; a <= A; ++a) e += a * dp[a];
    printf("%.10f\n", e);
  }

  return 0;
}

