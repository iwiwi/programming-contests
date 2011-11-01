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

#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>

struct __bench__ {
  double start;
  char msg[100];
  __bench__(const char* format, ...)
  __attribute__((format(printf, 2, 3)))
  {
    va_list args;
    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    start = sec();
  }
  ~__bench__() {
    fprintf(stderr, "%s: %.6f sec\n", msg, sec() - start);
  }
  double sec() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
  }
  operator bool() { return false; }
};

#define benchmark(...) if(__bench__ __b__ = __bench__(__VA_ARGS__));else





const int MAX_N = 200010;

int N, Y[MAX_N];

const int S = 1500;                // the block size
const int MAX_B = MAX_N / S + 10;  // the number of the blocks

int ys[MAX_B][S], ys_n[MAX_B];

void init() {
  for (int b = 0; (b + 1) * S <= N; ++b) {
    int l = b * S, r = (b + 1) * S;
    ys_n[b] = 0;
    for (int i = l; i < r; ++i) ys[b][ys_n[b]++] = Y[i];
    sort(ys[b], ys[b] + ys_n[b]);
  }
}

pair<int, int> query_count(int l, int r, int v) {  // [l, r) -> (smaller than v, other)
  int les = 0, lar = 0;
  {
    int lub = min(r, (l + S - 1) / S * S), b = l / S;
    for (; l < lub; ++l) {
      if (Y[l] != -1) ++(Y[l] < v ? les : lar);
    }
  }
  {
    int rlb = max(l, r / S * S), b = r / S;
    while (r > rlb) {
      --r;
      if (Y[r] != -1) ++(Y[r] < v ? les : lar);
    }
  }
  {
    for (; l < r; l += S) {
      int b = l / S;
      int t = lower_bound(ys[b], ys[b] + ys_n[b], v) - ys[b];
      les += t;
      lar += ys_n[b] - t;
    }
  }
  return mp(les, lar);
}

void query_remove(int p) {
  int y = Y[p];
  {
    // Process position |p|
    Y[p] = -1;
  }
  int b = p / S, l = b * S, r = (b + 1) * S;
  if (r <= N) {
    // Process block |b| = [l, r)

    int i = 0, *a = ys[b];
    for (; a[i] != y; ++i);
    int n = ys_n[b];
    for (; i < n - 1; ++i) a[i] = a[i + 1];
    --ys_n[b];
  }
}


int M;
int pos[1000010];

typedef long long ll;

ll mergecount(vector<int> &a) {
  ll count = 0;
  int n = a.size();
  if (n > 1) {
    vector<int> b(a.begin(), a.begin() + n/2);
    vector<int> c(a.begin() + n/2, a.end());
    count += mergecount(b);
    count += mergecount(c);
    for (int i = 0, j = 0, k = 0; i < n; ++i)
      if (k == c.size())       a[i] = b[j++];
      else if (j == b.size())  a[i] = c[k++];
      else if (b[j] <= c[k])   a[i] = b[j++];
      else                   { a[i] = c[k++]; count += n/2 - j; }
  }
  return count;
}


int main() {
  while (2 == scanf("%d%d", &N, &M)) {
    rep (i, N) {
      int j;
      scanf("%d", &j);
      Y[i] = j;
      pos[j] = i;
    }

    ll crr;
    benchmark("mergecount")
    {
      vector<int> a(Y, Y + N);
      crr = mergecount(a);
    }

    init();

    benchmark("iteration")
    rep (iter, M) {
      printf("%lld\n", crr);

      int j;
      scanf("%d", &j);
      int i = pos[j];

      crr -= query_count(0, i, j).second;
      crr -= query_count(i + 1, N, j).first;

      query_remove(i);
    }
  }

  return 0;
}

