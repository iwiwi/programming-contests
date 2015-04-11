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
#include <unordered_set>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

int main() {
  ll A, B, X;
  while (cin >> A >> B >> X) {
    ll a = A;
    unordered_set<ll> s;

    for (int t = 0; ; ++t) {
      if (!s.insert(a).second) {
        puts("-1");
        fprintf(stderr, " %d\n", t);
        break;
      }

      if (a == X) {
        printf("%d\n", t);
        break;
      }

      a = (a >> 1) ^ ((a & 1) ? B : 0);
    }
  }
}
