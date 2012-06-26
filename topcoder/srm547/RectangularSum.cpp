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

struct RectangularSum {
  long long minimalArea(int height, int width, long long S);
};

typedef long long ll;

ll H, W, S2;

inline bool test2(ll w, ll h) {
  if (w > W || h > H) return false;

  ll s = S2 / (w * h);
  s -= W * (h - 1);
  s -= w - 1;
  if (s % 2 != 0) return false;
  s /= 2;
  ll i = s / W;
  ll j = s % W;

  if (0 <= i && i + h <= H && 0 <= j && j + w <= W) {
    // printf("(%lld, %lld), %lld x %lld\n", i, j, w, h);
    return true;
  } else {
    return false;
  }
}

bool test(ll wh) {
  if (wh > W * H) return false;

  for (ll d = 1; d * d <= wh; ++d) {
    if (wh % d != 0) continue;

    ll e = wh / d;
    if (test2(d, e)) return true;
    if (test2(e, d)) return true;
  }
  return false;
}

long long RectangularSum::minimalArea(int H_, int W_, long long S) {
  H = H_;
  W = W_;

  S2 = S * 2;

  vector<ll> whs, whs2;
  for (ll d = 1; d * d <= S2; ++d) if (S2 % d == 0) whs.pb(d);
  for (ll d = 1; d * d <= S2; ++d) if (S2 % d == 0) whs2.pb(S2 / d);
  whs.insert(whs.end(), whs2.rbegin(), whs2.rend());

  rep (i, whs.size()) {
    ll wh = whs[i];
    if (test(wh)) return wh;
  }
  return -1;
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
			int height                = 2;
			int width                 = 3;
			long long S               = 8;
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int height                = 3;
			int width                 = 3;
			long long S               = 10;
			long long expected__      = -1;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int height                = 3;
			int width                 = 3;
			long long S               = 36;
			long long expected__      = 9;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int height                = 25;
			int width                 = 25;
			long long S               = 16000;
			long long expected__      = 32;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int height                = 1000000;
			int width                 = 1000000;
			long long S               = 1000000000000LL;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int height                = 1000000;
			int width                 = 1000000;
			long long S               = 200560490130 * 4;
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int height                = ;
			int width                 = ;
			long long S               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int height                = ;
			int width                 = ;
			long long S               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
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
