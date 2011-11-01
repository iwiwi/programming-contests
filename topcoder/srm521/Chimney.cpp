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
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

map<int, int> ids;
vector<int> adj[1010];

int get(int b, int lev, int pos) {
  return 1 & (b >> (lev * 4 + pos));
}

int search(int b) {
  while ((b & 0xF) == 0xF) b >>= 4;
  if (ids.count(b)) return ids[b];
  int id = ids.size();
  ids[b] = id;

  adj[id].clear();
  for (int l = 0; l < 3; ++l) {
    rep (p, 4) {
      if (get(b, l, p)) continue;
      if (l > 0 && (!get(b, l - 1, p) || !get(b, l - 1, (p + 1) % 4))) continue;

      int tb = b | (1 << (l * 4 + p));
      adj[id].pb(search(tb));
    }
  }
  return id;
}

typedef long long ll;
const ll MOD = 1000000007;

typedef long long number;
typedef vector<number> vec_t;
typedef vector<vec_t> mat_t;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define IS0(x) ((x) == 0)
#define INV(x) inverse(x, MOD)
#define NOR(x) ((x) % MOD)

mat_t identity(int n) {
  mat_t A(n, vec_t(n));
  for (int i = 0; i < n; i++) A[i][i] = 1;
  return A;
}

mat_t multiply(const mat_t &A, const mat_t &B) {
  mat_t C(A.size(), vec_t(B[0].size()));
  for (int i = 0; i < C.size(); i++)
    for (int k = 0; k < A[i].size(); k++)
      for (int j = 0; j < C[i].size(); j++) {
        C[i][j] = NOR(C[i][j] + A[i][k] * B[k][j]);
      }
  return C;
}

mat_t power(const mat_t &A, long long p) {
  if (p == 0) return identity(A.size());
  if (p == 1) return A;
  mat_t B = power(multiply(A, A), p / 2);
  if (p % 2 == 1) B = multiply(B, A);
  return B;
}

struct Chimney {
  int countWays(long long n) {
    ids.clear();
    search(0);

    int K = ids.size();
    mat_t A(K, vec_t(K));
    rep (i, K) rep (j, adj[i].size()) A[i][adj[i][j]] = 1;
    A = power(A, n);
    A = power(A, 4);

    return A[0][0];
  }



};





// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
