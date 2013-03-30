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

typedef long long ll;

inline ll absll(ll x) {
  return x >= 0 ? x : -x;
}

inline ll div_less(ll a, ll b) {  // x < a/b
  return (a < 0) ^ (b < 0) ? -absll(a) / absll(b) - 1 : (absll(a) + absll(b) - 1) / absll(b) - 1;
}

inline ll div_more(ll a, ll b) {  // a/b < x
  return (a < 0) ^ (b < 0) ? -(absll(a) + absll(b) - 1) / absll(b) + 1 : absll(a) / absll(b) + 1;
}

struct TheFrog {
  double getMinimum(int D, vector <int> L, vector <int> R);
};

double TheFrog::getMinimum(int D, vector <int> L, vector <int> R) {
  vector<int> ps;
  ps.insert(ps.end(), all(L));
  ps.insert(ps.end(), all(R));

  vector<pair<int, int> > v;
  rep (i, ps.size()) {
    int p = ps[i];
    for (int d = 1; d <= p; ++d) {
      int g = __gcd(p, d);
      v.pb(mp(p / g, d / g));
    }
  }
  sort(all(v));
  v.erase(unique(all(v)), v.end());

  double ans = 1E30;
  rep (i, v.size()) {
    ll n = v[i].first, d = v[i].second;
    // printf("%f\n", n / double(d));
    rep (i, L.size()) {
      ll l = L[i], r = R[i];
      if (div_more(d * l, n) <= div_less(d * r, n)) goto dmp;
    }
    ans = min(ans, n / double(d));
 dmp:;
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
			int D                     = 16;
			int L[]                   = {2};
			int R[]                   = {7};
			double expected__         = 7.0;

			clock_t start__           = clock();
			double received__         = TheFrog().getMinimum(D, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int D                     = 25;
			int L[]                   = {11, 3};
			int R[]                   = {21, 7};
			double expected__         = 10.5;

			clock_t start__           = clock();
			double received__         = TheFrog().getMinimum(D, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int D                     = 100;
			int L[]                   = {0};
			int R[]                   = {100};
			double expected__         = 100.0;

			clock_t start__           = clock();
			double received__         = TheFrog().getMinimum(D, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int D                     = 100;
			int L[]                   = {0, 50};
			int R[]                   = {50, 100};
			double expected__         = 50.0;

			clock_t start__           = clock();
			double received__         = TheFrog().getMinimum(D, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int D                     = 30000;
			int L[]                   = {17, 25281, 5775, 2825, 14040};
			int R[]                   = {55, 26000, 5791, 3150, 14092};
			double expected__         = 787.8787878787879;

			clock_t start__           = clock();
			double received__         = TheFrog().getMinimum(D, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int D                     = ;
			int L[]                   = ;
			int R[]                   = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheFrog().getMinimum(D, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int D                     = ;
			int L[]                   = ;
			int R[]                   = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheFrog().getMinimum(D, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int D                     = ;
			int L[]                   = ;
			int R[]                   = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheFrog().getMinimum(D, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
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
