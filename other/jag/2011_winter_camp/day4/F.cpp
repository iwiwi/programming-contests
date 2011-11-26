#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back

const double INF = 1E10;
const double EPS = 1E-10;

int N, K;
double R;
int S[5], T[5];
vector<int> ord;

int X[110], Y[110];
double dist[110][110];

int sqr(int x) { return x * x; }

void saiki(int step) {
  int k = ord[step];
  
  int pot[110], prv[110];
  rep (i, N) pot[i] = INF;
  multimap<double, int> que;
  pot[S[k]] = 0.0;
  que.insert(make_pair(0, S[k]));
  while (!que.empty()) {
    double c = que.begin()->first;
    int v = que.begin()->second;
    que.erase(que.begin());
    if (c > pot[v]) continue;
    if (c == T[k]) break;

    rep (w, N) {
      double tc = c + dist[v][w];
      if (tc < pot[w]) {
        
      }
    }
  }
}

int main() {
  scanf("%d%d%lf", &N, &K, &R);
  rep (i, K) { scanf("%d", S + i); --S[i]; }
  rep (i, K) { scanf("%d", T + i); --T[i]; }
  rep (i, N) scanf("%d%d", &X[i], &Y[i]);

  rep (i, N) rep (j, N) {
    if (Y[i] > Y[j]) dist[i][j] = INF;
    else dist[i][j] = sqrt(sqr(X[j] - X[i]) + sqr(Y[j] - Y[i]));
  }
  
  ord.resize(K);
  rep (i, K) ord[i] = i;
  do {
    saiki(0);
  } while (next_permutation(ord.begin(), ord.end()));
  
  return 0;
}
