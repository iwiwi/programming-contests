#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <climits>
#include <list>
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair
#define pb push_back

vector<pair<int, int> > adj[300];
bool usd[1000010];

void euler_rec(int v, list<int> &res, const list<int>::iterator &ite) {
  rep (i, adj[v].size()) {
    int w = adj[v][i].first, e = adj[v][i].second;
    if (usd[e]) continue;
    usd[e] = true;
    list<int>::iterator ite2 = res.insert(ite, w);
    euler_rec(w, res, ite2);
  }
}

void euler(int v, list<int> &res) {
  res.clear();
  res.insert(res.begin(), v);
  memset(usd, 0, sizeof(usd));
  euler_rec(v, res, res.begin());
  reverse(res.begin(), res.end());
}

string S;
int mat[300][300];

void print(list<int> &l) {
  list<int>::iterator ite = l.begin();
  for (; ite != l.end(); ++ite) printf("%c ", char(*ite));
  puts("");
}

int main() {
  for (;;) {
    cin >> S;
    if (S == "#") return 0;
    int N = S.length();

    if (N <= 2) {
      puts("No Results");
      continue;
    }

    memset(mat, 0, sizeof(mat));
    for (int i = 0; i + 1 < N; ++i) {
      mat[S[i]][S[i + 1]] = 1;
    }

    // Outdeg - Indeg
    vector<pair<int, int> > pos, neg;
    rep (c, 256) {
      int d = 0;
      rep (tc, 256) d += mat[c][tc];
      rep (tc, 256) d -= mat[tc][c];
      if (d > 0) pos.pb(mp(c, d));
      if (d < 0) neg.pb(mp(c, -d));
    }

    bool multiple = false;
    int cost = 1;
    rep (c, 256) rep (tc, 256) cost += mat[c][tc];
    // fprintf(stderr, "initial cost: %d\n", cost);

    {
      // Compute |cost|
      int s = 0;
      rep (i, pos.size()) s += pos[i].second;
      if (s > 0) cost += s - 1;  // We can leave one point as a starting (or goal) point
    }

    if (pos.size() == 0 && neg.size() == 0) {
      // fprintf(stderr, "type 0-0\n");

      // "aaaaaaa" ? -> actually no, but OK (because the cost is lower)
      // otherwise   -> we can choose the starting point!
      multiple = true;
    } else if (pos.size() > 1 || neg.size() > 1) {
      // we can choose the edges
      multiple = true;
    } else {
      // fprintf(stderr, "type 1-1\n");

      // pos.size() == 1 && neg.size() == 1
      int sv = pos[0].first;
      int gv = neg[0].first;
      while (pos[0].second > 1) {
        ++mat[gv][sv];
        --pos[0].second;
        --neg[0].second;
      }

      list<int> euler1, euler2;

      int E = 0;
      rep (c, 256) {
        adj[c].clear();
        rep (tc, 256) {
          while (mat[c][tc] > 0) {
            adj[c].pb(mp(tc, E++));
            --mat[c][tc];
          }
        }
      }

      euler(sv, euler1);
      rep (c, 256) reverse(adj[c].begin(), adj[c].end());
      euler(sv, euler2);

      // print(euler1);
      // print(euler2);
      multiple = euler1 != euler2;
    }

    if (cost < N) printf("%d\n", cost);
    else if (multiple) printf("%d\n", N);
    else printf("%d\n", N + 1);
    // printf("%d %d\n", cost, multiple);
  }
}
