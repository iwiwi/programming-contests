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

struct FoxAndGCDLCM {
  long long get(long long G, long long L);
};

typedef long long ll;
const ll INF = 1LL << 60;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

long long FoxAndGCDLCM::get(long long G, long long L) {
  if (L % G != 0) return -1;

  ll res = INF;

  ll X = L / G;
  for (ll a = 1; a * a <= X; ++a) {
    ll b = X / a;
    if (a * b != X || gcd(a, b) != 1) continue;

    res = min(res, (G * a + G * b));
  }

  if (res == INF) return -1;
  else return res;
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
			long long G               = 2;
			long long L               = 20;
			long long expected__      = 14;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long G               = 5;
			long long L               = 8;
			long long expected__      = -1;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long G               = 1000;
			long long L               = 100;
			long long expected__      = -1;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long G               = 100;
			long long L               = 1000;
			long long expected__      = 700;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long G               = 10;
			long long L               = 950863963000LL;
			long long expected__      = 6298430;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			long long G               = ;
			long long L               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			long long G               = ;
			long long L               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long G               = ;
			long long L               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
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
