#include <cstdio>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

typedef long long ll;

int main() {
  int T;
  cin >> T;
  rep (ca, T) {
    ll M, A, B, C, D, E, F, G, H, I, J, K;
    cin >> M >> A >> B >> C >> D >> E >> F >> G >> H >> I >> J >> K;

    ll m = 0;
    int x;
    for (x = 1; m < M; ++x) {
      switch ((J * x + K) % 3) {
        case 0:
          m += A*x*x + B*x + C;
          break;
        case 1:
          m += D*x*x + E*x + F;
          break;
        case 2:
          m += G*x*x + H*x + I;
          break;
      }
    }

    printf("%d\n", x - 1);
  }

  return 0;
}
