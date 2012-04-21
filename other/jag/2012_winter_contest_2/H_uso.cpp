#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair
#define pb push_back

int V;
int wgh[110][110];

int main() {
  for (int ca = 1; ; ++ca) {
    int N, H;
    scanf("%d%d", &N, &H);
    if (N == 0) return 0;

    V = N + 1;
    for (int i = 1; i <= N; ++i) {
      int b;
      scanf("%d", &b);
      wgh[0][i] = wgh[i][0] = b;
    }
    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= N; ++j) {
        int c;
        scanf("%d", &c);
        wgh[i][j] = wgh[j][i] = c;
      }
    }

    double ans = 1E30;
    vector<int> ans_high;
    
    int i, j, a, b, c;
    vector<int> v(V), p(V);
    vector<vector<int> > vv(V);
    
    rep (i, V) vv[v[i] = i].pb(i);
    
    for (int n = V; n > 1; --n) {
      p[0] = 1;
      for (int i = 1; i < n; ++i) p[i] = 0;

      rep (i, n) {
        b = a;
        a = max_element(p.begin(), p.end()) - p.begin();
        c = p[a];
        p[a] = -1;
        rep (j, n) if (p[j] >= 0) p[j] += wgh[v[a]][v[j]];
      }
      
      {
        // printf("n = %d: %d (%d - %d)\n", n, c, v[b], v[a]);
        // rep (j, vv[v[a]].size()) printf(" %d", vv[v[a]][j]);
        // puts("");

        int k = vv[v[a]].size();
        double tmp = c * double(H) / k;
        if (tmp < ans) {
          ans = tmp;
          ans_high = vv[v[a]];
        }
      }

      rep (i, n) {
        wgh[v[i]][v[b]] += wgh[v[i]][v[a]];
        wgh[v[b]][v[i]] += wgh[v[a]][v[i]];
      }
      vv[v[b]].insert(vv[v[b]].end(), vv[v[a]].begin(), vv[v[a]].end());
      v.erase(v.begin() + a);
    }
    
    printf("Case %d:\n", ca);
    {
      int k = ans_high.size();
      double h = H / double(k);
      for (int i = 1; i <= N; ++i) {
        if (find(ans_high.begin(), ans_high.end(), i) != ans_high.end()) {
          printf("%.15f", h);
        } else {
          printf("0");
        }
        printf("%c", i == N ? '\n' : ' ');        
      }
    }
  }
}
