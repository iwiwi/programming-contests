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

struct FoxAndMountainEasy {
  string possible(int n, int h0, int hn, string history);
};



string FoxAndMountainEasy::possible(int n, int h0, int hn, string history) {
  puts("==========");
  int k = history.length(), y = 0, min_y = 0;
  rep (i, k) {
    y += (history[i] == 'U' ? +1 : -1);
    min_y = min(y, min_y);
  }
  int hekomi = -min_y;
  printf("hekomi = %d\n", hekomi);

  int start_u = 0;
  if (hekomi > h0) start_u = hekomi - h0;
  printf("start_u = %d\n", start_u);

  int n1 = n - k - start_u;
  int h1 = h0 + start_u + y;
  printf("n1 = %d, h1 = %d\n", n1, h1);
  if (n1 < 0) return "NO";

  int dh = hn - h1;
  printf("dh = %d\n", dh);
  if (abs(dh) <= n1 && abs(n1 % 2) == abs(dh % 2)) return "YES";
  else return "NO";
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

	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) {
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
			cerr << "    Expected: \"" << expected << "\"" << endl;
			cerr << "    Received: \"" << received << "\"" << endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int n                     = 4;
			int h0                    = 0;
			int hn                    = 4;
			string history            = "UU";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 4;
			int h0                    = 0;
			int hn                    = 4;
			string history            = "D";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 4;
			int h0                    = 100000;
			int hn                    = 100000;
			string history            = "DDU";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 4;
			int h0                    = 0;
			int hn                    = 0;
			string history            = "DDU";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 20;
			int h0                    = 20;
			int hn                    = 20;
			string history            = "UDUDUDUDUD";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int n                     = 20;
			int h0                    = 0;
			int hn                    = 0;
			string history            = "UUUUUUUUUU";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int n                     = 20;
			int h0                    = 0;
			int hn                    = 0;
			string history            = "UUUUUUUUUUU";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			int n                     = ;
			int h0                    = ;
			int hn                    = ;
			string history            = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int n                     = ;
			int h0                    = ;
			int hn                    = ;
			string history            = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int n                     = ;
			int h0                    = ;
			int hn                    = ;
			string history            = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
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
