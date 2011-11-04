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

const int MAX_N = 1000000;

int par[MAX_N], rank[MAX_N];

void init(int n) {
  for (int i = 0; i < n; i++) {
    par[i] = i;
    rank[i] = 0;
  }
}

int root(int x) {
  return par[x] == x ? x : par[x] = root(par[x]);
}

void unite(int x, int y) {
  x = root(x);
  y = root(y);
  if (x == y) return;

  if (rank[x] < rank[y]) {
    par[x] = y;
  } else {
    par[y] = x;
    if (rank[x] == rank[y]) rank[x]++;
  }
}

bool find(int x, int y) {
  return root(x) == root(y);
}



bool is_prime(int n) {
  if (n == 1) return false;
  int t = n;
  for (int i = 2; i * i <= t; ++i) {
    if (t % i == 0) return false;
  }
  return true;
}

int main() {
  string S;
  while (cin >> S) {
    int N = S.length();
    init(N + 1);

    for (int p = 1; p <= N; ++p) {
      if (p == 1 || !is_prime(p)) continue;

      for (int i = 1; i <= N / p; ++i) {
        unite(p, p * i);
      }
    }

    int two = 0;
    for (int i = 1; i <= N; ++i) {
      if (find(i, 2)) ++two;
    }

    sort(all(S));
    int cnt[256] = {0};
    rep (i, N) ++cnt[(int)S[i]];

    for (int c = 'a'; c <= 'z'; ++c) {
      if (cnt[c] >= two) {
        puts("YES");

        // printf("c = %c\n", (char)c);

        cnt[c] -= two;
        for (int i = 1; i <= N; ++i) {
          if (find(i, 2)) putchar(c);
          else {
            for (int d = 'a'; d <= 'z'; ++d) {
              if (cnt[d] > 0) {
                putchar(d);
                --cnt[d];
                break;
              }
            }
          }
        }
        puts("");
        goto done;
      }
    }

    puts("NO");
 done:;
  }

  return 0;
}

