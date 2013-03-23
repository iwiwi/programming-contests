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


int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    if (N % 4 >= 2) {
      puts("-1");
    } else {
      vector<int> a(N);
      a[N / 2] = N / 2;
      for (int i = 0; i < N / 2; i += 2) {
        a[i + 0] = i + 1;
        a[i + 1] = N - 1 - i;
        a[N - 1 - i] = N - 2 - i;
        a[N - 2 - i] = i + 0;
      }

      rep (i, N) printf("%d%c", a[i] + 1, i == N - 1 ? '\n' : ' ');
    }
  }
  return 0;

  for (int n = 1; n <= 10; ++n) {
    vector<int> a(n);
    rep (i, n) a[i] = i;
    do {
      rep (i, n) if (a[a[i]] != n - i - 1) goto dmp;
      printf("%d\n", n);
      break;
   dmp:;
    } while (next_permutation(all(a)));
  }

  return 0;
}

