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
#define eb emplace_back
#define mp make_pair

class YetAnotherBoardGame {
 public:
  int minimumMoves(vector <string> board);
};

const int INF = 987654321;

int W, H, ans;

inline void push(int x, int y, int type, vector<int> &F) {
  ++x;
  ++y;
  F[y] ^= 1 << (x + 1); F[y + 1] ^= 1 << (x);
  F[y] ^= 1 << (x - 1); F[y - 1] ^= 1 << (x);
  if (type == 1) F[y] ^= 1 << x;
}

inline bool get(int x, int y, const vector<int> &F) {
  return (F[y + 1] >> (x + 1)) & 1;
}

int solve(vector<int> &F, int b, int tmp) {
  for (int y = 1; y < H; ++y) {
    int cnt[2] = {};
    rep (x, W) if (get(x, y - 1, F)) {
      int t = (b >> x) & 1;
      push(x, y, t, F);
      ++cnt[t];
    }
    if (cnt[0] && cnt[1]) return INF;
    tmp += cnt[0] + cnt[1];
    if (tmp >= ans) return INF;
  }

  rep (x, W) if (get(x, H - 1, F)) return INF;
  return tmp;
}

int YetAnotherBoardGame::minimumMoves(vector <string> board) {
  W = board[0].length();
  H = board.size();
  vector<int> F(H + 2);
  rep (y, H) rep (x, W) F[y + 1] |= (board[y][x] == 'W' ? 1 : 0) << (x + 1);

  ans = INF;
  vector<int> tf(H + 2);
  rep (b, 1 << W) {
    {
      // Flip 1s
      int super = b, sub = super;
      do {
        copy(all(F), tf.begin());
        rep (x, W) if (sub & (1 << x)) push(x, 0, 1, tf);
        ans = min(ans, solve(tf, b, __builtin_popcount(sub)));

        sub = (sub - 1) & super;
      } while (sub != super);
    }
    {
      // Flip 0s
      int super = (1 << W) - 1 - b, sub = super;
      do {
        copy(all(F), tf.begin());
        rep (x, W) if (sub & (1 << x)) push(x, 0, 0, tf);
        ans = min(ans, solve(tf, b, __builtin_popcount(sub)));

        sub = (sub - 1) & super;
      } while (sub != super);
    }
  }

  return ans >= INF ? -1 : ans;
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
			string board[]            = {"BBBBBBBBB",
 "BBWBBBBBB",
 "BWWWBBBBB",
 "BBWBBBWBB",
 "BBBBBWBWB",
 "BBBBBBWBB"};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"BBW",
 "WWW",
 "BWW"};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"WBW",
 "BBW",
 "WBW"};
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"BBBB",
 "WBWB",
 "BBBB",
 "BBBB"};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"WWWWWBW",
 "WBWBWBW",
 "BBWBBWW"};
			int expected__            = 7;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {"WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW"}
;
			int expected__            = 30;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
        string board[]            = {
          "WWWWWWWWWWWWW", "WWWWWWWWWWWWW", "WWWWWWWWWWWWW", "WWWWWWWWWWWWW", "WWWWWWWWWWWWW", "WWWWWWWWWWWWW", "WWWWWWWWWWWWW", "WWWWWWWWWWWWW", "WWWWWWWWWWWWW", "WWWWWWWWWWWWW", "WWWWWWWWWWWWW", "WWWWWWWWWWWWW", "WWWWWWWWWWWWW"
        };
			int expected__            = 53;
			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
