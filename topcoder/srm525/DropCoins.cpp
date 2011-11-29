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


template<size_t csize>
void init_sum(int W, int H, int val[][csize], int sum[][csize]) {
  for (int y = 0; y <= H; ++y) {
    for (int x = 0; x <= W; ++x) {
      sum[y][x] = (y == 0 || x == 0) ? 0 :
          sum[y-1][x] + sum[y][x-1] - sum[y-1][x-1] + val[y-1][x-1];
    }
  }
}

template<size_t csize>
inline int get_sum(int x0, int y0, int x1, int y1, int sum[][csize]) {
  return sum[y1][x1] - sum[y1][x0] - sum[y0][x1] + sum[y0][x0];
}


int val[60][60], sum[60][60];

struct DropCoins {
  int cst(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return min(a + a + b, b + b + a);
  }

  int getMinimum(vector <string> board, int K) {
    int H = board.size();
    int W = board[0].length();

    rep (y, H) rep (x, W) val[y][x] = board[y][x] == 'o' ? 1 : 0;

    init_sum(W, H, val, sum);

    int ans = INT_MAX;
    for (int xl = 0; xl < W; ++xl) {
      for (int xu = xl; xu <= W; ++xu) {
        for (int yl = 0; yl < H; ++yl) {
          for (int yu = yl; yu <= H; ++yu) {
            // [xl, xu) * [yl, yu)
            int s = get_sum(xl, yl, xu, yu, sum);
            if (s != K) continue;
            int c = cst(xl, W - xu) + cst(yl, H - yu);
            ans = min(ans, c);
          }
        }
      }
    }
    if (ans == INT_MAX) return -1;
    return ans;
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".o.."
,"oooo"
,"..o."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 2; verify_case(0, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {".....o"
,"......"
,"oooooo"
,"oooooo"
,"......"
,"o....."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; int Arg2 = 3; verify_case(1, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"...."
,".oo."
,".oo."
,"...."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = -1; verify_case(2, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"......."
,"..ooo.."
,"ooooooo"
,".oo.oo."
,"oo...oo"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; int Arg2 = 4; verify_case(3, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"................."
,".ooooooo...oooo.."
,".ooooooo..oooooo."
,".oo.......oo..oo."
,".oo.......oo..oo."
,".ooooo.....oooo.."
,".ooooooo...oooo.."
,".....ooo..oo..oo."
,"......oo..oo..oo."
,".ooooooo..oooooo."
,".oooooo....oooo.."
,"................."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 58; int Arg2 = 6; verify_case(4, Arg2, getMinimum(Arg0, Arg1)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  DropCoins ___test;
  ___test.run_test(-1);
}
// END CUT HERE
