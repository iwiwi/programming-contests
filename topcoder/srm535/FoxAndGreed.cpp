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

struct FoxAndGreed {
  int count(int H, int W, int S);
};

typedef long long ll;
const int MOD = 10007;

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m = MOD) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}

ll fac[MOD], inv[MOD];

void init() {
  fac[0] = 1;
  for (int i = 1; i < MOD; i++) {
    fac[i] = (fac[i - 1] * i) % MOD;
    inv[i] = inverse(i, MOD);
  }
}

ll pow_mod(ll a, ll k, ll m) {
  if (k == 0) return 1;
  ll t = pow_mod(a, k / 2, m);
  return mod(mod(t * t, m) * (k % 2 ? a : 1), m);
}

int H, W, S;
int ge[5100][110];
int gt[5100][110];
int fr[5100][110];

int ans;

void doit(int r, int b, int f, bool lastr) {
  int base = 1;
  base = base
      * fac[r + b - 1] % MOD
      * inv[fac[r - (lastr ? 1 : 0)]] % MOD
      * inv[fac[b - (lastr ? 0 : 1)]] % MOD;

  int fren = W * H - r * 2 - b * 2 - 1 - f;
  base *= pow_mod(S + 1, fren, MOD);
  base %= MOD;

  int sels = 0;
  for (int ges = 0; ges <= S; ++ges) {
    for (int gts = 0; ges + gts <= S; ++gts) {
      sels += ge[r][ges] * gt[b][gts] % MOD * fr[f][S - ges - gts];
      sels %= MOD;
    }
  }

  ans += base * sels;
  ans %= MOD;
}

int FoxAndGreed::count(int H_, int W_, int S_) {
  H = H_;
  W = W_;
  S = S_;

  init();

  int K = H + W + 10;
  memset(ge, 0, sizeof(ge)); ge[0][0] = 1;
  memset(gt, 0, sizeof(gt)); gt[0][0] = 1;
  memset(fr, 0, sizeof(fr)); fr[0][0] = 1;
  for (int k = 1; k <= K; ++k) {
    for (int s = 0; s <= S; ++s) {
      for (int t = 0; t <= s; ++t) {
        ge[k][s] += ge[k - 1][s - t] * (t + 1); ge[k][s] %= MOD;
        gt[k][s] += gt[k - 1][s - t] * (t + 0); gt[k][s] %= MOD;
        fr[k][s] += fr[k - 1][s - t];           fr[k][s] %= MOD;
      }
    }
  }

  if (W == 1 || H == 1) {
    return fr[H + W - 2][S];
  } else {
    ans = 0;
    rep (y, H - 1) doit(W - 1, y, H - y - 1, true);
    rep (x, W - 1) doit(x, H - 1, W - x - 1, false);
    return ans;
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
			int H                     = 2;
			int W                     = 2;
			int S                     = 1;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int H                     = 2;
			int W                     = 2;
			int S                     = 2;
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int H                     = 2;
			int W                     = 2;
			int S                     = 0;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int H                     = 47;
			int W                     = 58;
			int S                     = 100;
			int expected__            = 1301;

			clock_t start__           = clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int H                     = 1234;
			int W                     = 2345;
			int S                     = 97;
			int expected__            = 8894;

			clock_t start__           = clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int H                     = 3;
			int W                     = 3;
			int S                     = 1;
			int expected__            = 28;

			clock_t start__           = clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int H                     = ;
			int W                     = ;
			int S                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int H                     = ;
			int W                     = ;
			int S                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndGreed().count(H, W, S);
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
