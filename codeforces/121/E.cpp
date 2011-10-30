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

bool isL[10010];
vector<int> L;

void init(ll crr) {
  if (crr > 10000) return;
  if (crr != 0) {
    isL[crr] = true;
    L.pb(crr);
  }
  init(crr * 10 + 4);
  init(crr * 10 + 7);
}


const int MAX_N = 100010;
const int S = 1500;                 // the block size
const int MAX_B = MAX_N / S + 10;  // the number of the blocks

int N, A[MAX_N];
int cnt[MAX_B][10010];
int dif[MAX_B];

void init() {
  memset(cnt, 0, sizeof(cnt));
  memset(dif, 0, sizeof(dif));

  for (int b = 0; (b + 1) * S <= N; ++b) {
    int l = b * S, r = (b + 1) * S;
    // Process block |b| = [l, r)

    for (int i = l; i < r; ++i) ++cnt[b][A[i]];
  }
}

void query_add(int l, int r, int d) {  // [l, r)
  {
    int lub = min(r, (l + S - 1) / S * S), b = l / S;
    for (; l < lub; ++l) {
      // Process position |l| in block |b|

      --cnt[b][A[l]];
      A[l] += d;
      ++cnt[b][A[l]];
    }
  }
  {
    int rlb = max(l, r / S * S), b = r / S;
    while (r > rlb) {
      --r;
      // Process position |r| in block |b|

      --cnt[b][A[r]];
      A[r] += d;
      ++cnt[b][A[r]];
    }
  }
  {
    for (; l < r; l += S) {
      // Process block |b|
      int b = l / S;

      dif[b] += d;
    }
  }
}


int query_count(int l, int r) {  // [l, r)
  int ans = 0;

  {
    int lub = min(r, (l + S - 1) / S * S), b = l / S;
    for (; l < lub; ++l) {
      // Process position |l| in block |b|

      if (isL[dif[b] + A[l]]) ++ans;
    }
  }
  {
    int rlb = max(l, r / S * S), b = r / S;
    while (r > rlb) {
      --r;
      // Process position |r| in block |b|

      if (isL[dif[b] + A[r]]) ++ans;
    }
  }
  {
    for (; l < r; l += S) {
      // Process block |b|
      int b = l / S;

      rep (i, L.size()) {
        int a = L[i] - dif[b];
        if (a >= 0) ans += cnt[b][a];
      }
    }
  }

  return ans;
}

int main() {
  init(0);
  sort(all(L));

  int M;
  while (2 == scanf("%d%d", &N, &M)) {
    rep (i, N) scanf("%d", &A[i]);
    init();

    char buf[256];
    int l, r;
    rep (i, M) {
      scanf("%s%d%d", buf, &l, &r);
      --l;  // [l, r) ... 0-indexed

      if (buf[0] == 'c') {
        printf("%d\n", query_count(l, r));
      } else {
        int d;
        scanf("%d", &d);
        query_add(l, r, d);
      }
    }
  }

  return 0;
}

