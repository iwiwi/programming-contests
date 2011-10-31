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

int N, key[100010];
int root;
int par[100010];
int lch[100010];
int rch[100010];

int Q;
pair<int, int> query[100010];



int mi[100010], ma[100010];

void saiki0(int v) {
  if (lch[v] == -1) {
    mi[v] = ma[v] = key[v];
  } else {
    saiki0(lch[v]);
    saiki0(rch[v]);
    mi[v] = mi[lch[v]];
    ma[v] = ma[rch[v]];
  }
}


int branch[100010];
double sum[100010];

void saiki1(int v) {
  if (par[v] == -1) {
    branch[v] = 0;
    sum[v] = 0.0;
  } else {
    branch[v] = branch[par[v]] + 1;
    sum[v] = sum[par[v]];
    if (v == lch[par[v]]) sum[v] += mi[rch[par[v]]];
    else                  sum[v] += ma[lch[par[v]]];
  }

  if (lch[v] != -1) {
    saiki1(lch[v]);
    saiki1(rch[v]);
  }
}


double ans[100010];

void saiki2(int v, int lb, int ub) {
  if (lch[v] != -1) {
    saiki2(lch[v], lb, key[v]);
    saiki2(rch[v], key[v], ub);
  }
  else {
    for (int i = lower_bound(query, query + Q, mp(lb, 0)) - query;
         i < Q && query[i].first < ub;
         ++i) {
      // printf("%d: %d (%f / %d)\n", i, v, sum[v], branch[v]);
      ans[query[i].second] = sum[v] / branch[v];
    }
  }
}


int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) {
      scanf("%d%d", &par[i], &key[i]);
      if (par[i] == -1) root = i;
      else --par[i];
    }

    memset(lch, -1, sizeof(lch));
    memset(rch, -1, sizeof(rch));
    rep (i, N) if (par[i] != -1) {
      int p = par[i];
      if (key[i] < key[p]) lch[p] = i;
      else rch[p] = i;
    }

    scanf("%d", &Q);
    rep (i, Q) {
      scanf("%d", &query[i].first);
      query[i].second = i;
    }
    sort(query, query + Q);

    saiki0(root);
    saiki1(root);
    saiki2(root, INT_MIN, INT_MAX);

    rep (i, Q) printf("%.13f\n", ans[i]);
  }

  return 0;
}

