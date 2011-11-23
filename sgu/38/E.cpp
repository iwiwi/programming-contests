#include <cstdio>
#include <algorithm>
#include <utility>
#include <climits>
#include <iostream>
#include <vector>
#include <functional>
#include <cstring>
#include <cassert>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(c) (c).begin(), (c).end()

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, pii> piiii;

int N;
vector<piiii> cadj[100010];
piiii padj[100010];

int D;
vector<int> chd[1000010];

int diameter(int v, int p) {
  rep (i, cadj[v].size()) {
    if (cadj[v][i].F.F == p) {
      padj[v] = cadj[v][i];
      cadj[v].erase(cadj[v].begin() + i);
      break;
    }
  }
  if (p == -1) padj[v] = mp(mp(-1, -1), mp(-1, -1));

  vector<int> tmp(2, 0);
  chd[v].resize(cadj[v].size());
  rep (i, cadj[v].size()) {
    chd[v][i] = cadj[v][i].S.F + diameter(cadj[v][i].F.F, v);
    tmp.pb(chd[v][i]);
  }
  partial_sort(tmp.begin(), tmp.begin() + 2, tmp.end(), greater<int>());
  D = max(D, tmp[0] + tmp[1]);
  return tmp[0];
}

bool memp[100010][2];
vector<bool> memc[100010][2];

pii doit(int v, int p) {
  int chn = chd[v].size();
  memp[v][0] = memp[v][1] = false;
  memc[v][0] = memc[v][1] = vector<bool>(chn, false);

  int d0 = chd[v].empty() ? 0 : *max_element(chd[v].begin(), chd[v].end());
  int d1 = 0;
  rep (i, chn) if (chd[v][i] < d0) d1 = max(d1, chd[v][i]);

  vector<int> ch0, ch1;
  rep (i, chd[v].size()) {
    if (chd[v][i] == d0) ch0.pb(i);
    else if (chd[v][i] == d1) ch1.pb(i);
  }
  int n0 = ch0.size(), n1 = ch1.size();

  int lgd = ch0.size() >= 2 ? 2 * d0 : d0 + d1;

  int base = 0;
  rep (i, cadj[v].size()) {
    if (chd[v][i] != d0 && chd[v][i] != d1) base += doit(cadj[v][i].F.F, v).F;
  }
  vector<int> chc0(n0), chc1(n1);
  rep (i, n0) {
    pii c = doit(cadj[v][ch0[i]].F.F, v);
    base += c.first;
    chc0[i] = c.second - c.first;
  }
  rep (i, n1) {
    pii c = doit(cadj[v][ch1[i]].F.F, v);
    base += c.first;
    chc1[i] = c.second - c.first;
  }

  int res0, res1;

  { // Zero
    if (lgd < D) {
      res0 = 0;
    } else {
      if (ch0.size() >= 2) {  // Case 2
        int s = 0, mint = INT_MAX;
        rep (i, n0) s += chc0[i];
        rep (i, n0) {
          int t = s - chc0[i];
          mint = min(mint, t);
        }
        rep (i, n0) {
          int t = s - chc0[i];
          if (t == mint) {
            res0 = mint;
            rep (j, n0) memc[v][0][ch0[j]] = (i != j);
          }
        }
      } else {  // Case 1
        assert(n0 == 1);
        int t0 = chc0[0], t1 = INT_MAX;
        if (n1 > 0) {
          t1 = 0;
          rep (i, n1) t1 += chc1[i];
        }
        res0 = min(t0, t1);
        if (t0 < t1) memc[v][0][ch0[0]] = true;
        else rep (i, n1) memc[v][0][ch1[i]] = true;
    }
    }
  }
  { // One
    if (p == -1) { res1 = INT_MIN; goto done; }  // needleess

    int tp = res0 + padj[v].S.S;
    int tc = INT_MAX;

    if (n0 > 0) {
      tc = 0;
      rep (i, n0) tc += chc0[i];
    }
    // printf("<< %d: tp=%d, tc=%d\n", v, tp, tc);
    res1 = min(tp, tc);
    if (tp < tc) {
      memc[v][1] = memc[v][0];
      memp[v][1] = true;
    }
    else rep (i, n0) memc[v][1][ch0[i]] = true;
  }
done:;
  // printf("< %d: %d + (%d, %d)\n", v, base, res0, res1);

  return mp(base + res0, base + res1);
}

vector<int> res;

void restore(int v, int c, int p) {
  if (memp[v][c]) res.pb(padj[v].F.S);
  rep (i, cadj[v].size()) restore(cadj[v][i].F.F, memc[v][c][i], v);
}

int main() {
  while (1 == scanf("%d", &N) && N) {
    rep (i, N) cadj[i].clear();
    rep (i, N - 1) {
      int a, b, c, d;
      scanf("%d%d%d%d", &a, &b, &c, &d);
      --a;
      --b;
      cadj[a].pb(mp(mp(b, i), mp(c, d)));
      cadj[b].pb(mp(mp(a, i), mp(c, d)));
    }

    D = 0;
    diameter(0, -1);
    // printf("%d\n", D);

    pair<int, int> cost = doit(0, -1);
    printf("%d\n", cost.F);

    res.clear();
    restore(0, 0, 0);
    printf("%d\n", (int)res.size());
    rep (i, res.size()) {
      if (i) putchar(' ');
      printf("%d", res[i] + 1);
    }
    puts("");
  }

  return 0;
}
