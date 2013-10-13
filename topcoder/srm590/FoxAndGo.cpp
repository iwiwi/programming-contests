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
#include <tuple>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

class FoxAndGo {
 public:
  int maxKill(vector <string> board);
};

int N;
vector<string> B;

int score() {
  bool vis[30][30] = {};
  int ans = 0;

  rep (sy, N) rep (sx, N) {
    if (B[sy][sx] == 'o' && !vis[sy][sx]);
    else continue;

    vector<tuple<int, int> > stk;
    stk.emplace_back(sx, sy);
    vis[sy][sx] = true;
    int sz = 0, fr = 0;

    while (!stk.empty()) {
      int x, y;
      tie(x, y) = stk.back();
      stk.pop_back();
      ++sz;

      static const int dx[4] = {1, 0, -1, 0};
      static const int dy[4] = {0, 1, 0, -1};
      rep (d, 4) {
        int tx = x + dx[d], ty = y + dy[d];
        auto f = [&](int z) { return z < 0 || N <= z; };
        if (f(tx) || f(ty) || vis[ty][tx] || B[ty][tx] == 'x') continue;
        else if (B[ty][tx] == '.') ++fr;
        else {
          assert(B[ty][tx] == 'o');
          stk.emplace_back(tx, ty);
          vis[ty][tx] = true;
        }
      }
    }
    if (fr == 0) ans += sz;
  }
  return ans;
}

int FoxAndGo::maxKill(vector <string> board) {
  N = board.size();
  B = board;

  int ans = 0;
  rep (y, N) rep (x, N) if (B[y][x] == '.') {
    B[y][x] = 'x';
    ans = max(ans, score());
    B[y][x] = '.';
  }

  return ans;
}















// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
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
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}

	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) {
		std::cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;

		if (verdict == "FAILED") {
			std::cerr << "    Expected: " << expected << std::endl;
			std::cerr << "    Received: " << received << std::endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string board[]            = {".....",
 "..x..",
 ".xox.",
 ".....",
 "....."}
;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGo().maxKill(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"ooooo",
 "xxxxo",
 "xxxx.",
 "xxxx.",
 "ooooo"}
;
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGo().maxKill(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {".xoxo",
 "ooxox",
 "oooxx",
 "xoxox",
 "oxoox"}
;
			int expected__            = 13;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGo().maxKill(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {".......",
 ".......",
 ".......",
 "xxxx...",
 "ooox...",
 "ooox...",
 "ooox..."}
;
			int expected__            = 9;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGo().maxKill(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {".......",
 ".xxxxx.",
 ".xooox.",
 ".xo.ox.",
 ".xooox.",
 ".xxxxx.",
 "......."}
;
			int expected__            = 8;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGo().maxKill(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {"o.xox.o",
 "..xox..",
 "xxxoxxx",
 "ooo.ooo",
 "xxxoxxx",
 "..xox..",
 "o.xox.o"}
;
			int expected__            = 12;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGo().maxKill(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string board[]            = {".......",
 "..xx...",
 ".xooox.",
 ".oxxox.",
 ".oxxxo.",
 "...oo..",
 "......."};
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGo().maxKill(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			string board[]            = {".ox....",
 "xxox...",
 "..xoox.",
 "..xoox.",
 "...xx..",
 ".......",
 "......."}
 ;
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGo().maxKill(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 8: {
			string board[]            = {"...................",
 "...................",
 "...o..........o....",
 "................x..",
 "...............x...",
 "...................",
 "...................",
 "...................",
 "...................",
 "...................",
 "...................",
 "...................",
 "...................",
 "...................",
 "................o..",
 "..x................",
 "...............x...",
 "...................",
 "..................."}
;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGo().maxKill(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 9: {
			string board[]            = {"xx.xxxx", "xoo..xo", "o.x..o.", "..x.x..", ".o.x.xx", "x....o.", ".xxooox"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGo().maxKill(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 10: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGo().maxKill(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 11: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGo().maxKill(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
