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

#define F first
#define S second

typedef long long ll;


const char *H_answers[] = {
  "A",
  "ACD",
  "DH",
  "D",

  "C",
  "G",
  "E", "BE", "BEF", "BF", "B"
};


vector<string> split(string s, const string &t) {
  vector<string> v;
  for (string::size_type p = s.find(t); p != s.npos; p = s.find(t)) {
    v.push_back(s.substr(0, p));
    s = s.substr(p + t.size());
  }
  v.push_back(s);
  return v;
}

int how_many_numbers(string s) {
  vector<string> vs = split(s, " ");

  int c = 0;
  rep (i, vs.size()) if (isdigit(vs[i][0])) ++c;
  return c;
}

int main() {
  vector<string> input;
  for (string line; getline(cin, line); ) input.pb(line);

  string line0 = input[0];
  int n = how_many_numbers(line0);

  if (n == 0) {
    if (line0 == "NO") {
      puts("ACD");
      return 0;
    } else {
      rep (i, sizeof(H_answers) / sizeof(H_answers[0])) {
        if (line0 == H_answers[i]) {
          puts("DH");
          return 0;
        }
      }

      puts("D");
      return 0;
    }
  }
  else if (n == 1) {
    if (input.size() > 1) {
      if (how_many_numbers(input[1]) == 0) {
        puts("A");
        return 0;
      }
      else {
        puts("G");
        return 0;
      }
    } else {
      // B, E, F
      pair<int, int> B = mp(1, (100000 - 1) * 10000 - 1);
      pair<int, int> E = mp(0, 50);
      pair<int, int> F = mp(4, (100000 - 2) * (10000 - 1) + 10000 * 2);

      int x = atoi(line0.c_str());
      string res = "";
      if (B.F <= x && x <= B.S) res += "B";
      if (E.F <= x && x <= E.S) res += "E";
      if (F.F <= x && x <= F.S) {
        if (x >= 100000) {
          for (ll d = 1; d < 10000; ++d) {
            ll n = x / d;
            if (n > 100000) continue;

            if (d * n <= x && x <= d * (n - 2) + 20000) goto ok;
          }
          goto ng;
        ok:;
        }

        res += "F";
      ng:;
      }
      cout << res << endl;
      return 0;
    }
  }
  else {
    puts("C");
    return 0;
  }
}

/*
【文字列】
A: N+N行 or "NO"
C: "NO"
D: アルファベット大文字，100 文字以下，多分たまにあり得ないけど多分どうでも良い
H: !!!!!

【数値】
B: 1個　/　[1, D*(M-1)-1 = 999 989 999] ?
C: N * 2N (2 ≦ N ≦ 150) 個
E: 1個　/　[0, 50] ?
F: 1個　/　[4, 999 900 002]
G: T (≧ 2) * 1 個

↓↓↓25 点もらったので決定版!!!↓↓↓
【それでは，H の出力としてあり得るのは！？】
N+N行: A
"NO": ACD
"A"とか: DH
それ以外の変な文字列: D

N*2N: C
T行: G
1個: E, BE, BEF, BF, B

区間
B:    -----------------------------
E:  ---------
F:        ---------------------
*/
