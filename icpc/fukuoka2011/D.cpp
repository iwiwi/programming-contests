#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <map>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define pb push_back
#define mp make_pair
#define F first
#define S second

const int dx[8]={1,1,1,0,-1,-1,-1,0};
const int dy[8]={1,0,-1,-1,-1,0,1,1};

int lpg[310];

int V;
vector<pair<int, int> > adj[6010];
int mat[310][310];

vector<int> dijkstra(int s) {
  vector<int> pot(V, INT_MAX);
  multimap<int, int> que;
  pot[s] = 0;
  que.insert(mp(0, s));

  while (!que.empty()) {
    int p = que.begin()->first;
    int v = que.begin()->second;
    que.erase(que.begin());
    if (p > pot[v]) continue;

    rep (i, adj[v].size()) {
      int tv = adj[v][i].first;
      int tp = p + adj[v][i].second;
      if (tp < pot[tv]) {
	pot[tv] = tp;
	que.insert(mp(tp, tv));
      }
    }
  }

  return pot;
}

map<string, int> name2id;
int getid(const string &s) {
  int id;
  if (name2id.count(s)) return name2id[s];
  else {
    id = name2id.size();
    adj[id].clear();
  }
  return name2id[s] = id;
}



int main() {
  for (;;) {
    int N, M, cap;
    name2id.clear();
    
    scanf("%d%d%d", &N, &M, &cap);
    if (N == 0 && M == 0 && cap == 0) return 0;
    cap *= 10;

    string src, dst;
    cin >> src >> dst;
    int S = getid(src);
    int T = getid(dst);

    rep (i, N) {
      string a, b;
      int c;
      cin >> a >> b >> c;
      adj[getid(a)].pb(mp(getid(b), c));
      adj[getid(b)].pb(mp(getid(a), c));
    }

    rep (i, M) {
      string a;
      cin >> a;
      lpg[i] = getid(a);
    }
    lpg[M++] = S;
    lpg[M++] = T;
    
    V = name2id.size();

    rep (i, M) {
      vector<int> t = dijkstra(lpg[i]);
      rep (j, M) {
	mat[i][j] = t[lpg[j]];
	if (mat[i][j] > cap) mat[i][j] = -1;
      }
    }

    rep (k, M) rep (i, M) rep (j, M) {
      if (mat[i][k] == -1 || mat[k][j] == -1) continue;
      int t = mat[i][k] + mat[k][j];
      if (mat[i][j] == -1 || t < mat[i][j]) mat[i][j] = t;
    }

    printf("%d\n", mat[M - 2][M - 1]);
  }
}
