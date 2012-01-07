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

struct ColorfulCookie {
  int getMaximum(vector <int> cookies, int P1, int P2);
};


int dp[60][2100];

int ColorfulCookie::getMaximum(vector<int> A, int P1, int P2) {
  int N = A.size();

  int lb = 0, ub = 2010;
  while (ub - lb > 1) {
    int M = (lb + ub) / 2;

    dp[0][0] = 0;
    for (int j = 1; j <= M; ++j) dp[0][j] = INT_MIN;

    rep (i, N) {
      for (int j = 0; j <= M; ++j) dp[i + 1][j] = INT_MIN;

      for (int j = 0; j <= M; ++j) {
        if (dp[i][j] < 0) continue;

        for (int k1 = 0; k1 * P1 <= A[i] && j + k1 <= M; ++k1) {
          int k2 = min(M - k1, (A[i] - k1 * P1) / P2);
          dp[i + 1][j + k1] = max(dp[i + 1][j + k1], dp[i][j] + k2);
        }
      }
    }

    if (dp[N][M] >= M) lb = M;
    else ub = M;
  }

  return lb * (P1 + P2);
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
			int cookies[]             = {100, 100};
			int P1                    = 50;
			int P2                    = 50;
			int expected__            = 200;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int cookies[]             = {50, 250, 50};
			int P1                    = 50;
			int P2                    = 100;
			int expected__            = 300;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int cookies[]             = {2000};
			int P1                    = 100;
			int P2                    = 200;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int cookies[]             = {123, 456, 789, 555};
			int P1                    = 58;
			int P2                    = 158;
			int expected__            = 1728;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int cookies[]             = ;
			int P1                    = ;
			int P2                    = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int cookies[]             = ;
			int P1                    = ;
			int P2                    = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int cookies[]             = ;
			int P1                    = ;
			int P2                    = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
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
