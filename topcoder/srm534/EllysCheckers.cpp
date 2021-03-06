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

struct EllysCheckers {
  string getWinner(string board);
};

int N;
int mem[1 << 20];

bool c(int b, int i) {
  return (b >> i) & 1;
}

bool search(int b) {
  if (c(b, N - 1)) b -= 1 << (N - 1);
  if (mem[b] != -1) return mem[b];

  rep (i, N) {
    if (c(b, i)) {
      if (i + 1 < N && !c(b, i + 1)) {
        if (!search(b - (1 << i) + (1 << (i + 1)))) return mem[b] = true;
      }
      if (i + 3 < N && c(b, i + 1) && c(b, i + 2) && !c(b, i + 3)) {
        if (!search(b - (1 << i) + (1 << (i + 3)))) return mem[b] = true;
      }
    }
  }

  return mem[b] = false;
}

string EllysCheckers::getWinner(string board) {
  N = board.size();
  int b = 0;
  rep (i, N) b |= (board[i] == 'o') << i;

  memset(mem, -1, sizeof(mem));
  return search(b) ? "YES" : "NO";
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

	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) {
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
			cerr << "    Expected: \"" << expected << "\"" << endl;
			cerr << "    Received: \"" << received << "\"" << endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string board              = ".o...";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board              = "..o..o";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board              = ".o...ooo..oo..";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board              = "......o.ooo.o......";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board              = ".o..o...o....o.....o";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string board              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string board              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string board              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
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
