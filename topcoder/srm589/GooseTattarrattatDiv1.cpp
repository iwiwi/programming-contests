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

class GooseTattarrattatDiv1 {
 public:
  int getmin(string S);
};

const int C = 26;

int GooseTattarrattatDiv1::getmin(string S) {
  int L = S.length();
  bool adj[30][30] = {};
  rep (c, C) adj[c][c] = true;
  rep (i, L / 2) {
    adj[S[i] - 'a'][S[L - i - 1] - 'a'] = true;
    adj[S[L - i - 1] - 'a'][S[i] - 'a'] = true;
  }
  rep (k, C) rep (i, C) rep (j, C) adj[i][j] |= adj[i][k] && adj[k][j];

  bool done[30] = {};
  int ans = 0;
  rep (c, C) if (!done[c]) {
    int to = 0, ma = 0;
    rep (d, C) if (adj[c][d]) {
      int x = count(all(S), d + 'a');
      to += x;
      ma = max(ma, x);
      done[d] = true;
    }
    ans += to - ma;
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
			string S                  = "geese";
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S                  = "tattarrattat";
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S                  = "xyyzzzxxx";
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S                  = "xrepayuyubctwtykrauccnquqfuqvccuaakylwlcjuyhyammag";
			int expected__            = 11;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string S                  = "abaabb";
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string S                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string S                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string S                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
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
