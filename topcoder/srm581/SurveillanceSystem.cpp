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

class SurveillanceSystem {
 public:
  string getContainerInfo(string containers, vector <int> reports, int L);
};



string SurveillanceSystem::getContainerInfo(string containers, vector <int> reports, int L) {
  int N = containers.length();

  map<int, int> cnt;
  for (int r : reports) ++cnt[r];

  string ans(N, '-');
  tr (cnt, ite) {
    int r = ite->first, c = ite->second;

    vector<int> pos(N);
    int tot = 0;
    for (int i = 0; i + L <= N; ++i) {
      string s = containers.substr(i, L);
      if (count(all(s), 'X') == r) {
        rep (j, L) ++pos[i + j];
        ++tot;
      }
    }

    rep (i, N) {
      if (pos[i] + c > tot) ans[i] = '+';
      else if (pos[i] > 0 && ans[i] == '-') ans[i] = '?';
    }
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
			string containers         = "-X--XX";
			int reports[]             = {1, 2};
			int L                     = 3;
			string expected__         = "??++++";

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string containers         = "-XXXXX-";
			int reports[]             = {2};
			int L                     = 3;
			string expected__         = "???-???";

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string containers         = "------X-XX-";
			int reports[]             = {3, 0, 2, 0};
			int L                     = 5;
			string expected__         = "++++++++++?";

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string containers         = "-XXXXX---X--";
			int reports[]             = {2, 1, 0, 1};
			int L                     = 3;
			string expected__         = "???-??++++??";

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string containers         = "-XX--X-XX-X-X--X---XX-X---XXXX-----X";
			int reports[]             = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
			int L                     = 7;
			string expected__         = "???++++?++++++++++++++++++++??????--";

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string containers         = ;
			int reports[]             = ;
			int L                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string containers         = ;
			int reports[]             = ;
			int L                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string containers         = ;
			int reports[]             = ;
			int L                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
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
