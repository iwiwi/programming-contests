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



const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

typedef pair<int, int> pii;
typedef pair<pii, pii> piiii;

int M, N;
char fld[60][60];

map<pair<int, int>, pair<int, int>, int> mem;

int main() {
  while (2 == scanf("%d%d", &M, &N)) {
    rep (y, M) rep (x, M) scanf(" %c", &fld[y][x]);

    mem.clear();
    piiii p = mp(mp(0, 0), mp(0, -1));
    rep (i, N) {
      int x = p.
    }
  }
  return 0;
}

