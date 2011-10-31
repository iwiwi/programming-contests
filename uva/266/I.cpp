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

typedef long long number;
typedef vector<number> vec_t;
typedef vector<vec_t> mat_t;

const ll MOD = 987654321;

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

mat_t power(const mat_t &A, int p) {
  if (p == 0) return identity(A.size());
  if (p == 1) return A;
  mat_t B = power(multiply(A, A), p / 2);
  if (p % 2 == 1) B = multiply(B, A);
  return B;
}


int main() {

  for (;;) {
    int P;
    scanf("%d", &P);
    if (!P) return 0;

    if (P % 2 != 0 || P < 8) {
      puts("0");
      continue;
    }

    mat_t A(2, vec_t(2));
    A[0][0] = A[0][1] = A[1][0] = 1;
    A = power(A, P - 4);
    ll t = A[0][0];
    t -= P / 2 - 1;
    t = (t % MOD + MOD) % MOD;
    cout << t << endl;
  }

  return 0;
}

