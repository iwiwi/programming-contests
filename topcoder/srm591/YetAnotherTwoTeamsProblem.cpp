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

class YetAnotherTwoTeamsProblem {
 public:
  long long count(vector <int> skill);
};

typedef long long ll;

ll dp[3000010];

long long YetAnotherTwoTeamsProblem::count(vector <int> skill) {
  int N = skill.size();
  sort(all(skill), [&](int a, int b) { return a > b; } );
  int T = accumulate(all(skill), 0);

  memset(dp, 0, sizeof(dp));
  dp[0] = 1;

  ll ans = 0;
  rep (i, N) {
    int s = skill[i];

    for (int x = T; x >= s; --x) {
      ll p = dp[x - s];
      dp[x] += p;

      int y = T - x;
      if (x > y && x - s < y + s) ans += p;
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
			int skill[]               = {5, 4, 7, 6};
			long long expected__      = 2;

			std::clock_t start__      = std::clock();
			long long received__      = YetAnotherTwoTeamsProblem().count(vector <int>(skill, skill + (sizeof skill / sizeof skill[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int skill[]               = {1, 1, 1, 1, 1};
			long long expected__      = 10;

			std::clock_t start__      = std::clock();
			long long received__      = YetAnotherTwoTeamsProblem().count(vector <int>(skill, skill + (sizeof skill / sizeof skill[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int skill[]               = {1, 2, 3, 5, 10};
			long long expected__      = 5;

			std::clock_t start__      = std::clock();
			long long received__      = YetAnotherTwoTeamsProblem().count(vector <int>(skill, skill + (sizeof skill / sizeof skill[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int skill[]               = {1, 2, 3, 4, 10};
			long long expected__      = 0;

			std::clock_t start__      = std::clock();
			long long received__      = YetAnotherTwoTeamsProblem().count(vector <int>(skill, skill + (sizeof skill / sizeof skill[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int skill[]               = {999, 999, 999, 1000, 1000, 1001, 999, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 999, 1000, 512, 511, 1001, 1001, 1001, 1001, 1001, 1000};
			long long expected__      = 17672631900LL;

			std::clock_t start__      = std::clock();
			long long received__      = YetAnotherTwoTeamsProblem().count(vector <int>(skill, skill + (sizeof skill / sizeof skill[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int skill[]               = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = YetAnotherTwoTeamsProblem().count(vector <int>(skill, skill + (sizeof skill / sizeof skill[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int skill[]               = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = YetAnotherTwoTeamsProblem().count(vector <int>(skill, skill + (sizeof skill / sizeof skill[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int skill[]               = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = YetAnotherTwoTeamsProblem().count(vector <int>(skill, skill + (sizeof skill / sizeof skill[0])));
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
