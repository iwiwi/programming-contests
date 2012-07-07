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

struct SRMIntermissionPhase {
  int countWays(vector <int> points, vector <string> description);
};

typedef long long ll;

const int MOD = 1000000007;

int pre[1 << 3][200010];
int dp[2][200010];

int SRMIntermissionPhase::countWays(vector <int> points, vector <string> description) {
  int P = accumulate(all(points), 0) + 5;

  rep (b, 1 << 3) {
    int *prv = dp[0], *crr = dp[1];
    for (int x = 0; x <= P; ++x) prv[x] = 1;

    rep (i, 3) if (b & (1 << i)) {
      int p = points[i];
      for (int x = 0; x <= P; ++x) {
        crr[x] = x == 0 ? 0 : crr[x - 1];
        if (0 <= x - 1    ) crr[x] = (crr[x] + prv[x - 1]    ) % MOD;
        if (0 <= x - p - 1) crr[x] = (crr[x] - prv[x - p - 1]) % MOD;
      }
      swap(prv, crr);
    }

    int t = 0;
    for (int x = 0; x <= P; ++x) {
      pre[b][x] = (prv[x] - t) % MOD;
      t = prv[x];
    }
  }

  {
    int *prv = dp[0], *crr = dp[1];
    for (int x = 0; x <= P; ++x) prv[x] = 1;

    for (int i = description.size() - 1; i >= 0; --i) {
      int b = 0;
      rep (j, 3) b |= (description[i][j] == 'Y') << j;

      crr[0] = 0;
      for (int x = 1; x <= P; ++x) {
        crr[x] = crr[x - 1];
        crr[x] = (crr[x] + pre[b][x - 1] * (ll)prv[x - 1]) % MOD;
      }
      swap(crr, prv);
    }

    return (prv[P] + MOD) % MOD;
  }
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

	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) {
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
			cerr << "    Expected: " << expected << endl;
			cerr << "    Received: " << received << endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int points[]              = {25000, 50000, 100000};
			string description[]      = {"YNN",
 "NNN"};
			int expected__            = 25000;

			clock_t start__           = clock();
			int received__            = SRMIntermissionPhase().countWays(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <string>(description, description + (sizeof description / sizeof description[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int points[]              = {30000, 60000, 90000};
			string description[]      = {"NYN",
 "NYN"};
			int expected__            = 799969993;

			clock_t start__           = clock();
			int received__            = SRMIntermissionPhase().countWays(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <string>(description, description + (sizeof description / sizeof description[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int points[]              = {25000, 45000, 110000};
			string description[]      = {"NNN",
 "YYY"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = SRMIntermissionPhase().countWays(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <string>(description, description + (sizeof description / sizeof description[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int points[]              = {25600, 51200, 102400};
			string description[]      = {"NYY",
 "YNY",
 "YYY",
 "YNN",
 "YYN",
 "NNY",
 "NYN",
 "NNN"};
			int expected__            = 867560805;

			clock_t start__           = clock();
			int received__            = SRMIntermissionPhase().countWays(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <string>(description, description + (sizeof description / sizeof description[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
        int points[]              = {1, 2, 3};
			string description[]      = "NNN";
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = SRMIntermissionPhase().countWays(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <string>(description, description + (sizeof description / sizeof description[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 5: {
			int points[]              = ;
			string description[]      = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SRMIntermissionPhase().countWays(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <string>(description, description + (sizeof description / sizeof description[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int points[]              = ;
			string description[]      = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SRMIntermissionPhase().countWays(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <string>(description, description + (sizeof description / sizeof description[0])));
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
