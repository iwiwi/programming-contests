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
    deque<int> A(N);
    rep (i, N) A[i] = i + 1;

    for (int k = 2; k <= N; ++k) {
      int x = A.front();
      for (int i = k; i < N; i += k) swap(x, A[i]);
      A.pop_front();
      A.push_back(x);
    }
    rep (i, N) printf("%d%c", A[i], i + 1 == N ? '\n' : ' ');
  }
  return 0;
}

