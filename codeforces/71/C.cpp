#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

string S;
int N;
vector<string> B;

int main() {
  while (cin >> S) {
    scanf("%d", &N);
    B.resize(N);
    rep (i, N) cin >> B[i];

    sort(all(B));
    B.erase(unique(all(B)), B.end());
    N = B.size();

    vector<bool> die(N, false);
    rep (i, N) rep (j, N) if (i != j) {
      if (B[i].length() < B[j].length()) {
        for (int k = 0; k + B[i].length() <= B[j].length(); ++k) {
          if (B[i] == B[j].substr(k, B[i].length())) {
            die[j] = true;
          }
        }
      }
    }

    vector<string> C;
    rep (i, N) if (!die[i]) C.pb(B[i]);

    N = C.size();
    // rep (i, N) cout << C[i] << endl;

    int best_pos = 0, best_len = 0;
    int last_bgn = -1;
    int L = S.length();
    for (int p = 0; p < L; ++p) {
      rep (i, N) {
        if (S.compare(p, C[i].length(), C[i].c_str()) == 0) {
          int bgn = p;
          int end = p + C[i].length();
          int len = end - last_bgn - 2;
          if (len > best_len) {
            best_pos = last_bgn + 1;
            best_len = len;
          }
          last_bgn = bgn;
        }
      }
    }

    {
      // TODO: be careful!
      int len = L - last_bgn - 1;
      if (len > best_len) {
        best_pos = last_bgn + 1;
        best_len = len;
      }
    }

    printf("%d %d\n", best_len, best_pos);
  }

  return 0;
}

