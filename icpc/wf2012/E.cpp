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

typedef bitset<80> bs_t;

int N;
int adj[80][80];

bs_t all;
bs_t B[80];

int best_siz;
vector<int> best_sel;

void greedy() {
  int cov[80];
  best_sel.clear();
  memset(cov, 0, sizeof(cov));

  for (;;) {
    rep (i, N) if (cov[i] == 0) goto notyet;
    break;
  notyet:;
    int bc = 0, bi = -1;
    rep (i, N) {
      int c = 0;
      rep (j, N) if (cov[j] == 0) c += adj[i][j];
      if (c > bc) {
	bc = c;
	bi = i;
      }
    }
    best_sel.pb(bi);
    rep (j, N) cov[j] += adj[bi][j];
  }

  best_siz = best_sel.size();
}


vector<int> sel;

void search2(int start) {
  //printf("sel: "); rep (i, sel.size()) printf("%d ", sel[i]); puts("");
  
  bs_t b;
  rep (i, sel.size()) b |= B[sel[i]];
  if (b == all && (int)sel.size()<best_siz) {
    best_siz = sel.size();
    best_sel = sel;
    return;
  }
  
  if ((int)sel.size() + 1 >= best_siz) return;
  //if(sel.size()>=5)return;
  //if(sel.size()<5){
  for (int i = start; i < N; ++i) {
    sel.pb(i);
    search2(i + 1);
    sel.pop_back();
  }
  //}
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
    all.reset();
    rep (i, N) all[i] = true;

    greedy();
    //fprintf(stderr,"best_siz=%d\n",best_siz);
    assert(best_siz <= 6);
        
    sel.clear();
    search2(0);

    printf("%d", best_siz);
    sort(best_sel.begin(), best_sel.end());
    rep (i, best_siz) printf(" %d", best_sel[i] + 1);
    puts("");
  }
}

