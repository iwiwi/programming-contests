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

class FoxAndGomoku {
 public:
  string win(vector <string> board);
};

string FoxAndGomoku::win(vector <string> board) {
  int N = board.size();

  rep (i, 4) {
    int dx = vector<int>{1, 0, 1,  1}[i];
    int dy = vector<int>{0, 1, 1, -1}[i];

    rep (x, N) rep (y, N) {
      rep (j, 5) {
        int tx = x + dx * j;
        int ty = y + dy * j;

        auto chk = [&](int z) { return 0 <= z && z < N; };
        if (chk(tx) && chk(ty) && board[ty][tx] == 'o');
        else goto dmp;
      }
      return "found";
   dmp:;
    }
  }

  return "not found";
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

	int verify_case(int casenum, const string &expected, const string &received, std::clock_t elapsed) {
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
			std::cerr << "    Expected: \"" << expected << "\"" << std::endl;
			std::cerr << "    Received: \"" << received << "\"" << std::endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string board[]            = {"....o.",
 "...o..",
 "..o...",
 ".o....",
 "o.....",
 "......"};
			string expected__         = "found";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndGomoku().win(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"oooo.",
 ".oooo",
 "oooo.",
 ".oooo",
 "....."}
 ;
			string expected__         = "not found";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndGomoku().win(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"oooo.",
 ".oooo",
 "oooo.",
 ".oooo",
 "....o"}
 ;
			string expected__         = "found";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndGomoku().win(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"o.....",
 ".o....",
 "..o...",
 "...o..",
 "....o.",
 "......"};
			string expected__         = "found";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndGomoku().win(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"o....",
 "o.o..",
 "o.o.o",
 "o.o..",
 "o...."};
			string expected__         = "found";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndGomoku().win(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {"..........",
 "..........",
 "..oooooo..",
 "..o.......",
 "..o.......",
 "..oooooo..",
 ".......o..",
 ".......o..",
 "..oooooo..",
 ".........."}

;
			string expected__         = "found";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndGomoku().win(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string board[]            = {"..........",
 "..........",
 "..oooo.o..",
 "..o.......",
 "..o.......",
 "..o.oooo..",
 ".......o..",
 ".......o..",
 "..oooo.o..",
 ".........."}
;
			string expected__         = "not found";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndGomoku().win(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			string board[]            = {"ooooo",
 "ooooo",
 "ooooo",
 "ooooo",
 "ooooo"};
			string expected__         = "found";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndGomoku().win(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 8: {
			string board[]            = {".....",
 ".....",
 ".....",
 ".....",
 "....."};
			string expected__         = "not found";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndGomoku().win(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 9: {
			string board[]            = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = FoxAndGomoku().win(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			string board[]            = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = FoxAndGomoku().win(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 11: {
			string board[]            = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = FoxAndGomoku().win(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
