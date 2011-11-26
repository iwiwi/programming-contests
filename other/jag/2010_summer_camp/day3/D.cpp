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

struct union_find {
  int par[40010], rnk[40010];

  void init(int n) {
    rep (i, n) {
      par[i] = i;
      rnk[i] = 0;
    }
  }

  int root(int x) {
    return par[x] == x ? x : par[x] = root(par[x]);
  }

  bool unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x == y) return false;

    if (rnk[x] < rnk[y]) {
      par[x] = y;
    } else {
      par[y] = x;
      if (rnk[x] == rnk[y]) ++rnk[x];
    }
    return true;
  }
};

const int B = 200;

int N, K;
int Q[40010], U[40010], V[40010];

int M, s[40010], t[40010], con[40010], des[40010];

union_find uf1, uf2;
int vid[40010];
int ts[210], tt[210], tcon[210], tdes[210];

int main() {
  scanf("%d%d", &N, &K);

  map<pair<int, int>, int> id;
  rep (i, K) {
    scanf("%d%d%d", Q + i, U + i, V + i);
    if (Q[i] == 1) {
      s[M] = U[i];
      t[M] = V[i];
      con[M] = i;
      des[M] = K;
      id[mp(U[i], V[i])] = M++;
    }
    else if (Q[i] == 2) {
      iter(id) ite = id.find(mp(U[i], V[i]));
      des[ite->second] = i;
      id.erase(ite);
    }
  }

  for (int b = 0; b * B < K; ++b) {
    int bb = b * B;
    int be = min((b + 1) * B, K);

    vector<int> es;
    uf1.init(N);
    rep (i, M) {
      if (con[i] < bb && be <= des[i]) uf1.unite(s[i], t[i]);
      else if (be <= con[i]) break;
      else if (des[i] < bb) continue;
      else es.push_back(i);
    }

    int en = es.size();
    int tvn = 0;
    memset(vid, -1, sizeof(vid));
    rep (i, en) {
      vid[uf1.root(s[es[i]])] = 0;
      vid[uf1.root(t[es[i]])] = 0;
    }
    rep (i, N) if (vid[i] == 0 && uf1.par[i] == i) vid[i] = tvn++;

    rep (i, en) {
      int e = es[i];
      ts[i] = vid[uf1.root(s[e])];
      tt[i] = vid[uf1.root(t[e])];
      tcon[i] = con[e];
      tdes[i] = des[e];
    }

    for (int i = bb; i < be; ++i) {
      if (Q[i] != 3) continue;
      if (uf1.root(U[i]) == uf1.root(V[i])) {
        puts("YES");
        continue;
      }

      uf2.init(tvn);
      rep (j, en) {
        if (i < tcon[j]) break;
        if (i < tdes[j]) uf2.unite(ts[j], tt[j]);
      }

      int tv = vid[uf1.root(U[i])];
      int tw = vid[uf1.root(V[i])];
      if (tv != -1 && tw != -1 && uf2.root(tv) == uf2.root(tw)) {
        puts("YES");
      } else {
        puts("NO");
      }
    }
  }

  return 0;
}

