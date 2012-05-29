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

struct ElectionFraudDiv1 {
  int MinimumVoters(vector <int> percentages);
};

typedef long long ll;

ll absll(ll x) {
  return x >= 0 ? x : -x;
}

ll div_at_least(ll a, ll b) {  // a/b <= x
  return (a < 0) ^ (b < 0) ? -absll(a) / absll(b) : (absll(a) + absll(b) - 1) / absll(b);
}

ll div_less(ll a, ll b) {  // x < a/b
  return (a < 0) ^ (b < 0) ? -absll(a) / absll(b) - 1 : (absll(a) + absll(b) - 1) / absll(b) - 1;
}

int ElectionFraudDiv1::MinimumVoters(vector <int> percentages) {
  int N = percentages.size();

  for (ll m = 1; m <= 20000; ++m) {
    ll mi = 0, ma = 0;
    rep (i, N) {
      ll p = percentages[i];
      ll a = (2 * p - 1) * m, b = (2 * p + 1) * m;
      ll l = max(0LL, div_at_least(a, 200));
      ll r = max(0LL, div_less(b, 200));
      if (r < l) goto dmp;
      mi += l;
      ma += r;
    }
    if (mi <= m && m <= ma) return m;
 dmp:;
  }

  return -1;
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
			int percentages[]         = {33, 33, 33};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int percentages[]         = {29, 29, 43};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int percentages[]         = {12, 12, 12, 12, 12, 12, 12, 12};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int percentages[]         = {13, 13, 13, 13, 13, 13, 13, 13};
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int percentages[]         = {0, 1, 100};
			int expected__            = 200;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int percentages[]         = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4};
			int expected__            = 97;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
        int percentages[]         = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 100};
        int expected__            = -1;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 7: {
			int percentages[]         = {0, 0, 0, 75, 0, 0, 0, 25, 0, 0, 0, 0, 0};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 8: {
			int percentages[]         = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
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
