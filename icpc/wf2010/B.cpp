#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define iter(c) __typeof((c).begin())
#define all(c) (c).begin(), (c).end()
#define mp make_pair
#define pb push_back

typedef long long ll;

const double EPS = 1E-9;

enum ERR {
  ERR_BAD_CODE = 0,
  ERR_BAD_C = 1,
  ERR_BAD_K = 2,
};

int N, A[160];

double X1, X2;
char enc[160];

void decide_x() {
  double d = A[5] * 1.5;
  double ma = -1E30, mi = 1E30;
  rep (i, N) {
    double t = A[i];
    if (t > d) t /= 2.0;
    ma = max(ma, t);
    mi = min(mi, t);
  }

  if (ma > mi / 0.95 * 1.05 + EPS) throw ERR_BAD_CODE;
  else {
    X1 = (mi / 0.95 + ma / 1.05) / 2.0;
    X2 = X1 * 2;
  }

  // double xub = mi * 100.0 /  95.0;
  // double xlb = ma * 100.0 / 105.0 / 2.0;
  // if (xub + EPS < xlb) throw ERR_BAD_CODE;
  // X1 = (xlb + xub) / 2.0;
  // X2 = X1 * 2;

  // printf("%f %f\n", xlb, xub);
}

void decode() {
  rep (i, N) {
    double a = A[i];
    /***/if (X1 * 0.95 - EPS <= a && a <= X1 * 1.05 + EPS) enc[i] = '0';
    else if (X2 * 0.95 - EPS <= a && a <= X2 * 1.05 + EPS) enc[i] = '1';
    else throw ERR_BAD_CODE;
  }
}

const char *codes[] = {
  "00001",
  "10001",
  "01001",
  "11000",
  "00101",
  "10100",
  "01100",
  "00011",
  "10010",
  "10000",
  "00100",
  "00110",
};
const int codes_n = sizeof(codes) / sizeof(codes[0]);

int read_char(int p) {
  rep (i, codes_n) {
    if (strncmp(enc + p, codes[i], 5) == 0) {
      if (p + 5 >= N || enc[p + 5] == '0') return i;
      else throw ERR_BAD_CODE;  // bad separate character
    }
  }
  throw ERR_BAD_CODE;  // unknown encoding
}

void read() {
  if ((N + 1) % 6 != 0) throw ERR_BAD_CODE;

  decide_x();
  decode();

  vector<int> res;
  for (int p = 0; p < N; p += 6) res.pb(read_char(p));

  if (res.size() <= 4) throw ERR_BAD_CODE;  // too short
  if (res.front() != 11 || res.back() != 11) throw ERR_BAD_CODE;  // start/stop

  int K = res.size() - 4;
  for (int i = 1; i <= K; ++i) if (res[i] == 11) throw ERR_BAD_CODE;  // normal characters

  // C
  int c = 0;
  for (int i = 1; i <= K; ++i) (c += ((K - i) % 10 + 1) * res[i]) %= 11;
  c %= 11;
  if (res[K + 1] != c) throw ERR_BAD_C;

  // K
  int k = 0;
  for (int i = 1; i <= K + 1; ++i) (k += ((K - i + 1) % 9 + 1) * res[i]) %= 11;
  k %= 11;
  if (res[K + 2] != k) throw ERR_BAD_K;

  for (int i = 1; i <= K; ++i) printf("%c", res[i] < 10 ? '0' + res[i] : '-'); puts("");
}

int main() {
  for (int ca = 0; ; ++ca) {
    scanf("%d", &N);
    if (N == 0) return 0;
    rep (i, N) scanf("%d", A + i);

    printf("Case %d: ", ca + 1);

    int err = -1;
    rep (iter, 2) {
      try {
        read();
        goto done;  // ok!!
      } catch (ERR e) {
        // if (X1 == 10) printf(" %d\n", (int)e);
        err = max(err, (int)e);
        reverse(A, A + N);
        continue;
      }
    }

    if (err == ERR_BAD_K) puts("bad K");
    else if (err == ERR_BAD_C) puts("bad C");
    else puts("bad code");

 done:;
  }
}
