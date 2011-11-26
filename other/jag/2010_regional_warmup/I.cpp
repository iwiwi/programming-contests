#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <complex>
#include <iostream>
#include <queue>
#include <set>
#include <cassert>

using namespace std;

const int INF = 987654321;

typedef long long ll;
typedef complex<double> p_t;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back
#define mp make_pair

int N, T;
int M[1010];
int L[1010];
int K[1010];

bool calling[1010][1010];
bool done[1010];
int last[1010];

bool vis[1010];
bool ans[1010];

bool doit(int x) {
  memset(last, 0, sizeof(last));
  memset(done, 0, sizeof(done));
  int cov = 0;
  
  rep (t, T) {
    bool *cal = calling[t];
    
    int i = 0;
    rep (j, x) if (last[j] <= t) {
      // printf(" t = %d, j=%d\n", t, j);
      for (; i < N; ++i) if (!done[i] && cal[i]) break;
      if (i == N) break;
      // printf(" t=%d, %d-%d: %d\n", t, j, i, last[j]);

      last[j] = t + M[i];
      if (last[j] > T) return false;

      done[i] = true;
      if (++cov == N) return true;
    }
  }

  return false;
}


int main() {
  freopen("I.txt", "r", stdin);
  
  for (;;) {
    scanf("%d%d", &N, &T);
    if (N == 0 && T == 0) return 0;
    rep (i, N) scanf("%d%d%d", M + i, L + i, K + i);

    rep (i, N) {
      rep (t, T) calling[t][i] = (t % (L[i] + K[i])) <= L[i];
    }

    // for (int x = 1; x <= N; ++x) printf("%d: %d\n", x, doit(x));
    
    memset(vis, 0, sizeof(vis));

    int lb = 0, ub = N;
    while (ub - lb > 1) {
      int x = (lb + ub) / 2;

      vis[x] = true;
      ans[x] = doit(x);
      
      if (ans[x]) ub = x;
      else lb = x;
    }

    int res = ub;
    for (int i = 1; i <= 100; ++i) {
      int x = ub - i;
      if (x < 1) break;
      if (!vis[x]) {
        vis[x] = true;
        ans[x] = doit(x);
      }
      if (ans[x]) res = x;
    }
    
    printf("%d\n", res);
  }
}
