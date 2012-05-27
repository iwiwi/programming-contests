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

#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>

using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

double sec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}



int N, M, K;
int A[30], B[30];

bool ng[30][30];

int main() {
  while (3 == scanf("%d%d%d", &N, &M, &K)) {
    double start = sec();
    rep (i, M) scanf("%d%d", &A[i], &B[i]);

    memset(ng, 0, sizeof(ng));
    rep (i, M) ng[A[i]][B[i]] = ng[B[i]][A[i]] = true;

    long long num = 0, den = 0;
    while (sec() - start < 9.0) {
      rep (iter, 1000) {
        int ord[30];
        rep (i, N) ord[i] = i;

        rep (i, K) {
          int a = rand() % N;
          int b = rand() % (N - 1);

          if (a <= b) ++b;
          swap(ord[a], ord[b]);
        }

        rep (i, N - 1) if (ng[ord[i]][ord[i + 1]]) goto dmp;
        if (ng[ord[N - 1]][ord[0]]) goto dmp;
        ++num;
     dmp:;
        ++den;
      }
    }

    fprintf(stderr, "iter: %lld\n", den);

    printf("%.20f\n", num / (double)den);
  }

  return 0;
}

