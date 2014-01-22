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

typedef long long ll;

void print_ll(ll x) {
#ifdef LOCAL
  printf("%lld\n", x);
#else
  printf("%I64d\n", x);
#endif
}



const int B = 400;

int N, M, Q;
ll A[100010];
int K[100010];
vector<int> S[100010];

int is_heavy[100010];
vector<int> heavy;
ll heavy_dif[510];  // per one element
ll heavy_sum[510];  // total (not including dif)

bool elem_to_heavy[100010][310];
int set_to_heavy[100010][310];


int main() {
  while (3 == scanf("%d%d%d", &N, &M, &Q)) {
    rep (i, N) {
      int a;
      scanf("%d", &a);
      A[i] = a;
    }
    rep (i, M) {
      S[i].clear();
      scanf("%d", &K[i]);
      S[i].resize(K[i]);
      rep (k, K[i]) {
        scanf("%d", &S[i][k]);
        --S[i][k];
      }
    }

    heavy.clear();
    rep (k, M) {
      if (K[k] > B) {
        is_heavy[k] = heavy.size();
        heavy.pb(k);
      } else {
        is_heavy[k] = -1;
      }
    }
    int H = heavy.size();

    memset(elem_to_heavy, 0, sizeof(elem_to_heavy));
    rep (h, H) {
      int k = heavy[h];
      heavy_sum[h] = 0;
      rep (j, S[k].size()) {
        heavy_sum[h] += A[S[k][j]];
        elem_to_heavy[S[k][j]][h] = true;
      }
    }
    memset(set_to_heavy, 0, sizeof(set_to_heavy));
    rep (k, M) {
      rep (j, S[k].size()) rep (th, H) set_to_heavy[k][th] += elem_to_heavy[S[k][j]][th] ? 1 : 0;
    }

    rep (q, Q) {
      char c;
      int k;
      scanf(" %c%d", &c, &k);
      --k;

      if (c == '?') {
        ll s = 0;
        if (is_heavy[k] != -1) {  // Heavy
          int h = is_heavy[k];
          s = heavy_sum[h];
        }
        else {  // Light
          rep (j, S[k].size()) s += A[S[k][j]];
        }
        rep (th, H) s += set_to_heavy[k][th] * heavy_dif[th];
        print_ll(s);
      }
      else {  // +
        int x;
        scanf("%d", &x);

        if (is_heavy[k] != -1) {  // Heavy
          int h = is_heavy[k];
          heavy_dif[h] += x;
        }
        else {  // Light
          rep (j, S[k].size()) A[S[k][j]] += x;
          rep (th, H) heavy_sum[th] += (ll)set_to_heavy[k][th] * x;
        }
      }
    }
  }

  return 0;
}
