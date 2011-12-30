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

struct Cut {
  int getMaximum(vector <int> eelLengths, int maxCuts);
};



int Cut::getMaximum(vector <int> A, int C) {
  int ans = 0;

  // mul of 10
  for (;;) {
    int best_i = -1, best_a = INT_MAX;
    rep (i, A.size()) {
      if (A[i] % 10 == 0 && A[i] < best_a) {
        best_a = A[i];
        best_i = i;
      }
    }
    if (best_i == -1) break;

    while (C > 0 && A[best_i] > 10) {
      A[best_i] -= 10;
      --C;
      ++ans;
    }

    if (A[best_i] == 10) {
      A.erase(A.begin() + best_i);
      ++ans;
    }

    if (C == 0) break;
  }

  // rest
  rep (i, A.size()) {
    while (C > 0 && A[i] > 10) {
      A[i] -= 10;
      --C;
      ++ans;
    }
  }

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
			int eelLengths[]          = {13, 20, 13};
			int maxCuts               = 2;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = Cut().getMaximum(vector <int>(eelLengths, eelLengths + (sizeof eelLengths / sizeof eelLengths[0])), maxCuts);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int eelLengths[]          = {5, 5, 5, 5};
			int maxCuts               = 2;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = Cut().getMaximum(vector <int>(eelLengths, eelLengths + (sizeof eelLengths / sizeof eelLengths[0])), maxCuts);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int eelLengths[]          = {34, 10, 48};
			int maxCuts               = 4;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = Cut().getMaximum(vector <int>(eelLengths, eelLengths + (sizeof eelLengths / sizeof eelLengths[0])), maxCuts);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int eelLengths[]          = {30, 50, 30, 50};
			int maxCuts               = 350;
			int expected__            = 16;

			clock_t start__           = clock();
			int received__            = Cut().getMaximum(vector <int>(eelLengths, eelLengths + (sizeof eelLengths / sizeof eelLengths[0])), maxCuts);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int eelLengths[]          = ;
			int maxCuts               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Cut().getMaximum(vector <int>(eelLengths, eelLengths + (sizeof eelLengths / sizeof eelLengths[0])), maxCuts);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int eelLengths[]          = ;
			int maxCuts               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Cut().getMaximum(vector <int>(eelLengths, eelLengths + (sizeof eelLengths / sizeof eelLengths[0])), maxCuts);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int eelLengths[]          = ;
			int maxCuts               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Cut().getMaximum(vector <int>(eelLengths, eelLengths + (sizeof eelLengths / sizeof eelLengths[0])), maxCuts);
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
