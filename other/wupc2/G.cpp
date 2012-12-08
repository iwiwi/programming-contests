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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

int N, M, H, K;


const int MAX_N = 200000;

int n;
ll dat[4 * MAX_N];

void init(int n_) {
  for (n = 1; n < n_; n *= 2);
  fill(dat, dat + 2 * n - 1, 0LL);
}

void update(int k, ll a) {
  k += n - 1;
  dat[k] = a;
  while (k > 0) {
    k = (k - 1) / 2;
    dat[k] = dat[k * 2 + 1] + dat[k * 2 + 2];
  }
}

void challenge(ll y) {
  int k = 0, l = 0, r = n;

  ll s = 0;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (y < s + dat[k * 2 + 1]) {
      k = k * 2 + 1;
      r = m;
    } else {
      s += dat[k * 2 + 1];
      k = k * 2 + 2;
      l = m;
    }
  }


  ll dy = dat[k];
  // printf("y = %lld, s = %lld, dy = %lld\n", y, s, dy);

  k -= n - 1;
  if (dy > 0 && (y + 2*H <= s + dy || s == dat[0] - dy)) {
    puts("go");
    update(k, 0);
  } else if (s == dat[0]) {
    puts("miss");
  } else {
    puts("stop");
  }
}


int main() {
  while (3 == scanf("%d%d%d", &N, &M, &H)) {
    init(N + M);
    K = 0;
    rep (i, N) {
      ll a;
      scanf("%lld", &a);
      update(K++, a);
    }

    char q[256];
    ll a;
    rep (i, M) {
      scanf("%s%lld", q, &a);
      if (q[0] == 'c') {
        // Challenge
        challenge(a - H);
      } else {
        // Add
        update(K++, a);
      }
    }
  }

  return 0;
}

