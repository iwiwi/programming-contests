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
#include <bitset>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

const char ALPHA[] = "ABCDEFZHIKLMNOPQRSTVX.";
const int all = (1 << 21) - 1;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int W, H;
int fld[60][60];

ll ans = 0;
int center;

int id;
int cnt[1 << 21];
int cid[1 << 21];

inline void purify(int b) {
  if (cid[b] != id) {
    cnt[b] = 0;
    cid[b] = id;
  }
}

void search(int x, int y, int b, int k) {
  if (x < 0 || W <= x || y < 0 || H <= y) return;
  int d = fld[y][x];
  if (d == 21 || b & (1 << d)) return;
  b |= 1 << d;

  if (k == 0) {
    int tb = (all ^ b) | (1 << center);
    purify(tb);
    ans += cnt[tb];
    purify(b);
    ++cnt[b];
    // rep (i, 21) if (b & (1 << i)) putchar(ALPHA[i]); puts("");
  }
  else {
    rep (d, 4) search(x + dx[d], y + dy[d], b, k - 1);
  }
}

struct AlphabetPaths {
  long long count(vector <string> letterMaze) {
    W = letterMaze[0].length();
    H = letterMaze.size();
    rep (y, H) rep (x, W) fld[y][x] = strchr(ALPHA, letterMaze[y][x]) - ALPHA;

    memset(cid, 0, sizeof(cid));

    ans = id = 0;
    rep (y, H) rep (x, W) {
      ++id;
      center = fld[y][x];
      search(x, y, 0, 10);
    }

    return ans * 2;
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"ABCDEFZHIXKLMNOPQRST",
 "...................V"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arr0[] = {".................VT.",
 "....................",
 "ABCDEFZHIXKLMNOPQRS.",
 "..................S.",
 ".................VT."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arr0[] = {"TBCDE.PQRSA",
 "FZHIXKLMNOV"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 50LL; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arr0[] = {"ABCDEF.",
 "V....Z.",
 "T....H.",
 "S....I.",
 "R....X.",
 "KLMNOPQ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; verify_case(3, Arg1, count(Arg0)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  AlphabetPaths ___test;
  ___test.run_test(-1);
}
// END CUT HERE
