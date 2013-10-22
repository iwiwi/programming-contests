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

class TriangleXor {
 public:
  int theArea(int W);
};

double W;

pair<double, double> get_xy(int i) {
  return {W * i / (double)(W + i), 1 * i / (double)(W + i)};
}

int TriangleXor::theArea(int W_) {
  W = W_;

  double ans1 = 0.0, ans2 = 0.0, ans3 = 0.0;
  for (int i = 0; i < W; ++i) {
    double lo_x, lo_y, hi_x, hi_y;
    tie(lo_x, lo_y) = get_xy(i);
    tie(hi_x, hi_y) = get_xy(i + 1);

    {
      // Lower triangles
      double hor = W - (i % 2 == 0 ? hi_x : lo_x) * 2;
      double ver = hi_y - lo_y;
      ans1 += hor * ver / 2;
    }
    if (i % 2 == 0) {
      // Outside triangles
      double hor = 1 * (1 - hi_y);
      double ver = 1 - lo_y;
      ans2 += hor * ver / 2 * 2;
    }
  }
  if (W_ % 2 == 0) ans3 += W * (1 / 2.0) / 2.0;

  return floor(ans1 + ans2 + ans3);
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
			int W                     = 1;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = TriangleXor().theArea(W);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int W                     = 2;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TriangleXor().theArea(W);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int W                     = 3;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TriangleXor().theArea(W);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int W                     = 4;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TriangleXor().theArea(W);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int W                     = 5;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TriangleXor().theArea(W);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int W                     = 12345;
			int expected__            = 4629;

			std::clock_t start__      = std::clock();
			int received__            = TriangleXor().theArea(W);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int W                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TriangleXor().theArea(W);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int W                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TriangleXor().theArea(W);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int W                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TriangleXor().theArea(W);
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
