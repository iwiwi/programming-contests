#include <cstdio>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

typedef long long ll;

int main() {
  int T;
  cin >> T;

  rep (ca, T) {
    ll N;
    double P;
    cin >> N >> P;

    //double ans = (N + 1.0) / 3.0 / P;
    //printf("%.3f\n", ans);
    
     double e = 0.0;
     for (int i = N - 1; i >= 1; --i) {
       //double q = P * (i * (N - i) / (N * (N - 1) / 2));
       e += 1.0 / i;
     }
     e*=N-1;
     e/=P;
     printf("%.3f\n", e);
  }

  return 0;
}
