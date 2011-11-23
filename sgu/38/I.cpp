#include <cstdio>
#include <algorithm>
#include <utility>
#include <climits>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define mp make_pair

typedef long long ll;


int main() {
  string S;
  while (getline(cin, S)) {
    bool open = false;
    int ans = 0;
    rep (i, S.length()) {
      if (isalpha(S[i]) || isspace(S[i])) continue;
      else if (S[i] == '(') {
        // printf("open: %d\n", open);
        if (open) ++ans;
        else open = true;
      }
      else if (S[i] == ')') {
        // printf("close: %d\n", open);
        if (open) open = false;
        else ++ans;
      }
      else {
        if (open) { ++ans; open = false; }
      }
    }
    // printf("end: %d\n", open);
    if (open) ++ans;

    printf("%d\n", ans);
  }
  return 0;
}
