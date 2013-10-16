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

class GUMIAndSongsDiv1 {
 public:
  int maxSongs(vector <int> duration, vector <int> tone, int T);
};

int dp[60][60];

int GUMIAndSongsDiv1::maxSongs(vector <int> duration, vector <int> tone, int T) {
  int N = duration.size();
  vector<pair<int, int> > S(N);
  rep (i, N) S[i] = {tone[i], duration[i]};
  sort(all(S));

  int ans = 0;
  rep (i, N) {
    // Start from song |i|
    for (int k = 0; k <= N; ++k) dp[i][k] = T + 10;
    dp[i][1] = S[i].second;

    // Next to song |j|
    rep (j, i) for (int k = 1; k <= N; ++k) {
      dp[i][k] = min(dp[i][k], dp[j][k - 1] + (S[i].first - S[j].first) + S[i].second);
    }

    // End?
    for (int k = 0; k <= N; ++k) if (dp[i][k] <= T) ans = max(ans, k);
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
			int duration[]            = {3, 5, 4, 11};
			int tone[]                = {2, 1, 3, 1};
			int T                     = 17;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = GUMIAndSongsDiv1().maxSongs(vector <int>(duration, duration + (sizeof duration / sizeof duration[0])), vector <int>(tone, tone + (sizeof tone / sizeof tone[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int duration[]            = {100, 200, 300};
			int tone[]                = {1, 2, 3};
			int T                     = 99;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = GUMIAndSongsDiv1().maxSongs(vector <int>(duration, duration + (sizeof duration / sizeof duration[0])), vector <int>(tone, tone + (sizeof tone / sizeof tone[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int duration[]            = {1, 2, 3, 4};
			int tone[]                = {1, 1, 1, 1};
			int T                     = 100;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = GUMIAndSongsDiv1().maxSongs(vector <int>(duration, duration + (sizeof duration / sizeof duration[0])), vector <int>(tone, tone + (sizeof tone / sizeof tone[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int duration[]            = {9, 11, 13, 17};
			int tone[]                = {2, 1, 3, 4};
			int T                     = 20;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = GUMIAndSongsDiv1().maxSongs(vector <int>(duration, duration + (sizeof duration / sizeof duration[0])), vector <int>(tone, tone + (sizeof tone / sizeof tone[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int duration[]            = {87,21,20,73,97,57,12,80,86,97,98,85,41,12,89,15,41,17,68,37,21,1,9,65,4, 67,38,91,46,82,7,98,21,70,99,41,21,65,11,1,8,12,77,62,52,69,56,33,98,97};
			int tone[]                = {88,27,89,2,96,32,4,93,89,50,58,70,15,48,31,2,27,20,31,3,23,86,69,12,59, 61,85,67,77,34,29,3,75,42,50,37,56,45,51,68,89,17,4,47,9,14,29,59,43,3};
			int T                     = 212;
			int expected__            = 12;

			std::clock_t start__      = std::clock();
			int received__            = GUMIAndSongsDiv1().maxSongs(vector <int>(duration, duration + (sizeof duration / sizeof duration[0])), vector <int>(tone, tone + (sizeof tone / sizeof tone[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int duration[]            = ;
			int tone[]                = ;
			int T                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GUMIAndSongsDiv1().maxSongs(vector <int>(duration, duration + (sizeof duration / sizeof duration[0])), vector <int>(tone, tone + (sizeof tone / sizeof tone[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int duration[]            = ;
			int tone[]                = ;
			int T                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GUMIAndSongsDiv1().maxSongs(vector <int>(duration, duration + (sizeof duration / sizeof duration[0])), vector <int>(tone, tone + (sizeof tone / sizeof tone[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int duration[]            = ;
			int tone[]                = ;
			int T                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GUMIAndSongsDiv1().maxSongs(vector <int>(duration, duration + (sizeof duration / sizeof duration[0])), vector <int>(tone, tone + (sizeof tone / sizeof tone[0])), T);
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
