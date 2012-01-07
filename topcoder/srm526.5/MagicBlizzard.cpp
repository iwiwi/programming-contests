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

struct MagicBlizzard {
  double expectation(vector <int> range, vector <int> amount);
};

typedef long long ll;

ll area(ll r) {
  return (2 * r + 1) * (2 * r + 1);
}

double MagicBlizzard::expectation(vector <int> range, vector <int> amount) {
  vector<int> rs(range);
  sort(all(rs));
  rs.erase(unique(all(rs)), rs.end());

  double ans = 0.0;
  ll done = 0;
  rep (ri, rs.size()) {
    ll r = rs[ri];
    ll s = area(r) - done;

    double tot_v = 0.0, tot_e = 0.0;
    rep (i, range.size()) {
      if (r <= range[i]) {
        double n = amount[i];
        double p = 1.0 / area(range[i]);

        double e = n * p;
        double v = n * p * (1 - p);

        tot_e += e;
        tot_v += v;
      }
    }

    double tot_e2 = tot_e * tot_e;
    ans += (tot_v + tot_e2) * s;

    done += s;
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
			int range[]               = {1,0};
			int amount[]              = {1,1};
			double expected__         = 2.2222222222222223;

			clock_t start__           = clock();
			double received__         = MagicBlizzard().expectation(vector <int>(range, range + (sizeof range / sizeof range[0])), vector <int>(amount, amount + (sizeof amount / sizeof amount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int range[]               = {1,0};
			int amount[]              = {2,1};
			double expected__         = 3.666666666666667;

			clock_t start__           = clock();
			double received__         = MagicBlizzard().expectation(vector <int>(range, range + (sizeof range / sizeof range[0])), vector <int>(amount, amount + (sizeof amount / sizeof amount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int range[]               = {5,2,6,5};
			int amount[]              = {1,2,2,3};
			double expected__         = 8.46525111252384;

			clock_t start__           = clock();
			double received__         = MagicBlizzard().expectation(vector <int>(range, range + (sizeof range / sizeof range[0])), vector <int>(amount, amount + (sizeof amount / sizeof amount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int range[]               = {7,11,2,13,3,19,5,17};
			int amount[]              = {16,8,4,15,12,9,10,6};
			double expected__         = 98.55659436211914;

			clock_t start__           = clock();
			double received__         = MagicBlizzard().expectation(vector <int>(range, range + (sizeof range / sizeof range[0])), vector <int>(amount, amount + (sizeof amount / sizeof amount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int range[]               = {0,0,0,0,0,0,0,0,0,0};
			int amount[]              = {10000,10000,10000,10000,10000,10000,10000,10000,10000,10000};
			double expected__         = 1.0E10;

			clock_t start__           = clock();
			double received__         = MagicBlizzard().expectation(vector <int>(range, range + (sizeof range / sizeof range[0])), vector <int>(amount, amount + (sizeof amount / sizeof amount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int range[]               = ;
			int amount[]              = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = MagicBlizzard().expectation(vector <int>(range, range + (sizeof range / sizeof range[0])), vector <int>(amount, amount + (sizeof amount / sizeof amount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int range[]               = ;
			int amount[]              = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = MagicBlizzard().expectation(vector <int>(range, range + (sizeof range / sizeof range[0])), vector <int>(amount, amount + (sizeof amount / sizeof amount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int range[]               = ;
			int amount[]              = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = MagicBlizzard().expectation(vector <int>(range, range + (sizeof range / sizeof range[0])), vector <int>(amount, amount + (sizeof amount / sizeof amount[0])));
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
