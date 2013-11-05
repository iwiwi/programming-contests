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

class LittleElephantAndIntervalsDiv1 {
 public:
  long long getNumber(int M, vector <int> L, vector <int> R);
};

typedef long long ll;

long long LittleElephantAndIntervalsDiv1::getNumber(int M, vector <int> L, vector <int> R) {
  vector<int> A(M + 10, -1);
  rep (i, L.size()) {
    int l = L[i], r = R[i];
    for (int p = l; p <= r; ++p) A[p] = i;
  }

  ll ans = 1;
  rep (i, L.size()) if (count(all(A), i)) ans *= 2;
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

	int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) {
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
			int M                     = 4;
			int L[]                   = {1, 2, 3};
			int R[]                   = {1, 2, 3};
			long long expected__      = 8;

			std::clock_t start__      = std::clock();
			long long received__      = LittleElephantAndIntervalsDiv1().getNumber(M, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int M                     = 3;
			int L[]                   = {1, 1, 2};
			int R[]                   = {3, 1, 3};
			long long expected__      = 4;

			std::clock_t start__      = std::clock();
			long long received__      = LittleElephantAndIntervalsDiv1().getNumber(M, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int M                     = 1000;
			int L[]                   = {47};
			int R[]                   = {747};
			long long expected__      = 2;

			std::clock_t start__      = std::clock();
			long long received__      = LittleElephantAndIntervalsDiv1().getNumber(M, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int M                     = 42;
			int L[]                   = {5, 23, 4, 1, 15, 2, 22, 26, 13, 16, 28, 13, 27, 9, 18, 4, 10, 3, 4, 4, 3, 4, 1, 18, 18, 2, 38, 4, 10, 12, 3, 30, 11, 38, 2, 13, 1, 13, 18, 16, 13, 2, 14, 27, 13, 3, 26, 19, 5, 10};
			int R[]                   = {30, 41, 17, 1, 21, 6, 28, 30, 15, 19, 31, 28, 35, 27, 30, 13, 31, 5, 8, 25, 40, 10, 3, 26, 23, 9, 40, 8, 40, 23, 12, 37, 35, 39, 11, 34, 10, 21, 22, 21, 24, 5, 39, 27, 17, 16, 26, 35, 25, 36};
			long long expected__      = 256;

			std::clock_t start__      = std::clock();
			long long received__      = LittleElephantAndIntervalsDiv1().getNumber(M, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int M                     = ;
			int L[]                   = ;
			int R[]                   = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = LittleElephantAndIntervalsDiv1().getNumber(M, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int M                     = ;
			int L[]                   = ;
			int R[]                   = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = LittleElephantAndIntervalsDiv1().getNumber(M, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int M                     = ;
			int L[]                   = ;
			int R[]                   = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = LittleElephantAndIntervalsDiv1().getNumber(M, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
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
