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

struct PatrolRoute {
  int countRoutes(int X, int Y, int minT, int maxT);
};

typedef long long ll;
const ll MOD = 1000000007;

int PatrolRoute::countRoutes(int X, int Y, int minT, int maxT) {
  ll ans = 0;

  for (int w = 3; w <= X; ++w) {
    for (int h = 3; h <= Y; ++h) {
      int t = (w + h - 2) * 2;

      if (minT <= t && t <= maxT) {
        ll x = ll(X - w + 1) * ll(Y - h + 1) * 6;
        x *= (w - 2);
        x *= (h - 2);
        (ans += x) %= MOD;
      }
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
			int X                     = 3;
			int Y                     = 3;
			int minT                  = 1;
			int maxT                  = 20000;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int X                     = 3;
			int Y                     = 3;
			int minT                  = 4;
			int maxT                  = 7;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int X                     = 4;
			int Y                     = 6;
			int minT                  = 9;
			int maxT                  = 12;
			int expected__            = 264;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int X                     = 7;
			int Y                     = 5;
			int minT                  = 13;
			int maxT                  = 18;
			int expected__            = 1212;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int X                     = 4000;
			int Y                     = 4000;
			int minT                  = 4000;
			int maxT                  = 14000;
			int expected__            = 859690013;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int X                     = ;
			int Y                     = ;
			int minT                  = ;
			int maxT                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int X                     = ;
			int Y                     = ;
			int minT                  = ;
			int maxT                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int X                     = ;
			int Y                     = ;
			int minT                  = ;
			int maxT                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
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
