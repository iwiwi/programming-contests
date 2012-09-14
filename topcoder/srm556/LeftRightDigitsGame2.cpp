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

struct LeftRightDigitsGame2 {
  string minNumber(string digits, string lowerBound);
};

bool vis[60][60][2][2];
string mem[60][60][2][2];

int N;
string S, L;

string search(int a, int b, bool f, bool t) {
  if (a == 0) {
    if (f || t) return "";
    else return "Z";
  }
  if (vis[a][b][f][t]) return mem[a][b][f][t];

  string ans(a, 'Z');
  rep (ta, a) {
    if (f || S[ta] >= L[b]) {
      bool tf = f || S[ta] > L[b];

      string mytail = S.substr(    ta + 1, a - ta - 1);
      string lotail = L.substr(b + ta + 1, a - ta - 1);
      bool tt = mytail > lotail || (mytail == lotail && t);

      string tmp = search(ta, b + 1, tf, tt);
      if (!tmp.empty() && tmp[0] == 'Z') continue;

      ans = min(ans, S[ta] + tmp + mytail);
    }
  }

  vis[a][b][f][t] = true;
  mem[a][b][f][t] = ans;

  // cout << a << " " << b << " " << f << " " << t << " : " << ans << endl;

  return ans;
}

string LeftRightDigitsGame2::minNumber(string digits, string lowerBound) {
  S = digits;
  L = lowerBound;
  N = digits.length();

  memset(vis, 0, sizeof(vis));
  string ans = search(N, 0, false, true);
  if (ans[0] == 'Z') ans = "";
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
			string digits             = "565";
			string lowerBound         = "556";
			string expected__         = "556";

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string digits             = "565";
			string lowerBound         = "566";
			string expected__         = "655";

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string digits             = "565";
			string lowerBound         = "656";
			string expected__         = "";

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string digits             = "9876543210";
			string lowerBound         = "5565565565";
			string expected__         = "5678943210";

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string digits             = "8016352";
			string lowerBound         = "1000000";
			string expected__         = "1086352";

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string digits             = ;
			string lowerBound         = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string digits             = ;
			string lowerBound         = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string digits             = ;
			string lowerBound         = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
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
