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




int main() {
  for (;;) {
    int B, R, G, C, S, T;
    scanf("%d%d%d%d%d%d", &B, &R, &G, &C, &S, &T);
    if (B == 0 && R == 0 && G == 0 && C == 0 && S == 0 && T == 0) return 0;

    int bonus = B * 5 + R * 3;
    int normal = T - bonus;

    int medal = 100;

    // throw in
    medal -= (normal - S) * 3;
    medal -= bonus * 2;

    // normal get
    medal += B * 15;  // 7
    medal += R * 15;  // BAR
    medal += G * 7;   // grape
    medal += C * 2;   // cherry

    // bonus get
    medal += bonus * 15;

    printf("%d\n", medal);
  }

  return 0;
}

