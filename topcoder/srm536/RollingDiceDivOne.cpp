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

struct RollingDiceDivOne {
  long long mostLikely(vector <int> dice);
};

typedef long long ll;

long long RollingDiceDivOne::mostLikely(vector <int> dice_) {
  vector<ll> D(all(dice_));
  int N = D.size();

  ll ma = *max_element(all(D));
  ll su = accumulate(all(D), 0LL);

  ll r1 = su - ma + 1;
  ll r2 = (N + su) / 2;
  return min(r1, r2);
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

	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) {
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
			int dice[]                = {6, 6, 8};
			long long expected__      = 11;

			clock_t start__           = clock();
			long long received__      = RollingDiceDivOne().mostLikely(vector <int>(dice, dice + (sizeof dice / sizeof dice[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int dice[]                = {10};
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = RollingDiceDivOne().mostLikely(vector <int>(dice, dice + (sizeof dice / sizeof dice[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int dice[]                = {2, 3, 4, 5};
			long long expected__      = 9;

			clock_t start__           = clock();
			long long received__      = RollingDiceDivOne().mostLikely(vector <int>(dice, dice + (sizeof dice / sizeof dice[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int dice[]                = {1, 10, 1};
			long long expected__      = 3;

			clock_t start__           = clock();
			long long received__      = RollingDiceDivOne().mostLikely(vector <int>(dice, dice + (sizeof dice / sizeof dice[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int dice[]                = {382828264, 942663792, 291832707, 887961277, 546603677, 545185615, 146267547, 6938117, 167567032, 84232402, 700781193, 452172304, 816532384, 951089120, 448136091, 280899512, 256093435, 39595226, 631504901, 154772240};
			long long expected__      = 4366828428LL;

			clock_t start__           = clock();
			long long received__      = RollingDiceDivOne().mostLikely(vector <int>(dice, dice + (sizeof dice / sizeof dice[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int dice[]                = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = RollingDiceDivOne().mostLikely(vector <int>(dice, dice + (sizeof dice / sizeof dice[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int dice[]                = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = RollingDiceDivOne().mostLikely(vector <int>(dice, dice + (sizeof dice / sizeof dice[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int dice[]                = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = RollingDiceDivOne().mostLikely(vector <int>(dice, dice + (sizeof dice / sizeof dice[0])));
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
