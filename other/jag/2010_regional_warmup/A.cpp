#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)

char buf[1000010];

int main() {
  freopen("A.txt", "r", stdin);

  for (;;) {
    int N, Q;
    scanf("%d%d", &N, &Q);
    if (N == 0 && Q == 0) return 0;
    
    vector<string> name(N);
    vector<int> B(N), Y(N);
    rep (i, N) {
      scanf("%s%d%d", buf, &B[i], &Y[i]);
      name[i] = string(buf);
    }
    
    vector<pair<int, int> > v(N);
    rep (i, N) {
      v[i].first = Y[i];
      v[i].second = i;
    }
    
    sort(v.begin(), v.end());

    rep (q, Q) {
      int y;
      scanf("%d", &y);
      
      int i = lower_bound(v.begin(), v.end(), make_pair(y, -1))
        - v.begin();
      if (i == N) goto unk;
      
      {
        int k = v[i].second;
        if (Y[k] - B[k] < y) {
          printf("%s %d\n", name[k].c_str(), y - (Y[k] - B[k]));
          continue;
        }
      }
      
    unk:
      puts("Unknown");
    }
  }
}
