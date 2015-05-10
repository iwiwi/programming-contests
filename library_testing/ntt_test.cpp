#include <vector>
#include <cassert>
#include "gtest/gtest.h"
#include <iostream>
using namespace std;

namespace {
#include "ntt.h"
}

#include <iostream>
typedef long long ll;

#include <sys/time.h>

struct __bench__ {
  double start;
  __bench__() {
    start = sec();
  }
  ~__bench__() {
    fprintf(stderr, "%.6f sec\n", sec() - start);
  }
  double sec() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
  }
  operator bool() { return false; }
};

#define benchmark if ( __bench__ __b__ = __bench__()); else

TEST(ntt, trivial) {
  vector<ll> a = {1, 2, 3, 4, 5};
  vector<ll> b = {1, 2, 3, 4, 5};
  a = mod_convolution(a, b, 10);

  for (auto x : a) cout << x << " ";
  cout << endl;
}

TEST(ntt, random) {
  for (int i = 0; i < 10; ++i) {
    ll m = 1 + (ll)rand() % 100000000;
    vector<ll> a(1 + rand() % 1000000);
    vector<ll> b(1 + rand() % 1000000);

    printf("[%d] %lu * %lu mod %lld\n", i, a.size(), b.size(), m);

    for (auto &x : a) x = rand() % m;
    for (auto &x : b) x = rand() % m;
    vector<ll> c;
    benchmark {
      c = mod_convolution(a, b, m);
    }

    // for (auto x : a) printf("%lld ", x); puts("");
    // for (auto x : b) printf("%lld ", x); puts("");
    // for (auto x : c) printf("%lld ", x); puts("");

    int an = a.size(), bn = b.size();
    for (int trial = 0; trial < 300; ++trial) {
      int i = rand() % c.size();

      ll x = 0;
      for (int j = 0; j <= i; ++j) {
        int k = i - j;
        if (j < an && k < bn) (x += a[j] * b[k]) %= m;
      }
      ASSERT_EQ(x, c[i]) << trial << " " << i;
    }
  }
}
