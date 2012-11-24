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


int hash(string S) {
  int h = 0;
  rep (i, S.length()) h += S[i] - 'a' + 1;
  return h;
}

int main() {
  string S;
  while (cin >> S) {
    string original = S;
    int L = S.length();

    if (S == "a" || S == "zzzzzzzzzzzzzzzzzzzz") {
      puts("NO");
      continue;
    } else if (S.length() == 1) {
      S[0] -= 1;
      S += "a";
    } else if (count(all(S), 'a') == L) {
      S[0] += 1;
      S = S.substr(0, L - 1);
    } else if (count(all(S), 'z') == L) {
      S[0] -= 1;
      S += 'a';
    } else {
      int i, j;
      if (count(all(S), 'a')) {
        i = find(all(S), 'a') - S.begin();
      } else {
        for (i = 0; i < L; ++i) {
          if (S[i] != 'z') break;
        }
      }
      for (j = 0; j < L; ++j) {
        if (S[j] != 'a' && i != j) break;
      }
      S[i] += 1;
      S[j] -= 1;
    }

    cout << S << endl;
    assert(S != original && hash(S) == hash(original));
  }

  return 0;
}

