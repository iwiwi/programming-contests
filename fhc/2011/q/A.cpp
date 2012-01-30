#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

int main() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    ll x;
    cin >> x;

    ll ans = 0;
    for (ll a = 0; a * a <= x; ++a) {
      ll bb = x - a * a;
      ll b = (ll)round(sqrt(bb));
      if (a * a + b * b == x && a <= b) {
        ++ans;
      }
    }
    cout << ans << endl;
  }
}

