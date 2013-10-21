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

class Egalitarianism {
 public:
  int maxDifference(vector <string> isFriend, int d);
};

const int INF = 987654321;

int mat[60][60];

int Egalitarianism::maxDifference(vector <string> isFriend, int d) {
  int N = isFriend.size();
  rep (i, N) rep (j, N) mat[i][j] = i == j ? 0 : isFriend[i][j] == 'Y' ? 1 : INF;
  rep (k, N) rep (i, N) rep (j, N) mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);

  int ans = 0;
  rep (i, N) rep (j, i) {
    if (mat[i][j] >= INF) return -1;
    ans = max(ans, mat[i][j] * d);
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
			string isFriend[]         = {"NYN",
 "YNY",
 "NYN"};
			int d                     = 10;
			int expected__            = 20;

			std::clock_t start__      = std::clock();
			int received__            = Egalitarianism().maxDifference(vector <string>(isFriend, isFriend + (sizeof isFriend / sizeof isFriend[0])), d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string isFriend[]         = {"NN",
 "NN"};
			int d                     = 1;
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = Egalitarianism().maxDifference(vector <string>(isFriend, isFriend + (sizeof isFriend / sizeof isFriend[0])), d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string isFriend[]         = {"NNYNNN",
 "NNYNNN",
 "YYNYNN",
 "NNYNYY",
 "NNNYNN",
 "NNNYNN"};
			int d                     = 1000;
			int expected__            = 3000;

			std::clock_t start__      = std::clock();
			int received__            = Egalitarianism().maxDifference(vector <string>(isFriend, isFriend + (sizeof isFriend / sizeof isFriend[0])), d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string isFriend[]         = {"NNYN",
 "NNNY",
 "YNNN",
 "NYNN"};
			int d                     = 584;
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = Egalitarianism().maxDifference(vector <string>(isFriend, isFriend + (sizeof isFriend / sizeof isFriend[0])), d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string isFriend[]         = {"NYNYYYN",
 "YNNYYYN",
 "NNNNYNN",
 "YYNNYYN",
 "YYYYNNN",
 "YYNYNNY",
 "NNNNNYN"};
			int d                     = 5;
			int expected__            = 20;

			std::clock_t start__      = std::clock();
			int received__            = Egalitarianism().maxDifference(vector <string>(isFriend, isFriend + (sizeof isFriend / sizeof isFriend[0])), d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string isFriend[]         = {"NYYNNNNYYYYNNNN",
 "YNNNYNNNNNNYYNN",
 "YNNYNYNNNNYNNNN",
 "NNYNNYNNNNNNNNN",
 "NYNNNNYNNYNNNNN",
 "NNYYNNYNNYNNNYN",
 "NNNNYYNNYNNNNNN",
 "YNNNNNNNNNYNNNN",
 "YNNNNNYNNNNNYNN",
 "YNNNYYNNNNNNNNY",
 "YNYNNNNYNNNNNNN",
 "NYNNNNNNNNNNNNY",
 "NYNNNNNNYNNNNYN",
 "NNNNNYNNNNNNYNN",
 "NNNNNNNNNYNYNNN"}
;
			int d                     = 747;
			int expected__            = 2988;

			std::clock_t start__      = std::clock();
			int received__            = Egalitarianism().maxDifference(vector <string>(isFriend, isFriend + (sizeof isFriend / sizeof isFriend[0])), d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string isFriend[]         = {"NY",
 "YN"};
			int d                     = 0;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = Egalitarianism().maxDifference(vector <string>(isFriend, isFriend + (sizeof isFriend / sizeof isFriend[0])), d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string isFriend[]         = ;
			int d                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Egalitarianism().maxDifference(vector <string>(isFriend, isFriend + (sizeof isFriend / sizeof isFriend[0])), d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string isFriend[]         = ;
			int d                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Egalitarianism().maxDifference(vector <string>(isFriend, isFriend + (sizeof isFriend / sizeof isFriend[0])), d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string isFriend[]         = ;
			int d                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Egalitarianism().maxDifference(vector <string>(isFriend, isFriend + (sizeof isFriend / sizeof isFriend[0])), d);
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
