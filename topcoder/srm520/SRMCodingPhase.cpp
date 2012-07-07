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

struct SRMCodingPhase {
  int countScore(vector <int> points, vector <int> skills, int luck);
};



int SRMCodingPhase::countScore(vector <int> points, vector <int> skills, int luck) {
  const int T = 75;

  vector<int> ord(3);
  rep (i, 3) ord[i] = i;

  int ans = 0;
  do {
    for (int x0 = 0; x0 < skills[0] && x0 <= luck; ++x0) {
      for (int x1 = 0; x1 < skills[1] && x0 + x1 <= luck; ++x1) {
        for (int x2 = 0; x2 < skills[2] && x0 + x1 + x2 <= luck; ++x2) {
          int t[3] = {skills[0] - x0, skills[1] - x1, skills[2] - x2};

          int tt = 0, p = 0;
          rep (i, 3) {
            int k = ord[i];
            if (tt + t[k] > T) break;
            p += max(0, points[k] - (2 << k) * t[k]);
            tt += t[k];
          }
          ans = max(ans, p);
        }
      }
    }
  } while (next_permutation(all(ord)));

  return ans;
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
			int points[]              = {250, 500, 1000};
			int skills[]              = {10, 25, 40};
			int luck                  = 0;
			int expected__            = 1310;

			clock_t start__           = clock();
			int received__            = SRMCodingPhase().countScore(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <int>(skills, skills + (sizeof skills / sizeof skills[0])), luck);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int points[]              = {300, 600, 900};
			int skills[]              = {30, 65, 90};
			int luck                  = 25;
			int expected__            = 680;

			clock_t start__           = clock();
			int received__            = SRMCodingPhase().countScore(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <int>(skills, skills + (sizeof skills / sizeof skills[0])), luck);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int points[]              = {250, 550, 950};
			int skills[]              = {10, 25, 40};
			int luck                  = 75;
			int expected__            = 1736;

			clock_t start__           = clock();
			int received__            = SRMCodingPhase().countScore(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <int>(skills, skills + (sizeof skills / sizeof skills[0])), luck);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int points[]              = {256, 512, 1024};
			int skills[]              = {35, 30, 25};
			int luck                  = 0;
			int expected__            = 1216;

			clock_t start__           = clock();
			int received__            = SRMCodingPhase().countScore(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <int>(skills, skills + (sizeof skills / sizeof skills[0])), luck);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int points[]              = {300, 600, 1100};
			int skills[]              = {80, 90, 100};
			int luck                  = 4;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = SRMCodingPhase().countScore(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <int>(skills, skills + (sizeof skills / sizeof skills[0])), luck);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int points[]              = ;
			int skills[]              = ;
			int luck                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SRMCodingPhase().countScore(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <int>(skills, skills + (sizeof skills / sizeof skills[0])), luck);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int points[]              = ;
			int skills[]              = ;
			int luck                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SRMCodingPhase().countScore(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <int>(skills, skills + (sizeof skills / sizeof skills[0])), luck);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int points[]              = ;
			int skills[]              = ;
			int luck                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SRMCodingPhase().countScore(vector <int>(points, points + (sizeof points / sizeof points[0])), vector <int>(skills, skills + (sizeof skills / sizeof skills[0])), luck);
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
