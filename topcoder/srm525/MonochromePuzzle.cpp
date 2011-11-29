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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

int N;
vector<string> F, G;

vector<int> fix;
int fg[60], gf[60];
bool usd[60];

bool possible(int fi, int gi) {
  rep (i, fix.size()) if (F[fix[i]][fi] != G[fg[fix[i]]][gi]) return false;
  return true;
}

int ans;

void search() {
  int bfi = -1, bp = INT_MAX;
  rep (fi, N) if (fg[fi] == -1) {
    int p = 0;
    rep (gi, N) if (gf[gi] == -1) {
      if (possible(fi, gi)) ++p;
    }
    if (p < bp) {
      bfi = fi;
      bp = p;
    }
  }
  if (bfi == -1) {
    memset(usd, 0, sizeof(usd));
    int r = N;
    rep (i, N) if (!usd[i]) {
      int t = i;
      while (!usd[t]) {
        usd[t] = true;
        t = fg[t];
      }
      --r;
    }
    ans = min(ans, r);
    return;
  }

  rep (bgi, N) if (gf[bgi] == -1) {
    if (!possible(bfi, bgi)) continue;

    fg[bfi] = bgi;
    gf[bgi] = bfi;
    fix.pb(bfi);

    search();

    fix.pop_back();
    fg[bfi] = gf[bgi] = -1;
  }
}

struct MonochromePuzzle {
  int getMinimum(vector <string> board) {
    F = board;
    N = board.size();
    rep (i, N) if (F[i][i] == '#') return -1;

    G = vector<string>(N, string(N, '.'));
    rep (i, N) rep (j, N) {
      if (abs(i - j) == 1 || i + j == N - 1 ||
          mp(min(i, j), max(i, j)) == mp(0, N / 2 - 1) ||
          mp(min(i, j), max(i, j)) == mp(N / 2, N - 1)) {
        G[i][j] = '#';
      }
    }

    memset(fg, -1, sizeof(fg));
    memset(gf, -1, sizeof(gf));
    ans = INT_MAX;
    search();

    return ans == INT_MAX ? -1 : ans;
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".##.#."
,"#.##.."
,"##...#"
,".#..##"
,"#..#.#"
,"..###."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, getMinimum(Arg0)); }
	void test_case_1() { string Arr0[] = {"###..."
,".##..."
,"..#..."
,"#..###"
,"##..##"
,"###..#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, getMinimum(Arg0)); }
	void test_case_2() { string Arr0[] = {".#.#...#"
,"#.#...#."
,".#.#.#.."
,"#.#.#..."
,"...#.#.#"
,"..#.#.#."
,".#...#.#"
,"#...#.#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, getMinimum(Arg0)); }
	void test_case_3() { string Arr0[] = {".#..#....#"
,"#....#..#."
,"....###..."
,"....#.#..#"
,"#.##......"
,".##....#.."
,"..##...#.."
,".....##.#."
,".#.....#.#"
,"#..#....#."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, getMinimum(Arg0)); }
	void test_case_4() { string Arr0[] = {".##.....#."
,"#..#.....#"
,"#..##....."
,".##..#...."
,"..#..##..."
,"...##..#.."
,"....#..##."
,".....##..#"
,"#.....#..#"
,".#.....##."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(4, Arg1, getMinimum(Arg0)); }
	void test_case_5() { string Arr0[] = {".......##.#."
,"......#..#.#"
,"......#..##."
,".......##..#"
,"......#.#..#"
,".......#.##."
,".##.#......."
,"#..#.#......"
,"#..##......."
,".##..#......"
,"#.#..#......"
,".#.##......."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(5, Arg1, getMinimum(Arg0)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  MonochromePuzzle ___test;
  ___test.run_test(-1);
}
// END CUT HERE
