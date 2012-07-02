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
#include <bitset>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

struct KingdomAndDice {
  double newFairness(vector <int> firstDie, vector <int> secondDie, int X);
};

typedef bitset<2600> bs_t;

double KingdomAndDice::newFairness(vector <int> firstDie, vector <int> secondDie, int X) {
  int N = firstDie.size();

  vector<int> vs;
  vs.insert(vs.end(), all(firstDie));
  vs.insert(vs.end(), all(secondDie));
  vs.pb(0);
  vs.pb(X + 1);
  sort(all(vs));

  vector<pair<int, int> > nums;
  rep (i, vs.size() - 1) {
    int c = vs[i + 1] - vs[i] - 1;
    if (c <= 0) continue;
    int v = vs[i] + 1, w = 0;
    rep (j, N) if (v > secondDie[j]) ++w;
    nums.pb(mp(c, w));
    // printf("[%d, %d]: %d %d\n", vs[i] + 1, vs[i + 1] - 1, c, w);
  }

  int base_w = 0, Z;
  Z = count(all(firstDie), 0);
  rep (i, N) rep (j, N) if (firstDie[i] > secondDie[j]) ++base_w;

  bs_t crr[60];
  crr[0][base_w] = true;
  rep (i, nums.size()) {
    int c = nums[i].first, w = nums[i].second;

    bs_t nxt[60];
    for (int a = 0; a <= Z; ++a) {
      for (int b = 0; a + b <= Z && b <= c; ++b) {
        nxt[a + b] |= crr[a] << (b * w);
      }
    }

    for (int k = 0; k <= Z; ++k) crr[k] = nxt[k];
  }

  pair<int, int> best(INT_MAX, -1);
  for (int k = 0; k <= Z; ++k) {
    for (int w = 0; w <= N * N; ++w) {
      if (crr[k][w]) {
        int d = abs(2 * w - N * N);
        best = min(best, mp(d, w));
      }
    }
  }

  printf("%d %d\n", best.first, best.second);
  return best.second / double(N * N);
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
			int firstDie[]            = {0, 2, 7, 0};
			int secondDie[]           = {6, 3, 8, 10};
			int X                     = 12;
			double expected__         = 0.4375;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int firstDie[]            = {0, 2, 7, 0};
			int secondDie[]           = {6, 3, 8, 10};
			int X                     = 10;
			double expected__         = 0.375;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int firstDie[]            = {0, 0};
			int secondDie[]           = {5, 8};
			int X                     = 47;
			double expected__         = 0.5;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int firstDie[]            = {19, 50, 4};
			int secondDie[]           = {26, 100, 37};
			int X                     = 1000;
			double expected__         = 0.2222222222222222;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int firstDie[]            = {6371, 0, 6256, 1852, 0, 0, 6317, 3004, 5218, 9012};
			int secondDie[]           = {1557, 6318, 1560, 4519, 2012, 6316, 6315, 1559, 8215, 1561};
			int X                     = 10000;
			double expected__         = 0.49;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int firstDie[]            = ;
			int secondDie[]           = ;
			int X                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int firstDie[]            = ;
			int secondDie[]           = ;
			int X                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int firstDie[]            = ;
			int secondDie[]           = ;
			int X                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
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
