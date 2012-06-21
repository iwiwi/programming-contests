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

struct StrIIRec {
  string recovstr(int n, int minInv, string minStr);
};

int N;
int minInv;
string minStr;

bool check(string pfx) {
  bool usd[256] = {};
  rep (i, pfx.size()) {
    if (usd[pfx[i]]) return false;
    usd[pfx[i]] = true;
  }
  for (int i = pfx.size(); i < N; ++i) {
    for (char c = 'a' + N - 1; c >= 'a'; --c) {
      if (!usd[c]) {
        usd[c] = true;
        pfx += c;
        break;
      }
    }
  }

  if (pfx < minStr) return false;

  int inv = 0;
  rep (j, N) rep (i, j) if (pfx[i] > pfx[j]) ++inv;
  if (inv < minInv) return false;

  return true;
}


string StrIIRec::recovstr(int n, int minInv, string minStr) {
  ::N = n;
  ::minInv = minInv;
  ::minStr = minStr;

  string s = "";
  rep (i, n) {
    for (char c = 'a'; c <= 'z'; ++c) {
      if (check(s + c)) {
        s += c;
        goto ok;
      }
    }
    return "";
 ok:;
  }
  return s;
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
			int n                     = 2;
			int minInv                = 1;
			string minStr             = "ab";
			string expected__         = "ba";

			clock_t start__           = clock();
			string received__         = StrIIRec().recovstr(n, minInv, minStr);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 9;
			int minInv                = 1;
			string minStr             = "efcdgab";
			string expected__         = "efcdgabhi";

			clock_t start__           = clock();
			string received__         = StrIIRec().recovstr(n, minInv, minStr);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 11;
			int minInv                = 55;
			string minStr             = "debgikjfc";
			string expected__         = "kjihgfedcba";

			clock_t start__           = clock();
			string received__         = StrIIRec().recovstr(n, minInv, minStr);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 15;
			int minInv                = 0;
			string minStr             = "e";
			string expected__         = "eabcdfghijklmno";

			clock_t start__           = clock();
			string received__         = StrIIRec().recovstr(n, minInv, minStr);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 9;
			int minInv                = 20;
			string minStr             = "fcdebiha";
			string expected__         = "fcdehigba";

			clock_t start__           = clock();
			string received__         = StrIIRec().recovstr(n, minInv, minStr);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int n                     = ;
			int minInv                = ;
			string minStr             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = StrIIRec().recovstr(n, minInv, minStr);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int n                     = ;
			int minInv                = ;
			string minStr             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = StrIIRec().recovstr(n, minInv, minStr);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int n                     = ;
			int minInv                = ;
			string minStr             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = StrIIRec().recovstr(n, minInv, minStr);
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
