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

struct Over9000Rocks {
  int countPossibilities(vector <int> lowerBound, vector <int> upperBound);
};



int Over9000Rocks::countPossibilities(vector <int> lowerBound, vector <int> upperBound) {
  int N = lowerBound.size();

  vector<pair<int, int> > is;
  rep (b, 1 << N) {
    int lb = 0, ub = 0;
    rep (i, N) if (b & (1 << i)) { lb += lowerBound[i]; ub += upperBound[i]; }

    ub += 1;  // [lb, ub)
    if (lb < ub) is.pb(mp(lb, ub));
  }
  sort(all(is));

  int c = 9001, ans = 0;
  rep (i, is.size()) {
    ans += max(0, is[i].second - max(is[i].first, c));
    c = max(c, is[i].second);
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
			int lowerBound[]          = {9000};
			int upperBound[]          = {9001};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = Over9000Rocks().countPossibilities(vector <int>(lowerBound, lowerBound + (sizeof lowerBound / sizeof lowerBound[0])), vector <int>(upperBound, upperBound + (sizeof upperBound / sizeof upperBound[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int lowerBound[]          = {9000, 1, 10};
			int upperBound[]          = {9000, 2, 20};
			int expected__            = 15;

			clock_t start__           = clock();
			int received__            = Over9000Rocks().countPossibilities(vector <int>(lowerBound, lowerBound + (sizeof lowerBound / sizeof lowerBound[0])), vector <int>(upperBound, upperBound + (sizeof upperBound / sizeof upperBound[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int lowerBound[]          = {1001, 2001, 3001, 3001};
			int upperBound[]          = {1003, 2003, 3003, 3003};
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = Over9000Rocks().countPossibilities(vector <int>(lowerBound, lowerBound + (sizeof lowerBound / sizeof lowerBound[0])), vector <int>(upperBound, upperBound + (sizeof upperBound / sizeof upperBound[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int lowerBound[]          = {9000,90000,1,10};
			int upperBound[]          = {9000,90000,3,15};
			int expected__            = 38;

			clock_t start__           = clock();
			int received__            = Over9000Rocks().countPossibilities(vector <int>(lowerBound, lowerBound + (sizeof lowerBound / sizeof lowerBound[0])), vector <int>(upperBound, upperBound + (sizeof upperBound / sizeof upperBound[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int lowerBound[]          = {1,1,1,1,1,1};
			int upperBound[]          = {3,4,5,6,7,8};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = Over9000Rocks().countPossibilities(vector <int>(lowerBound, lowerBound + (sizeof lowerBound / sizeof lowerBound[0])), vector <int>(upperBound, upperBound + (sizeof upperBound / sizeof upperBound[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int lowerBound[]          = ;
			int upperBound[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Over9000Rocks().countPossibilities(vector <int>(lowerBound, lowerBound + (sizeof lowerBound / sizeof lowerBound[0])), vector <int>(upperBound, upperBound + (sizeof upperBound / sizeof upperBound[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int lowerBound[]          = ;
			int upperBound[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Over9000Rocks().countPossibilities(vector <int>(lowerBound, lowerBound + (sizeof lowerBound / sizeof lowerBound[0])), vector <int>(upperBound, upperBound + (sizeof upperBound / sizeof upperBound[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int lowerBound[]          = ;
			int upperBound[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Over9000Rocks().countPossibilities(vector <int>(lowerBound, lowerBound + (sizeof lowerBound / sizeof lowerBound[0])), vector <int>(upperBound, upperBound + (sizeof upperBound / sizeof upperBound[0])));
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
