#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <climits>
#include <set>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

int N, M;
int T[10];

int A[1010], B[1010], C[1010];

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d%d", &N, &M);
    if (N == 0 && M == 0) return 0;

    rep (i, N) scanf("%d", &T[i]);
    rep (i, M) {
      scanf("%d%d%d", A + i, B + i, C + i);
      --A[i];
      --B[i];
    }

    int ans = INT_MAX;
    vector<int> ord(N);
    rep (i, N) ord[i] = i;
    
    do {
      bool done[10] = {0};
      set<pair<int, int> > se;
      int ma = 0;
      rep (i, N) {
        int ta = ord[i];
        int cb = 0, th = 0;
        rep (j, M) {
          int a = A[j];
          if (done[a]) continue;
          else if (a != ta) {
            cb += C[j] - B[j];
            ma = max(ma, cb);
            continue;
          }

          int b = B[j];
          if (b > th) {
            se.insert(make_pair(b, j));
            cb += C[j] - B[j];
            ma = max(ma, cb);
            continue;
          }
          else {
            th = C[j];
            while (!se.empty() && se.begin()->first == th) {
              int k = se.begin()->second;
              th = C[k];
              cb -= C[k] - B[k];
              se.erase(se.begin());
            }
            if (th == T[ta]) break;
          }
        }
        done[ta] = true;
      }
      
      ans = min(ans, ma);
    } while (next_permutation(ord.begin(), ord.end()));
    
    printf("Case %d: %d\n\n", ca, ans);
  }
}
