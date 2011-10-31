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
  int ans = 0;

  for (;;) {
    int a, b;
    if (1 != scanf("%d", &a)) break;
    char o, e;
    scanf("%c", &o);
    scanf("%d", &b);
    scanf("%c", &e);
    char cstr[256];
    scanf("%s", cstr);
    if (!isdigit(cstr[0])) continue;
    int c = atoi(cstr);

    if (o == '+' && a + b == c) ++ans;
    if (o == '-' && a - b == c) ++ans;
  }
  printf("%d\n", ans);

  return 0;
}

