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

class ConvertibleStrings {
 public:
  int leastRemovals(string A, string B);
};

const int K = 'I' - 'A' + 1;

int ConvertibleStrings::leastRemovals(string A, string B) {
  int L = A.length();

  vector<char> per(K);
  iota(all(per), 'A');

  int ans = L;
  do {
    int tmp = 0;
    rep (i, L) if (per[A[i] - 'A'] != B[i]) ++tmp;
    ans = min(ans, tmp);
  } while (next_permutation(all(per)));

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
			string A                  = "DD";
			string B                  = "FF";
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = ConvertibleStrings().leastRemovals(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string A                  = "AAAA";
			string B                  = "ABCD";
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = ConvertibleStrings().leastRemovals(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string A                  = "AAIAIA";
			string B                  = "BCDBEE";
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = ConvertibleStrings().leastRemovals(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string A                  = "ABACDCECDCDAAABBFBEHBDFDDHHD";
			string B                  = "GBGCDCECDCHAAIBBFHEBBDFHHHHE";
			int expected__            = 9;

			std::clock_t start__      = std::clock();
			int received__            = ConvertibleStrings().leastRemovals(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string A                  = ;
			string B                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ConvertibleStrings().leastRemovals(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string A                  = ;
			string B                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ConvertibleStrings().leastRemovals(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string A                  = ;
			string B                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ConvertibleStrings().leastRemovals(A, B);
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
