#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <set>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define mp make_pair



int main() {
  for (int ca = 1; ; ++ca) {
    int H, W;

    char buf[1024];
    if (gets(buf) == NULL) return 0;
    if (2 != sscanf(buf, "%d%d", &H, &W)) return 0;

    vector<string> F(H);
    rep (y, H) getline(cin, F[y]);

    int K;
    gets(buf);
    sscanf(buf, "%d", &K);

    vector<string> S = F;
    rep (k, K - 1) {
      vector<string> T(S.size() * H, string(S[0].length() * W, ' '));

      rep (y, H) rep (x, W) {
        if (F[y][x] == ' ') continue;
        int ty = y * S.size();
        int tx = x * S[0].length();
        rep (dy, S.size()) rep (dx, S[0].length()) {
          T[ty + dy][tx + dx] = S[dy][dx];
        }
      }

      S = T;
      // printf("%d x %d\n", int(S.size()), int(S[0].length()));
    }

    if (ca > 1) puts("");
    printf("Fractal #%d:\n", ca);
    rep (y, S.size()) {
      string s = S[y];

      int pos = s.length();
      while (pos >= 1 && s[pos - 1] == ' ') --pos;
      s = s.substr(0, pos);

      // while (!s.empty() && s[s.length() - 1] == ' ') s = s.substr(0, s.length() - 1);
      printf("%s\n", s.c_str());
    }
  }
}
