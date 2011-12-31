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

struct WinningRecord {
  vector <int> getBestAndWorst(string games);
};

const double EPS = 1E-10;

vector <int> WinningRecord::getBestAndWorst(string games) {
  double mi = 1E30, ma = -1E30;
  int mi_r = 0, ma_r = 0;

  int w = 0, l = 0;
  rep (i, games.size()) {
    if (games[i] == 'W') ++w;
    else ++l;

    if (i + 1 < 3) continue;

    double t = w / double(w + l);
    if (t <= mi + EPS) { mi = t; mi_r = i + 1; }
    if (t >= ma - EPS) { ma = t; ma_r = i + 1; }
  }

  vector<int> res(2);
  res[0] = ma_r;
  res[1] = mi_r;
  return res;
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

	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, clock_t elapsed) {
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
			string games              = "WWWWWLLLLLLLLLLLLLLL";
			int expected__[]          = { 5, 20 };

			clock_t start__           = clock();
			vector <int> received__   = WinningRecord().getBestAndWorst(games);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string games              = "WWWWWW";
			int expected__[]          = { 6, 6 };

			clock_t start__           = clock();
			vector <int> received__   = WinningRecord().getBestAndWorst(games);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string games              = "LWLWLWLWLWLWLWLWLWLWLWLWLWLWLWLWLWLWLWLWLWLWLWLWLW";
			int expected__[]          = { 50, 3 };

			clock_t start__           = clock();
			vector <int> received__   = WinningRecord().getBestAndWorst(games);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string games              = "WLWLWLLWWLWLWWWWWWWLWLLLLLLLLLLLLWWLWLLWWWLLLWLWLW";
			int expected__[]          = { 19, 33 };

			clock_t start__           = clock();
			vector <int> received__   = WinningRecord().getBestAndWorst(games);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			string games              = "LWWLWWLWWLLLW";
			int expected__[]          = { 9, 12 };

			clock_t start__           = clock();
			vector <int> received__   = WinningRecord().getBestAndWorst(games);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string games              = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = WinningRecord().getBestAndWorst(games);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			string games              = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = WinningRecord().getBestAndWorst(games);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			string games              = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = WinningRecord().getBestAndWorst(games);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
