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

struct PalindromeMaker2 {
  string make(string baseString);
};



string PalindromeMaker2::make(string baseString) {
  string lef = "";
  char cen = 0;
  for (int c = 'A'; c <= 'Z'; ++c) {
    int x = count(all(baseString), c);
    lef += string(x / 2, c);
    if (x % 2 == 1) {
      if (!cen) cen = c;
      else return "";
    }
  }

  string ans = lef;
  if (cen) ans += cen;
  reverse(all(lef));
  ans += lef;
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
			string baseString         = "AABB";
			string expected__         = "ABBA";

			clock_t start__           = clock();
			string received__         = PalindromeMaker2().make(baseString);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string baseString         = "AAABB";
			string expected__         = "ABABA";

			clock_t start__           = clock();
			string received__         = PalindromeMaker2().make(baseString);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string baseString         = "ABACABA";
			string expected__         = "AABCBAA";

			clock_t start__           = clock();
			string received__         = PalindromeMaker2().make(baseString);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string baseString         = "ABCD";
			string expected__         = "";

			clock_t start__           = clock();
			string received__         = PalindromeMaker2().make(baseString);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string baseString         = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = PalindromeMaker2().make(baseString);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string baseString         = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = PalindromeMaker2().make(baseString);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string baseString         = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = PalindromeMaker2().make(baseString);
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
