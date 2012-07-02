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

struct KingdomAndTrees {
  int minLevel(vector <int> heights);
};

typedef long long ll;

int KingdomAndTrees::minLevel(vector <int> heights) {
  int N = heights.size();
  vector<ll> H(all(heights));

  ll lb = -1, ub = 1LL << 40;
  while (ub - lb > 1) {
    ll x = (lb + ub) / 2;

    ll h = 0;
    rep (i, N) {
      h = max(h + 1, H[i] - x);
      if (h - H[i] > x) goto ng;
    }
    ub = x;
    continue;
 ng:
    lb = x;
  }

  return ub;
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
			int heights[]             = {9, 5, 11};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = KingdomAndTrees().minLevel(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int heights[]             = {5, 8};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = KingdomAndTrees().minLevel(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int heights[]             = {1, 1, 1, 1, 1};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = KingdomAndTrees().minLevel(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int heights[]             = {548, 47, 58, 250, 2012};
			int expected__            = 251;

			clock_t start__           = clock();
			int received__            = KingdomAndTrees().minLevel(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int heights[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = KingdomAndTrees().minLevel(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int heights[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = KingdomAndTrees().minLevel(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int heights[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = KingdomAndTrees().minLevel(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
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
