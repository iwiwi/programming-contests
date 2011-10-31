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

#define F first
#define S second

typedef pair<pair<int, int>, pair<bool, bool> > ppiipii;

int X, Y, N, D;
int dx[30], dy[30];

map<ppiipii, bool> mem;

inline int sqr(int x) { return x * x; }

bool saiki(ppiipii s) {
  if (sqr(s.F.F) + sqr(s.F.S) > sqr(D)) return true;
  if (mem.count(s)) return mem[s];

  rep (i, N) {
    if (!saiki(mp(mp(s.F.F + dx[i], s.F.S + dy[i]), mp(s.S.S, s.S.F)))) return mem[s] = true;
  }
  if (s.S.F) {
    if (!saiki(mp(mp(s.F.S, s.F.F), mp(s.S.S, false)))) return mem[s] = true;
  }
  return mem[s] = false;
}

int main() {
  scanf("%d%d%d%d", &X, &Y, &N, &D);
  rep (i, N) scanf("%d%d", dx + i, dy + i);

  if (saiki(mp(mp(X, Y), mp(true, true)))) puts("Anton");
  else puts("Dasha");

  return 0;
}

