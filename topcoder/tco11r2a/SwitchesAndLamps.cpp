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
#include <bitset>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

struct SwitchesAndLamps {
  int theMin(vector <string> switches, vector <string> lamps);
};

typedef long long ll;

vector<string> S, L;

int ans;

void search(int k, ll bs, ll bl) {
  int c = __builtin_popcountll(bs);
  if (c != __builtin_popcountll(bl)) throw 0;  // inconsistent
  if (c <= 1) return;

  if (k == (int)S.size()) {
    for (int i = 0; ; ++i) {
      if (c <= (1LL << i)) {
        ans = max(ans, i);
        break;
      }
    }
  } else {
    ll ys = 0, yl = 0;
    rep (i, S[k].length()) {
      ys |= (S[k][i] == 'Y' ? 1LL : 0LL) << i;
      yl |= (L[k][i] == 'Y' ? 1LL : 0LL) << i;
    }

    search(k + 1, bs &  ys, bl &  yl);
    search(k + 1, bs & ~ys, bl & ~yl);
  }
}

int SwitchesAndLamps::theMin(vector <string> switches, vector <string> lamps) {
  S = switches;
  L = lamps;
  int n = switches[0].length();

  try {
    ans = 0;
    search(0, (1LL << n) - 1, (1LL << n) - 1);
    return ans;
  } catch (...) {
    return -1;
  }
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
			string switches[]         = {"NYNN", "NNYN"};
			string lamps[]            = {"NNNY", "NNYN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = SwitchesAndLamps().theMin(vector <string>(switches, switches + (sizeof switches / sizeof switches[0])), vector <string>(lamps, lamps + (sizeof lamps / sizeof lamps[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string switches[]         = {"YYN", "YNY", "YYN"};
			string lamps[]            = {"YNY", "NYY", "YNY"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = SwitchesAndLamps().theMin(vector <string>(switches, switches + (sizeof switches / sizeof switches[0])), vector <string>(lamps, lamps + (sizeof lamps / sizeof lamps[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string switches[]         = {"NYYYNYNNYYYNYNNNNY", "NYYYNYNNYYYNYNNNNY"};
			string lamps[]            = {"YYYNNNYNNYNYNYNYNY", "YYYNNNYNNYNYYNNYNY"};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = SwitchesAndLamps().theMin(vector <string>(switches, switches + (sizeof switches / sizeof switches[0])), vector <string>(lamps, lamps + (sizeof lamps / sizeof lamps[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string switches[]         = {"YYNNN", "NNYYN"};
			string lamps[]            = {"NYNNY", "NNNYY"};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = SwitchesAndLamps().theMin(vector <string>(switches, switches + (sizeof switches / sizeof switches[0])), vector <string>(lamps, lamps + (sizeof lamps / sizeof lamps[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string switches[]         = {"YNNYNNYNYY", "NYNNYNYNYN", "YNYNYYYYYN", "NNYYNYNYNN"};
			string lamps[]            = {"NYYNYNNYNY", "NYYYNNYNNN", "YYYYNYNNYY", "YNNNNYNYYN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = SwitchesAndLamps().theMin(vector <string>(switches, switches + (sizeof switches / sizeof switches[0])), vector <string>(lamps, lamps + (sizeof lamps / sizeof lamps[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string switches[]         = ;
			string lamps[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SwitchesAndLamps().theMin(vector <string>(switches, switches + (sizeof switches / sizeof switches[0])), vector <string>(lamps, lamps + (sizeof lamps / sizeof lamps[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string switches[]         = ;
			string lamps[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SwitchesAndLamps().theMin(vector <string>(switches, switches + (sizeof switches / sizeof switches[0])), vector <string>(lamps, lamps + (sizeof lamps / sizeof lamps[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string switches[]         = ;
			string lamps[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SwitchesAndLamps().theMin(vector <string>(switches, switches + (sizeof switches / sizeof switches[0])), vector <string>(lamps, lamps + (sizeof lamps / sizeof lamps[0])));
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
