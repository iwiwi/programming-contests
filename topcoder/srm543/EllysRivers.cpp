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

struct EllysRivers {
  double getMin(int length, int walk, vector <int> width, vector <int> speed);
};

double dp[2][100010];

inline double sqr(double x) { return x * x; }

double EllysRivers::getMin(int L, int walk, vector <int> width, vector <int> speed) {
  double *crr = dp[0], *nxt = dp[1];
  for (int y = 0; y <= L; ++y) crr[y] = double(y) / walk;

  rep (i, width.size()) {
    double w = width[i];
    double s = speed[i];

    int y = 0;
    for (int ty = 0; ty <= L; ++ty) {
      double td = crr[y] + sqrt(sqr(w) + sqr(ty - y)) / s;
      while (y + 1 <= L) {
        double ttd = crr[y + 1] + sqrt(sqr(w) + sqr(ty - (y + 1))) / s;
        if (ttd < td) {
          y = y + 1;
          td = ttd;
        } else {
          break;
        }
      }
      nxt[ty] = td;
    }

    for (int y = 0; y + 1 <= L; ++y) nxt[y + 1] = min(nxt[y + 1], nxt[y] + 1.0 / walk);
    for (int y = L; y - 1 >= 0; --y) nxt[y - 1] = min(nxt[y - 1], nxt[y] + 1.0 / walk);
    swap(crr, nxt);
  }

  return crr[L];
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
			int length                = 10;
			int walk                  = 3;
			int width[]               = {5, 2, 3};
			int speed[]               = {5, 2, 7};
			double expected__         = 3.231651964071508;

			clock_t start__           = clock();
			double received__         = EllysRivers().getMin(length, walk, vector <int>(width, width + (sizeof width / sizeof width[0])), vector <int>(speed, speed + (sizeof speed / sizeof speed[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int length                = 10000;
			int walk                  = 211;
			int width[]               = {911};
			int speed[]               = {207};
			double expected__         = 48.24623664712219;

			clock_t start__           = clock();
			double received__         = EllysRivers().getMin(length, walk, vector <int>(width, width + (sizeof width / sizeof width[0])), vector <int>(speed, speed + (sizeof speed / sizeof speed[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int length                = 1337;
			int walk                  = 2;
			int width[]               = {100, 200, 300, 400};
			int speed[]               = {11, 12, 13, 14};
			double expected__         = 128.57830549575695;

			clock_t start__           = clock();
			double received__         = EllysRivers().getMin(length, walk, vector <int>(width, width + (sizeof width / sizeof width[0])), vector <int>(speed, speed + (sizeof speed / sizeof speed[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int length                = 77;
			int walk                  = 119;
			int width[]               = {11, 12, 13, 14};
			int speed[]               = {100, 200, 300, 400};
			double expected__         = 0.3842077071089629;

			clock_t start__           = clock();
			double received__         = EllysRivers().getMin(length, walk, vector <int>(width, width + (sizeof width / sizeof width[0])), vector <int>(speed, speed + (sizeof speed / sizeof speed[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int length                = 7134;
			int walk                  = 1525;
			int width[]               = {11567, 19763, 11026, 10444, 24588, 22263, 17709, 11181, 15292, 28895, 15039, 18744, 19985, 13795, 26697, 18812, 25655, 13620, 28926, 12393};
			int speed[]               = {1620, 1477, 2837, 2590, 1692, 2270, 1655, 1078, 2683, 1475, 1383, 1153, 1862, 1770, 1671, 2318, 2197, 1768, 1979, 1057};
			double expected__         = 214.6509731258811;

			clock_t start__           = clock();
			double received__         = EllysRivers().getMin(length, walk, vector <int>(width, width + (sizeof width / sizeof width[0])), vector <int>(speed, speed + (sizeof speed / sizeof speed[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int length                = ;
			int walk                  = ;
			int width[]               = ;
			int speed[]               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = EllysRivers().getMin(length, walk, vector <int>(width, width + (sizeof width / sizeof width[0])), vector <int>(speed, speed + (sizeof speed / sizeof speed[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int length                = ;
			int walk                  = ;
			int width[]               = ;
			int speed[]               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = EllysRivers().getMin(length, walk, vector <int>(width, width + (sizeof width / sizeof width[0])), vector <int>(speed, speed + (sizeof speed / sizeof speed[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int length                = ;
			int walk                  = ;
			int width[]               = ;
			int speed[]               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = EllysRivers().getMin(length, walk, vector <int>(width, width + (sizeof width / sizeof width[0])), vector <int>(speed, speed + (sizeof speed / sizeof speed[0])));
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
