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

ll B, D;

vector<pair<int, int> > factorize(int n) {
  vector<pair<int, int> > res;
  for (int i = 2; i * i <= n; i++) {
    int c = 0;
    for (; n % i == 0; n /= i) c++;
    if (c > 0) res.push_back(make_pair(i, c));
  }
  if (n != 1) res.push_back(make_pair(n, 1));
  return res;
}




int main() {
  while (cin >> B >> D) {
    fprintf(stderr, "[%lld, %lld]\n", B, D);
    vector<pair<int, int> > f = factorize(D);

    if ((B - 1) % D == 0) {
      puts("3-type");
      continue;
    }
    if ((B + 1) % D == 0) {
      puts("11-type");
      continue;
    }

    int t2 = false, t3 = false, t11 = false;
    int n2 = 0;

    rep (i, f.size()) {
      int p = f[i].first, q = f[i].second;  // p^q

      ll t = 1;
      rep (j, q) t *= p;

      if (B % f[i].first == 0) {
        t2 = true;

        int c = 0, x = B;
        while (x % p == 0) {
          ++c;
          x /= p;
        }
        n2 = max(n2, q / c + (q % c ? 1 : 0));
      } else if ((B - 1) % t == 0) {
        t3 = true;
      } else if ((B + 1) % t == 0) {
        t11 = true;
      } else {
        goto t7;
      }
    }

    if (t2 + t3 + t11 > 1) puts("6-type");
    else if (t2) {
      puts("2-type");
      printf("%d\n", n2);
    }
    else if (t3) assert(false);
    else if (t11) assert(false);
    else assert(false);

    continue;
 t7:
    puts("7-type");
  }

  return 0;
}

