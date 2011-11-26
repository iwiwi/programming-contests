#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

int N, W, Q;

string S[20010];
int E[20010], P[20010];

string T[20010];
int mine[20010];

int ng[20010];

// a is in b ?
bool contain(const string &a, const string &b) {
  static const ll B = 101;

  int al = a.length(), bl = b.length();
  if (al > bl) return false;

  ll ah = 0, bh = 0, t = 1;
  rep (i, al) {
    ah = ah * B + (a[i] - 'a');
    bh = bh * B + (b[i] - 'a');
    t *= B;
  }
  for (int i = al; i <= bl; ++i) {
    if (ah == bh) return true;
    if (i < bl) bh = bh * B + (b[i] - 'a') - (b[i - al] - 'a') * t;
  }
  return false;
}


int main() {
  while (cin >> N >> W && (N | W)) {
    rep (i, N) cin >> S[i] >> E[i] >> P[i];
    cin >> Q;
    rep (i, Q) {
      cin >> T[i];

      vector<int> ngs;
      rep (j, i) {
        if (mine[j] == -1) continue;
        if (T[i].compare(0, min(T[i].length(), T[j].length()), T[j], 0, min(T[i].length(), T[j].length())) == 0) {
          ngs.pb(mine[j]);
          ++ng[mine[j]];
        }
      }

      int me = INT_MAX;
      int mej = -1;

      int dp[30] = {0};

      rep (j, N) {
        if (ng[j]) continue;
        if (!contain(T[i], S[j])) continue;

        if (E[j] < me) {
          me = E[j];
          mej = j;
        }

        for (int k = W - P[j]; k >= 0; --k) {
          dp[k + P[j]] = max(dp[k + P[j]], dp[k] + E[j]);
        }
      }
      if (mej == -1) puts("-1");
      else printf("%d\n", dp[W]);

      mine[i] = mej;

      rep (j, ngs.size()) --ng[ngs[j]];
    }
  }
}
