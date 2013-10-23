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
#include <tuple>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define eb emplace_back
#define mp make_pair

class CharacterBoard {
 public:
  int countGenerators(vector <string> fragment, int W, int i0, int j0);
};

typedef long long ll;
const ll MOD = 1000000009;

ll powmod(ll x, ll k) {
  if (k == 0) return 1;
  else if (k == 1) return x;
  else if (k % 2) return x * powmod(x, k - 1) % MOD;
  else return powmod(x * x % MOD, k / 2);
}

inline ll inv(ll x) {
  return powmod(x, MOD - 2);
}

int CharacterBoard::countGenerators(vector <string> fragment, int W_, int i0, int j0) {
  ll W = W_;
  ll w = fragment[0].length(), h = fragment.size();

  vector<ll> difs;
  rep (x0, w) rep (y0, h) {
    rep (x1, w) rep (y1, h) {
      if (mp(x0, y0) == mp(x1, y1)) continue;
      ll z0 = x0 + y0 * W;
      ll z1 = x1 + y1 * W;
      difs.eb(llabs(z1 - z0));
    }
  }
  sort(all(difs));
  difs.erase(unique(all(difs)), difs.end());

  vector<ll> cans;
  for (ll d : difs) {
    for (ll z = 1; z * z <= d; ++z) {
      if (d % z == 0) {
        if (z     <= W) cans.eb(z);
        if (d / z <= W) cans.eb(d / z);
      }
    }
  }
  sort(all(cans));
  cans.erase(unique(all(cans)), cans.end());

  ll ans = 0;
  {
    // k = {w*h, w*h+1, ..., W}
    // t = {  0,     1, ..., W-w*h}
    ll T = W - w * h;
    if (T >= 0) {
      ans += (powmod(26, T + 1) - 1) * inv(26 - 1) % MOD;
    }
  }

  for (ll k : cans) {
    vector<pair<int, char> > cs;
    rep (x, w) rep (y, h) cs.eb((x + y * W) % k, fragment[y][x]);
    sort(all(cs));

    ll free = k;
    rep (i, cs.size()) {
      if (i > 0 && cs[i - 1].first == cs[i].first) {
        if (cs[i - 1].second != cs[i].second) goto dmp;
      } else {
        --free;
      }
    }
    {
      ll tmp = powmod(26, free);
      (ans += tmp) %= MOD;
    }
 dmp:;

    if (k >= w * h) (ans -= powmod(26, k - w * h)) %= MOD;
  }

  return (ans + MOD) % MOD;
}















// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
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
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}

	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) {
		std::cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;

		if (verdict == "FAILED") {
			std::cerr << "    Expected: " << expected << std::endl;
			std::cerr << "    Received: " << received << std::endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string fragment[]         = {"dea",
 "abc"}
;
			int W                     = 7;
			int i0                    = 1;
			int j0                    = 1;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = CharacterBoard().countGenerators(vector <string>(fragment, fragment + (sizeof fragment / sizeof fragment[0])), W, i0, j0);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string fragment[]         = {"xyxxy"}
;
			int W                     = 6;
			int i0                    = 1;
			int j0                    = 0;
			int expected__            = 28;

			std::clock_t start__      = std::clock();
			int received__            = CharacterBoard().countGenerators(vector <string>(fragment, fragment + (sizeof fragment / sizeof fragment[0])), W, i0, j0);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string fragment[]         = {"gogogo",
 "jijiji",
 "rarara"}
;
			int W                     = 6;
			int i0                    = 0;
			int j0                    = 0;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = CharacterBoard().countGenerators(vector <string>(fragment, fragment + (sizeof fragment / sizeof fragment[0])), W, i0, j0);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string fragment[]         = {"abababacac",
 "aaacacacbb",
 "ccabababab"}
;
			int W                     = 8827;
			int i0                    = 104;
			int j0                    = 6022;
			int expected__            = 829146844;

			std::clock_t start__      = std::clock();
			int received__            = CharacterBoard().countGenerators(vector <string>(fragment, fragment + (sizeof fragment / sizeof fragment[0])), W, i0, j0);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string fragment[]         = ;
			int W                     = ;
			int i0                    = ;
			int j0                    = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CharacterBoard().countGenerators(vector <string>(fragment, fragment + (sizeof fragment / sizeof fragment[0])), W, i0, j0);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string fragment[]         = ;
			int W                     = ;
			int i0                    = ;
			int j0                    = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CharacterBoard().countGenerators(vector <string>(fragment, fragment + (sizeof fragment / sizeof fragment[0])), W, i0, j0);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string fragment[]         = ;
			int W                     = ;
			int i0                    = ;
			int j0                    = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CharacterBoard().countGenerators(vector <string>(fragment, fragment + (sizeof fragment / sizeof fragment[0])), W, i0, j0);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
