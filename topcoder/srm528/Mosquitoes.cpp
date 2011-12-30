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

struct Mosquitoes {
  int getMaximum(vector <int> xInit, vector <int> v, int R);
};

const double EPS = 1E-10;

int Mosquitoes::getMaximum(vector <int> X, vector <int> V, int R) {
  int N = X.size();
  int ans = 1;
  rep (i, N) rep (j, N) if (i != j) {
    // (X[i] + V[i] * t) - (X[j] + V[j] * t) = 2 * R
    // (V[i] - V[j]) * t = 2 * R + X[j] - X[i]

    double t;
    if (V[i] == V[j]) t = 0.0;
    else t = (2 * R + X[j] - X[i]) / (double)(V[i] - V[j]);
    if (t < -EPS) continue;

    double x0 = X[i] + V[i] * t - R;

    int tmp = 0;
    rep (k, N) {
      double x = X[k] + V[k] * t;
      if (fabs(x - x0) < R + EPS) ++tmp;
    }
    ans = max(ans, tmp);
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
			int xInit[]               = {1, -1};
			int v[]                   = {1, -1};
			int R                     = 10;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = Mosquitoes().getMaximum(vector <int>(xInit, xInit + (sizeof xInit / sizeof xInit[0])), vector <int>(v, v + (sizeof v / sizeof v[0])), R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int xInit[]               = {100, -100};
			int v[]                   = {1, -1};
			int R                     = 10;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = Mosquitoes().getMaximum(vector <int>(xInit, xInit + (sizeof xInit / sizeof xInit[0])), vector <int>(v, v + (sizeof v / sizeof v[0])), R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int xInit[]               = {0, -1, 10, -11, 99, -99};
			int v[]                   = {1, -1, -3, 3, 47, -47};
			int R                     = 3;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = Mosquitoes().getMaximum(vector <int>(xInit, xInit + (sizeof xInit / sizeof xInit[0])), vector <int>(v, v + (sizeof v / sizeof v[0])), R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int xInit[]               = {5};
			int v[]                   = {2};
			int R                     = 8;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = Mosquitoes().getMaximum(vector <int>(xInit, xInit + (sizeof xInit / sizeof xInit[0])), vector <int>(v, v + (sizeof v / sizeof v[0])), R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int xInit[]               = {12,34,56,78,90};
			int v[]                   = {-1,2,-3,4,-5};
			int R                     = 6;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = Mosquitoes().getMaximum(vector <int>(xInit, xInit + (sizeof xInit / sizeof xInit[0])), vector <int>(v, v + (sizeof v / sizeof v[0])), R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int xInit[]               = ;
			int v[]                   = ;
			int R                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Mosquitoes().getMaximum(vector <int>(xInit, xInit + (sizeof xInit / sizeof xInit[0])), vector <int>(v, v + (sizeof v / sizeof v[0])), R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int xInit[]               = ;
			int v[]                   = ;
			int R                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Mosquitoes().getMaximum(vector <int>(xInit, xInit + (sizeof xInit / sizeof xInit[0])), vector <int>(v, v + (sizeof v / sizeof v[0])), R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int xInit[]               = ;
			int v[]                   = ;
			int R                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Mosquitoes().getMaximum(vector <int>(xInit, xInit + (sizeof xInit / sizeof xInit[0])), vector <int>(v, v + (sizeof v / sizeof v[0])), R);
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
