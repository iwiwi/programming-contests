#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)

const int W = 7 * 24 * 60;

bool ovr(int t, int s) {
  t = (t % W + W) % W;
  s = (s % W + W) % W;
  if (t > s) swap(t, s);
  if (t + 30 > s) return true;
  if (s + 30 > t + W) return true;
  return false;
}

int main() {
  int N;
  while (cin >> N && N > 0) {
    map<string, int> prg;
    rep (i, N) {
      string name;
      int w, s;
      cin >> name >> w >> s;
      prg[name] = ((w * 24 + s / 100) * 60 + (s % 100)) % W;
    }

    int P;
    cin >> P;
    vector<int> fav(P);
    rep (i, P) {
      string name;
      cin >> name;
      fav[i] = prg[name];
      prg.erase(name);
    }

    sort(fav.begin(), fav.end());
    rep (i, P) rep (j, P) if (i != j) {
      if (ovr(fav[i], fav[j])) goto ng;
    }

    {
      deque<int> sel;
      tr (prg, ite) {
        int t = ite->second;
        rep (i, P) if (ovr(fav[i], t)) goto dmp;
        sel.push_back(t);
     dmp:;
      }

      sort(sel.begin(), sel.end());
      int K = sel.size();
      int ans = 0;
      rep (k, K) {
        int bgn = sel[0], lst = sel[0];
        int tmp = 1;
        for (int i = 1; i < K; ++i) {
          if (!ovr(bgn, sel[i]) && !ovr(lst, sel[i])) {
            ++tmp;
            lst = sel[i];
          }
        }
        ans = max(ans, tmp);

        sel.push_back(sel.front() + W);
        sel.pop_front();
      }

      printf("%d\n", ans + P);
    }

    continue;
 ng:
    puts("-1");
  }
}
