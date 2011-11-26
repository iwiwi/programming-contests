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

const char* segs[] = {
 //abcdefg
  "1111110",
  "0110000",
  "1101101",
  "1111001",
  "0110011",
  "1011011",
  "1011111",
  "1110010",
  "1111111",
  "1111011",
};

int main() {
  for (;;) {
    int N;
    scanf("%d", &N);
    if (N == -1) return 0;
    string prv = "0000000";
    rep (i, N) {
      int t;
      scanf("%d", &t);

      string nxt = segs[t];
      reverse(all(nxt));
      rep (i, nxt.size()) printf("%d", prv[i] == nxt[i] ? 0 : 1);
      puts("");

      prv = nxt;
    }
  }

  return 0;
}

