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

struct MergersDivOne {
  double findMaximum(vector <int> revenues);
};



double MergersDivOne::findMaximum(vector <int> revenues) {
  vector<double> a(all(revenues));
  sort(all(a));
  reverse(all(a));
  while (a.size() >= 2) {
    double x = a.back(); a.pop_back();
    double y = a.back(); a.pop_back();
    a.push_back((x + y) / 2);
  }
  return a[0];
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

	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ(double expected, double result) { if (isnan(expected)) { return isnan(result); } else if (isinf(expected)) { if (expected > 0) { return result > 0 && isinf(result); } else { return result < 0 && isinf(result); } } else if (isnan(result) || isinf(result)) { return false; } else if (fabs(result - expected) < MAX_DOUBLE_ERROR) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }

	int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) {
		cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received);
			if (rerr > 0) {
				sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int revenues[]            = {5, -7, 3};
			double expected__         = 1.5;

			clock_t start__           = clock();
			double received__         = MergersDivOne().findMaximum(vector <int>(revenues, revenues + (sizeof revenues / sizeof revenues[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int revenues[]            = {10, -17};
			double expected__         = -3.5;

			clock_t start__           = clock();
			double received__         = MergersDivOne().findMaximum(vector <int>(revenues, revenues + (sizeof revenues / sizeof revenues[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int revenues[]            = {12, 12, 12, 12, 12};
			double expected__         = 12.0;

			clock_t start__           = clock();
			double received__         = MergersDivOne().findMaximum(vector <int>(revenues, revenues + (sizeof revenues / sizeof revenues[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int revenues[]            = {0, 0, 0, 0, 0, 100};
			double expected__         = 50.0;

			clock_t start__           = clock();
			double received__         = MergersDivOne().findMaximum(vector <int>(revenues, revenues + (sizeof revenues / sizeof revenues[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int revenues[]            = {10, -10, 100, -100, 1000, -1000};
			double expected__         = 491.25;

			clock_t start__           = clock();
			double received__         = MergersDivOne().findMaximum(vector <int>(revenues, revenues + (sizeof revenues / sizeof revenues[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int revenues[]            = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = MergersDivOne().findMaximum(vector <int>(revenues, revenues + (sizeof revenues / sizeof revenues[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int revenues[]            = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = MergersDivOne().findMaximum(vector <int>(revenues, revenues + (sizeof revenues / sizeof revenues[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int revenues[]            = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = MergersDivOne().findMaximum(vector <int>(revenues, revenues + (sizeof revenues / sizeof revenues[0])));
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
