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

int N;
int A[100010];

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d", &A[i]);
    sort(A, A + N);

    if (count(A, A + N, 1) == N) {
      rep (i, N - 1) printf("1 ");
      puts("2");
    } else {
      rep (i, N) {
        printf("%d%c", i == 0 ? 1 : A[i - 1], i == N - 1 ? '\n' : ' ');
      }
    }
  }

  return 0;
}

