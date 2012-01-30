#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <cassert>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

typedef long long ll;

int main() {
  int N;
  scanf("%d", &N);
  rep (ca, N) {
    ll G, W, M;
    cin >> G >> W >> M;

    ll y0 = M / (2 * W);
    ll y1 = y0 + 1;

    ll d0 = M - y0 * (2 * W);
    ll d1 = y1 * (2 * W) - M;
    if (d0 > d1) cout << y0 << endl;
    else cout << y1 << endl;
  }

  return 0;
}
