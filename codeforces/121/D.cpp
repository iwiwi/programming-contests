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

const ll MAX = 10 + (ll)1E18;
vector<ll> A;

void init(ll crr) {
  if (crr > MAX) return;
  if (crr != 0) A.pb(crr);
  if (crr * 10.0 + 4 < MAX) init(crr * 10 + 4);
  if (crr * 10.0 + 7 < MAX) init(crr * 10 + 7);
}


int N;
ll K;
ll L[100010], R[100010];

ll readll() {
  ll x;
#ifdef LOCAL
  scanf("%lld", &x);
#else
  scanf("%I64d", &x);
#endif
  return x;
}

ll Lcost[1000010];

ll llmul(ll a, ll b) {
  if (double(a) * double(b) > MAX) return MAX;
  else return a * b;
}

int main() {
  N = readll();
  K = readll();

  init(0);
  sort(all(A));
  // fprintf(stderr, "%lld\n", A.front());
  // fprintf(stderr, "%lld\n", A.back());

  ll min_len = (ll)1E18;
  rep (i, N) {
    L[i] = readll();
    R[i] = readll();
    // [L, R]
    min_len = min(min_len, R[i] - L[i] + 1);
  }

  sort(L, L + N);
  sort(R, R + N);

  {
    ll sum = 0, cnt = 0, prv_p = 0;
    int i = N - 1;
    for (int j = A.size() - 1; j >= 0; --j) {
      ll p = A[j];
      sum += llmul(cnt, prv_p - p);
      sum = min(sum, MAX);

      while (i >= 0 && L[i] > p) {
        sum += L[i] - p;
        sum = min(sum, MAX);

        ++cnt;
        --i;
      }

      Lcost[j] = sum;
      prv_p = p;
    }
  }

  int ans = 0;
  {
    ll sum = 0, cnt = 0, prv_p = 0;
    int i = 0, lj = 0;
    rep (rj, A.size()) {
      ll p = A[rj];

      sum += llmul(cnt, p - prv_p);
      sum = min(sum, MAX);

      while (i < N && R[i] < p) {
        sum += p - R[i];
        sum = min(sum, MAX);

        ++cnt;
        ++i;
      }

      while (lj < rj && A[rj] - A[lj] + 1 > min_len) ++lj;
      while (lj < rj && sum + Lcost[lj] > K) ++lj;

      // printf("[%lld, %lld]: %lld + %lld = %lld\n", A[lj], A[rj], sum, Lcost[lj], sum + Lcost[lj]);

      if (sum + Lcost[lj] <= K) {
        ans = max(ans, rj - lj + 1);
      }
      prv_p = p;
    }
  }

  printf("%d\n", ans);

  return 0;
}

