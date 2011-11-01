#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

#define all(c) (c).begin(), (c).end()

int main() {
  const int N = 200000;
  const int M = 100000;
  vector<int> v(N); rep(i, N) v[i] = i; random_shuffle(all(v));
  vector<int> w(N); rep(i, N) w[i] = i; random_shuffle(all(w));

  printf("%d %d\n", N, M);
  rep (i, N) printf("%d\n", v[i]);
  rep (i, M) printf("%d\n", w[i]);
  return 0;
}
