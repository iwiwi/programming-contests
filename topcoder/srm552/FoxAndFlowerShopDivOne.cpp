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
#include <numeric>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

struct FoxAndFlowerShopDivOne {
  int theMaxFlowers(vector <string> flowers, int maxDiff);
};

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


const int P = 1000;
const int INF = 987654321;

int D;

vector<vector<int> > makeit(vector<string> flowers) {
  int H = flowers.size(), W = flowers[0].length(), WH = W * H;
  vector<vector<int> > res(H, vector<int>(2010, -INF));

  int val1[40][40], sum1[40][40];
  int val2[40][40], sum2[40][40];
  rep (y, H) rep (x, W) {
    val1[y][x] = flowers[y][x] == '.' ? 0 : flowers[y][x] == 'L' ? +1 : -1;
    val2[y][x] = flowers[y][x] == '.' ? 0 : +1;
  }
  init_sum(W, H, val1, sum1);
  init_sum(W, H, val2, sum2);

  rep (y0, H) rep (x0, W)
      for (int y1 = y0 + 1; y1 <= H; ++y1) {
        for (int x1 = x0 + 1; x1 <= W; ++x1) {
          int d = get_sum(x0, y0, x1, y1, sum1);
          int s = get_sum(x0, y0, x1, y1, sum2);
          res[y0][P + d] = max(res[y0][P + d], s);
        }
      }

  for (int d = -WH; d <= WH; ++d) {
    for (int y = H - 2; y >= 0; --y) {
      res[y][P + d] = max(res[y][P + d], res[y + 1][P + d]);
    }
  }


  return res;
}

int solve(vector<string> flowers) {
  int H = flowers.size(), W = flowers[0].length();
  int WH = W * H;

  vector<vector<int> > ma1 = makeit(flowers);
  reverse(all(flowers));
  vector<vector<int> > ma2 = makeit(flowers);

  int ans = -1;
  for (int y = 1; y < H; ++y) {
    for (int d1 = -WH; d1 <= WH; ++d1) {
      for (int d2 = max(-WH, -D - d1); d2 <= min(WH, D - d1); ++d2) {
        ans = max(ans, ma1[y][P + d1] + ma2[H - y][P + d2]);
      }
    }
  }
  return ans;
}

int FoxAndFlowerShopDivOne::theMaxFlowers(vector <string> flowers, int maxDiff) {
  D = maxDiff;
  int ans = solve(flowers);

  int H = flowers.size(), W = flowers[0].length();
  vector<string> f2(W, string(H, '.'));
  rep (y, H) rep (x, W) f2[x][y] = flowers[y][x];
  ans = max(ans, solve(f2));

  return ans;
}











// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			}
			return;
		}

		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}

		if (total == 0) {
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}

	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) {
		cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;

		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl;
			cerr << "    Received: " << received << endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string flowers[]          = {"LLL",
 "PPP",
 "LLL"};
			int maxDiff               = 1;
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string flowers[]          = {"LLL",
 "PPP",
 "LLL"};
			int maxDiff               = 0;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string flowers[]          = {"...",
 "...",
 "..."};
			int maxDiff               = 3;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string flowers[]          = {"LLPL.LPP",
 "PLPPPPLL",
 "L.P.PLLL",
 "LPL.PP.L",
 ".LLL.P.L",
 "PPLP..PL"};
			int maxDiff               = 2;
			int expected__            = 38;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string flowers[]          = {"LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL"};
			int maxDiff               = 0;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string flowers[]          = {"LLLP..LLP.PLL.LL..LP",
 "L.PL.L.LLLL.LPLLPLP.",
 "PLL.LL.LLL..PL...L..",
 ".LPPP.PPPLLLLPLP..PP",
 "LP.P.PPL.L...P.L.LLL",
 "L..LPLPP.PP...PPPL..",
 "PP.PLLL.LL...LP..LP.",
 "PL...P.PPPL..PLP.L..",
 "P.PPPLPLP.LL.L.LLLPL",
 "PLLPLLP.LLL.P..P.LPL",
 "..LLLPLPPPLP.P.LP.LL",
 "..LP..L..LLPPP.LL.LP",
 "LPLL.PLLPPLP...LL..P",
 "LL.....PLL.PLL.P....",
 "LLL...LPPPPL.PL...PP",
 ".PLPLLLLP.LPP...L...",
 "LL...L.LL.LLLPLPPPP.",
 "PLPLLLL..LP.LLPLLLL.",
 "PP.PLL..L..LLLPPL..P",
 ".LLPL.P.PP.P.L.PLPLL"};
			int maxDiff               = 9;
			int expected__            = 208;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string flowers[]          = ;
			int maxDiff               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string flowers[]          = ;
			int maxDiff               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string flowers[]          = ;
			int maxDiff               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
