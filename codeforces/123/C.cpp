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

int N, M;
int S;
ll K;

int crr[210];
ll mem[210][210];

const ll MAX = 1E18 + 100;

ll search(int s, int d) {
  if (d < 0) return 0;
  if (s == S) {
    if (d == 0) return 1;
    else return 0;
  }
  if (crr[s] != 0) return search(s + 1, d + crr[s]);

  if (mem[s][d] != -1) return mem[s][d];
  return mem[s][d] = min(MAX, search(s + 1, d + 1) + search(s + 1, d - 1));
}

int main() {
  while (cin >> N >> M >> K) {
    --K;

    S = N + M - 1;
    vector<pair<int, int> > ps;
    rep (y, N) rep (x, M) {
      int p;
      scanf("%d", &p);
      ps.pb(mp(p, x + y));
    }

    sort(all(ps));
    memset(crr, 0, sizeof(crr));
    rep (i, ps.size()) {
      int s = ps[i].second;
      if (crr[s] != 0) continue;

      crr[s] = 1;

      memset(mem, -1, sizeof(mem));
      ll t = search(0, 0);

      // printf("t = %lld\n", t);

      if (K < t) continue;
      else {
        K -= t;
        crr[s] = -1;
      }
    }

    rep (y, N) {
      rep (x, M) putchar(")("[(crr[x + y] + 1) / 2]);
      puts("");
    }
  }

  return 0;
}

