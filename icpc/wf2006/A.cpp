#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define mp make_pair
#define pb push_back


int NT, NI;
int C[30];
vector<int> T[30];

map<int, int> ma;
int getid(int k) {
  if (ma.count(k)) return ma[k];
  else {
    int r = ma.size();
    return ma[k] = r;
  }
}

int pot[210][30];
int lst[210][30];
pair<int, int> prv[210][30];

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d", &NT);
    if (NT == 0) return 0;
    ma.clear();

    rep (i, NT) {
      int k;
      scanf("%d%d", &C[i], &k);
      T[i].resize(k);
      rep (j, k) {
	scanf("%d", &T[i][j]);
	T[i][j] = getid(T[i][j]);
      }
    }

    scanf("%d", &NI);
    rep (trip, NI) {
      int K;
      scanf("%d", &K);
      vector<int> I(K);
      rep (j, K) {
	scanf("%d", &I[j]);
	I[j] = getid(I[j]);
      }
      
      int V = ma.size();

      multimap<int, pair<int, int> > que;
      rep (v, V) rep (k, K) pot[v][k] = INT_MAX;
      pot[I[0]][0] = 0;
      que.insert(mp(0, mp(I[0], 0)));
      int d, v, k;
      while (!que.empty()) {
	d = que.begin()->first;
	v = que.begin()->second.first;
	k = que.begin()->second.second;
	que.erase(que.begin());
	if (d > pot[v][k]) continue;

	if (k == K - 1) break;

	rep (i, NT) {
	  if (T[i][0] != v) continue;

	  int tk = k;
	  int td = d + C[i];
	  for (int j = 1; j < (int)T[i].size(); ++j) {
	    int tv = T[i][j];
	    if (tk + 1 < K && tv == I[tk + 1]) ++tk;
	    if (td < pot[tv][tk]) {
	      que.insert(mp(td, mp(tv, tk)));
	      pot[tv][tk] = td;
	      lst[tv][tk] = i;
	      prv[tv][tk] = mp(v, k);
	    }
	  }
	}
      }
      printf("Case %d, Trip %d: Cost = %d\n", ca, trip + 1, d);
      
      vector<int> usd;
      while (mp(v, k) != mp(I[0], 0)) {
	usd.pb(lst[v][k]);
	pair<int, int> p = prv[v][k];
	v = p.first;
	k = p.second;
      }
      reverse(usd.begin(), usd.end());
      printf("  Tickets used:");
      rep (i, usd.size()) printf(" %d", usd[i] + 1);
      puts("");
    }
  }
}
