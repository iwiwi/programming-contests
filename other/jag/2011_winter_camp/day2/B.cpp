#include <cstdio>
#include <queue>
#include <string>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int main() {
  int K;
  string S;
  cin >> K >> S;
  int L = S.length();
  
  string SS = S + S;
  int LL = SS.length();
  for (int t = L / 2; t >= 1; --t) {
    string ans = "";
    int crr = 0;
    rep (i, t) if (SS[i] != SS[i + t]) ++crr;

    for (int i = 0; i + t + t <= LL; ++i) {
      if (crr <= K) {
        string tmp = SS.substr(i, t + t);
        if (ans == "" || tmp < ans) ans = tmp;
      }

      if (SS[i] != SS[i + t]) --crr;
      if (SS[i + t] != SS[i + t + t]) ++crr;
    }

    if (ans != "") {
      cout << ans << endl;
      return 0;
    }
  }

  // Does not exist
  cout << endl;
  return 0;
}
