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

struct DengklekMakingChains {
  int maxBeauty(vector <string> chains);
};

int comp(const string &s) {
  int ans = 0, c = 0;
  rep (i, s.length()) {
    if (s[i] == '.') c = 0;
    else c += s[i] - '0';
    ans = max(ans, c);
  }
  return ans;
}

int DengklekMakingChains::maxBeauty(vector <string> chains) {
  chains.push_back("...");
  chains.push_back("...");
  int N = chains.size();

  int ans = 0;
  rep (i, N) ans = max(ans, comp(chains[i]));

  vector<bool> usd(N);
  string in = "";
  rep (i, N) {
    if (count(all(chains[i]), '.') == 0) {
      usd[i] = true;
      in += chains[i];
    }
  }

  rep (i, N) rep (j, N) {
    if (i == j || usd[i] || usd[j]) continue;
    string s = chains[i] + in + chains[j];
    ans = max(ans, comp(s));
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
			string chains[]           = {".15", "7..", "402", "..3"};
			int expected__            = 19;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string chains[]           = {"..1", "7..", "567", "24.", "8..", "234"};
			int expected__            = 36;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string chains[]           = {"...", "..."};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string chains[]           = {"16.", "9.8", ".24", "52.", "3.1", "532", "4.4", "111"};
			int expected__            = 28;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string chains[]           = {"..1", "3..", "2..", ".7."};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string chains[]           = {"412", "..7", ".58", "7.8", "32.", "6..", "351", "3.9", "985", "...", ".46"};
			int expected__            = 58;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string chains[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string chains[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string chains[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
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
