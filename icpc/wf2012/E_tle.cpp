#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cassert>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define mp make_pair
#define pb push_back

#define F first
#define S second

typedef bitset<75> bs_t;

int N;
int adj[80][80];

int best_siz;
vector<int> best_sel;
  
vector<int> sel;
bool ng[80];

bs_t all;
bs_t B[80];

void greedy() {
  int cov[80];
  best_sel.clear();
  memset(cov, 0, sizeof(cov));

  for (;;) {
    rep (i, N) if (cov[i] == 0) goto notyet;
    break;
  notyet:;

    int bc = 0, bi;
    rep (i, N) {
      int c = 0;
      rep (j, N) if (cov[j] == 0)
    }
  }
  
}

void search1() {
  best_siz = sel.size();
  best_sel = sel;
  throw 0;
  
 notyet:
  if ((int)sel.size() + 1 >= best_siz) return;

  vector<pair<int, int> > ord;
  rep (i, N) if (!ng[i]) {
    int c = 0;
    rep (j, N) if (cov[j] == 0 && adj[i][j]) ++c;
    ord.pb(mp(c, i));
  }
  sort(ord.rbegin(), ord.rend());
  // rep (i, ord.size()) printf("%*s%d %d\n", (int)sel.size(), "", ord[i].first, ord[i].second + 1);
  
  rep (i, ord.size()) {
    int k = ord[i].second;
    ng[k] = true;
    sel.pb(k);
    rep (j, N) if (adj[k][j]) ++cov[j];
    search1();
    rep (j, N) if (adj[k][j]) --cov[j];
    sel.pop_back();
  }

  rep (i, ord.size()) ng[ord[i].second] = false;
}


void search2(int start) {
  //printf("sel: "); rep (i, sel.size()) printf("%d ", sel[i]); puts("");
  
  bs_t b;
  rep (i, sel.size()) b |= B[sel[i]];
  if (b == all) {
    best_siz = sel.size();
    best_sel = sel;
    return;
  }
  
  if ((int)sel.size() + 1 >= best_siz) return;
  
  for (int i = start; i < N; ++i) {
    sel.pb(i);
    search2(i + 1);
    sel.pop_back();
  }
}

int main() {
  for (int ca = 1; 1 == scanf("%d", &N); ++ca) {
    printf("Case %d: ", ca);

    rep (i, N) rep (j, N) {
      char c;
      scanf(" %c", &c);
      adj[i][j] = c - '0';
    }
    rep (i, N) adj[i][i] = 1;
    
    rep (i, N) {
      B[i].reset();
      rep (j, N) B[i][j] = adj[i][j];
    }
    rep (i, N) all[i] = true;

    best_siz = 9876;

    try {
      memset(ng, 0, sizeof(ng));
      sel.clear();
      memset(cov, 0, sizeof(cov));
      search1();
    } catch (...) {}

    assert(best_siz <= 6);
        
    memset(ng, 0, sizeof(ng));
    sel.clear();
    memset(cov, 0, sizeof(cov));
    search2(0);

    printf("%d", best_siz);
    sort(best_sel.begin(), best_sel.end());
    rep (i, best_siz) printf(" %d", best_sel[i] + 1);
    puts("");
  }
}

