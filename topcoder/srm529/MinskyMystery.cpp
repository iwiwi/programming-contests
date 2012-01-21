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

struct MinskyMystery {
  int computeAnswer(long long N);
};

typedef long long ll;

const ll MOD = 1000000009;

inline ll mult_mod(ll a, ll b, ll m) {
  static const int BITS = sizeof(ll) * 8;
  ll t = a, r = 0;
  for (int i = 0; i < BITS && (b >> i) != 0; i++, t = (t + t) % m)
    r = (r + t * ((b >> i) & 1)) % m;
  return r;
}

ll calc(ll n, ll k) {
  ll res = 0, m = min((ll)floor(sqrt(n)), k);
  for (int i = 1; i <= m; ++i) res = (res + n / i) % MOD;
  if (m == k) return res;
  for (int i = 1; i <= n / (m + 1); ++i) res = (res + (min(n / i, k) - m)) % MOD;
  return res;
}

int MinskyMystery::computeAnswer(long long N) {
  if (N <= 1) return -1;

  ll K = N;
  for (ll k = 2; k * k <= N; ++k) {
    if (N % k == 0) {
      K = k;
      break;
    }
  }

  ll ans = -N;
  ans += mult_mod(N * 4 + 2, K - 2 + 1, MOD);
  ans += calc(N, K) - calc(N, 1);
  ans = (ans % MOD + MOD) % MOD;

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
			long long N               = 2;
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = MinskyMystery().computeAnswer(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long N               = 3;
			int expected__            = 27;

			clock_t start__           = clock();
			int received__            = MinskyMystery().computeAnswer(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long N               = 4;
			int expected__            = 16;

			clock_t start__           = clock();
			int received__            = MinskyMystery().computeAnswer(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long N               = 2401;
			int expected__            = 59058;

			clock_t start__           = clock();
			int received__            = MinskyMystery().computeAnswer(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long N               = 24;
			int expected__            = 86;

			clock_t start__           = clock();
			int received__            = MinskyMystery().computeAnswer(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			long long N               = 999999974243;
			int expected__            = 997345690;

			clock_t start__           = clock();
			int received__            = MinskyMystery().computeAnswer(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			long long N               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MinskyMystery().computeAnswer(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long N               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MinskyMystery().computeAnswer(N);
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
