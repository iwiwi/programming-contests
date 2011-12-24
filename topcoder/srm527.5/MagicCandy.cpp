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

struct MagicCandy {
  int whichOne(int n);
};

typedef long long ll;


ll rec(ll n) {
  if (n == 1) return 1;
  ll a = (int)sqrt(n);
  if (n == a * a) return rec(n - 1);

  ll b = n - a;
  ll c = rec(b);
  return n - (b - c);
}

int solve2(ll n) {
  if (n == 1) return 1;

  int rad = (int)sqrt(n), pat;
  pat = rad * rad;

  if (n - pat == 0) {
    n--;
    rad = (int)sqrt(n);
    pat = rad * rad;
  }

  if ((n - pat) % rad == 0) {
    return n - rad + 1;
  }
  else {
    return n - ((n - pat) % rad) + 1;
  }

  return 1;
}


int MagicCandy::whichOne(int n_) {
  return solve2(n_);

  ll N = n_;

  ll x = 1;
  for (ll d = 1; ; ++d) {
    ll t = (d + 1) * (d + 1) - x;
    ll k = t / d - (t % d == 0 ? 1 : 0);
    ll tx = x + k * d;

    if (tx > N) {
      ll k2 = (N - x) / d;
      x = x + k2 * d;
      break;
    }
  }

  return x;
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
			int n                     = 5;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = MagicCandy().whichOne(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 9;
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = MagicCandy().whichOne(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 20;
			int expected__            = 17;

			clock_t start__           = clock();
			int received__            = MagicCandy().whichOne(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 5265;
			int expected__            = 5257;

			clock_t start__           = clock();
			int received__            = MagicCandy().whichOne(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 20111223;
			int expected__            = 20110741;

			clock_t start__           = clock();
			int received__            = MagicCandy().whichOne(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int n                     = 1;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = MagicCandy().whichOne(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
			int n                     = 1000000000;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = MagicCandy().whichOne(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			int n                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MagicCandy().whichOne(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int n                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MagicCandy().whichOne(n);
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
