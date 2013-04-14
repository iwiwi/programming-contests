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

struct FoxAndHandle {
  string lexSmallestName(string S);
};

string ans = "";

bool check(const string &l, const string &r) {
  int cnt[300] = {};
  rep (i, ans.length()) ++cnt[int(ans[i])];
  rep (i, r.length()) ++cnt[int(r[i])];
  rep (i, l.length()) if (--cnt[int(l[i])] < 0) return false;
  return true;
}

string FoxAndHandle::lexSmallestName(string S) {
  int N = S.length();
  int cnt[300] = {};
  rep (i, N) ++cnt[int(S[i])];

  ans = string(N / 2, '#');
  string l = "", r = S;
  rep (i, N / 2) {
    for (char c = 'a'; c <= 'z'; ++c) {
      if (cnt[int(c)] == 0) continue;

      string::size_type p = r.find(c);
      string tl = l + r.substr(0, p);
      string tr = r.substr(p + 1);

      ans[i] = c;
      if (check(tl, tr)) {
        l = tl;
        r = tr;
        cnt[int(c)] -= 2;
        break;
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
			string S                  = "foxfox";
			string expected__         = "fox";

			clock_t start__           = clock();
			string received__         = FoxAndHandle().lexSmallestName(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S                  = "ccieliel";
			string expected__         = "ceil";

			clock_t start__           = clock();
			string received__         = FoxAndHandle().lexSmallestName(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S                  = "abaabbab";
			string expected__         = "aabb";

			clock_t start__           = clock();
			string received__         = FoxAndHandle().lexSmallestName(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S                  = "bbbbaaaa";
			string expected__         = "bbaa";

			clock_t start__           = clock();
			string received__         = FoxAndHandle().lexSmallestName(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string S                  = "fedcbafedcba";
			string expected__         = "afedcb";

			clock_t start__           = clock();
			string received__         = FoxAndHandle().lexSmallestName(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string S                  = "nodevillivedon";
			string expected__         = "deilvon";

			clock_t start__           = clock();
			string received__         = FoxAndHandle().lexSmallestName(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string S                  = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndHandle().lexSmallestName(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string S                  = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndHandle().lexSmallestName(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string S                  = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndHandle().lexSmallestName(S);
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
