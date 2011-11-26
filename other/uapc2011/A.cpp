#include <cstdio>

#define rep(i, n) for (int i = 0; i < (int)n; ++i)

void print(const char *s, int ok, int to) {
  if (to > 0) printf("%s %d\n", s, ok * 100 / to);
  else printf("%s no guest\n", s);
}

int main() {
  int N;
  while (1 == scanf("%d", &N) && N > 0) {
    int okl = 0, okd = 0, okm = 0;
    int tol = 0, tod = 0, tom = 0;
    rep (i, N) {
      int h, m, M;
      scanf("%d:%d %d", &h, &m, &M);
      int t = M - m;
      if (t < 0) t += 60;

      if (11 <= h && h < 15) { ++tol; okl += !!(t <= 8); }
      if (18 <= h && h < 21) { ++tod; okd += !!(t <= 8); }
      if (21 <= h || h <  2) { ++tom; okm += !!(t <= 8); }
    }
    print("lunch", okl, tol);
    print("dinner", okd, tod);
    print("midnight", okm, tom);
  }
}
