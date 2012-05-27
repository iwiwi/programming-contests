#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <cassert>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define mp make_pair
#define pb push_back

#define F first
#define S second

typedef long long ll;

const int INF = 100000000;
typedef pair<int, int> pii;
typedef map<int, int> mii;
typedef mii::iterator iter;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, -1, 0, 1};

int sum(int i, int *bit) {
  int s = 0;
  for (; i > 0; i -= i & -i) s += bit[i];
  return s;
}

void add(int i, int v, int *bit, int n) {
  for (; i <= n; i += i & -i) bit[i] += v;
}


iter get_larger(mii &m, int x) {
  return m.upper_bound(x);
}
iter get_smaller(mii &m, int x) {
  iter i = m.lower_bound(x);
  if (i == m.begin()) return m.end();
  else return --i;
}

int H, W, N, M;
map<int, int> mir_yoko[1000010];
map<int, int> mir_tate[1000010];

vector<pair<int, pii> >  seg_tate, seg_yoko;

pii simulate(int y, int x, int d) {
  seg_tate.clear();
  seg_yoko.clear();
  
  for (;;) {
    iter ite;
    switch (d) {
    case 0: ite = get_larger (mir_yoko[y], x); break;
    case 1: ite = get_smaller(mir_tate[x], y); break;
    case 2: ite = get_smaller(mir_yoko[y], x); break;
    case 3: ite = get_larger (mir_tate[x], y); break;
    }

    int tx = x, ty = y;
    if (ite == (d % 2 == 0 ? mir_yoko[y] : mir_tate[x]).end()) {
      switch(d) {
      case 0: tx = W + 1; break;
      case 1: ty = 0;     break;
      case 2: tx = 0;     break;
      case 3: ty = H + 1; break;
      }
      if (d % 2 == 0) { seg_yoko.pb(mp(y, mp(min(x, tx), max(x, tx)))); }
      else            { seg_tate.pb(mp(x, mp(min(y, ty), max(y, ty)))); }
      return mp(ty, tx);
    }
    else {
      if (d % 2 == 0) { tx = ite->first; seg_yoko.pb(mp(y, mp(min(x, tx), max(x, tx)))); }
      else            { ty = ite->first; seg_tate.pb(mp(x, mp(min(y, ty), max(y, ty)))); }

      // printf(" %d\n", ite->second);
      
      d = (d + ite->second + 4) % 4;
      y = ty;
      x = tx;
    }

    // printf("sim %d %d %d\n", y, x, d);
  }
}


vector<pair<int, pii> > segs_tate[2], segs_yoko[2];
vector<pair<int, pair<int, int> > > evt_tate[1000010];
vector<pair<pii, int> > evt_yoko[1000010];
int bit[2][1000010], has[2][1000010];

void process_evt_tate(int y, int sign) {
  rep (i, evt_tate[y].size()) {
    pair<int, pair<int, int> > e = evt_tate[y][i];
    
    if (e.S.S != sign) continue;
    add(e.F, sign, bit[e.S.F], H + 1);
    has[e.S.F][e.F] += sign;
  }
}

int main() {
  for (int ca = 1; 4 == scanf("%d%d%d%d", &H, &W, &M, &N); ++ca) {
    printf("Case %d: ", ca);
    
    for (int y = 0; y <= H + 1; ++y) mir_yoko[y].clear();
    for (int x = 0; x <= W + 1; ++x) mir_tate[x].clear();

    rep (i, M + N) {
      int y, x;
      scanf("%d%d", &y, &x);
      // printf(" %d %d %d\n", y, x, i < M);
      mir_yoko[y][x] = i < M ? +1 : -1;
      mir_tate[x][y] = i < M ? -1 : +1;
    }

    seg_tate.clear();
    seg_yoko.clear();
    pii res = simulate(1, 0, 0);
    segs_tate[0].swap(seg_tate);
    segs_yoko[0].swap(seg_yoko);
    
    // printf("-> %d %d\n", res.first, res.second);
    if (res == mp(H, W + 1)) {
      puts("0");
      continue;
    }
    
    simulate(H, W + 1, 2);
    segs_tate[1].swap(seg_tate);
    segs_yoko[1].swap(seg_yoko);
    
    for (int x = 0; x <= W + 1; ++x) evt_tate[x].clear();
    for (int y = 0; y <= H + 1; ++y) evt_yoko[y].clear();
    rep (i, 2) rep (j, segs_yoko[i].size()) evt_yoko[segs_yoko[i][j].F].pb(mp(segs_yoko[i][j].S, i));
    rep (i, 2) rep (j, segs_tate[i].size()) {
      assert(segs_tate[i][j].S.F < segs_tate[i][j].S.S);
      assert(0 <= segs_tate[i][j].S.F);
      assert(segs_tate[i][j].S.S <= H + 1);
      evt_tate[segs_tate[i][j].S.F].pb(mp(segs_tate[i][j].F, mp(i, +1)));
      evt_tate[segs_tate[i][j].S.S].pb(mp(segs_tate[i][j].F, mp(i, -1)));
    }

    ll ans = 0;
    pii pos(-1, -1);
    memset(bit, 0, sizeof(bit));
    memset(has, 0, sizeof(has));
    for (int y = 0; y <= H + 1; ++y) {
      process_evt_tate(y, -1);

      rep (i, evt_yoko[y].size()) {
	int x0 = evt_yoko[y][i].F.F;
	int x1 = evt_yoko[y][i].F.S;
	int k = evt_yoko[y][i].S;

	// printf("[%d] tate %d: (%d, %d)\n", y, k, x0, x1);
	// assert(x1 > x0);
	ll get = sum(x1 - 1, bit[1 - k]) - sum(x0, bit[1 - k]);
	// assert(get >= 0);
	
	// ll get2 = 0;
	// for (int x = x0 + 1; x < x1; ++x) get2 +=  has[1 - k][x];
	// assert(get == get2);
	
	if (ans == 0 && get > 0) {
	  for (int x = x0; x <= x1; ++x) {
	    if (has[1 - k][x]) {
	      pos = mp(y, x);
	      break;
	    }
	  }
	}
	ans += get;
      }
      
      process_evt_tate(y, +1);
    }


    if (ans == 0) puts("impossible");
    else {
      // assert(pos != mp(-1, -1));
      printf("%lld %d %d\n", ans, pos.first, pos.second);
    }
  }
}

