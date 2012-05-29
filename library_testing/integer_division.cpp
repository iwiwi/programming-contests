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

inline ll absll(ll x) {
  return x >= 0 ? x : -x;
}

ll div_at_most(ll a, ll b) {  // x <= a/b
  return (a < 0) ^ (b < 0) ? -(absll(a) + absll(b) - 1) / absll(b) : absll(a) / absll(b);
}

ll div_at_least(ll a, ll b) {  // a/b <= x
  return (a < 0) ^ (b < 0) ? -absll(a) / absll(b) : (absll(a) + absll(b) - 1) / absll(b);
}

ll div_less(ll a, ll b) {  // x < a/b
  return (a < 0) ^ (b < 0) ? -absll(a) / absll(b) - 1 : (absll(a) + absll(b) - 1) / absll(b) - 1;
}

ll div_more(ll a, ll b) {  // a/b < x
  return (a < 0) ^ (b < 0) ? -(absll(a) + absll(b) - 1) / absll(b) + 1 : absll(a) / absll(b) + 1;
}

#include <gtest/gtest.h>

const int kNumTrial = 100000000;

void normalize_signs(ll &a, ll &b) {
  if (b < 0) {
    a *= -1;
    b *= -1;
  }
}

void test_at_most(ll a, ll b) {
  ll x = div_at_most(a, b);
  normalize_signs(a, b);
  ASSERT_LE(b * x, a)       << a << " / " << b << " -> " << x;
  ASSERT_LT(a, b * (x + 1)) << a << " / " << b << " -> " << x;
}

void test_at_least(ll a, ll b) {
  ll x = div_at_least(a, b);
  normalize_signs(a, b);
  ASSERT_LE(a, b * x)       << a << " / " << b << " -> " << x;
  ASSERT_LT(b * (x - 1), a) << a << " / " << b << " -> " << x;
}

void test_less(ll a, ll b) {
  ll x = div_less(a, b);
  normalize_signs(a, b);
  ASSERT_LT(x * b, a)       << a << " / " << b << " -> " << x;
  ASSERT_LE(a, (x + 1) * b) << a << " / " << b << " -> " << x;
}

void test_more(ll a, ll b) {
  ll x = div_more(a, b);
  normalize_signs(a, b);
  ASSERT_LT(a, x * b)       << a << " / " << b << " -> " << x;
  ASSERT_LE((x - 1) * b, a) << a << " / " << b << " -> " << x;
}

void test_all(ll a, ll b) {
  test_at_most(a, b);
  test_at_least(a, b);
  test_less(a, b);
  test_more(a, b);
}

ll gen_num() {
  return rand() % 20000001 - 10000000;
}

ll gen_den() {
  ll n = rand() % 200000 - 100000;
  if (0 <= n) ++n;
  return n;
}

TEST(all, random_tests) {
  #pragma omp parallel for
  rep (t, kNumTrial) test_all(gen_num(), gen_den());
}

TEST(all, num_zero) {
  #pragma omp parallel for
  rep (t, kNumTrial) test_all(0, gen_den());
}

TEST(all, num_one) {
  #pragma omp parallel for
  rep (t, kNumTrial) test_all(+1, gen_den());
  rep (t, kNumTrial) test_all(-1, gen_den());
}

TEST(all, den_one) {
  #pragma omp parallel for
  rep (t, kNumTrial) test_all(gen_num(), +1);
  rep (t, kNumTrial) test_all(gen_num(), -1);
}

TEST(all, divisible) {
  #pragma omp parallel for
  rep (t, kNumTrial) {
    ll d = gen_den();
    ll n = d * (rand() % 100);
    test_all(n, d);
  }
}

TEST(all, almost_divisible) {
  #pragma omp parallel for
  rep (t, kNumTrial) {
    ll d = gen_den();
    ll n = d * (rand() % 100);
    test_all(n + 1, d);
    test_all(n - 1, d);
  }
}
