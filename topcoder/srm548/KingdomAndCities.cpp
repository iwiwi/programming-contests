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

struct KingdomAndCities {
  int howMany(int N, int M, int K);
};

typedef long long ll;

const ll MOD = 1000000007;

ll cmb[2510][2510];

void init_cmb(int N) {
  cmb[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    cmb[i][0] = 1;
    for (int j = 1; j <= i; ++j) cmb[i][j] = (cmb[i-1][j-1] + cmb[i-1][j]) % MOD;
  }
}


ll mem[60][60];

ll any(int n, int k);
ll connected(int n, int k);

ll disconnected(int n, int k) {
  if (n < 0 || k < 0) return 0;

  ll res = 0;
  for (int tn = 1; tn < n; ++tn) {
    for (int tk = 0; tk <= k; ++tk) {
      res += cmb[n - 1][tn - 1] *
          connected(tn    , tk    ) % MOD *
          any      (n - tn, k - tk) % MOD;
      res %= MOD;
    }
  }
  return res;
}

ll any(int n, int k) {
  if (n < 0 || k < 0) return 0;
  return cmb[n * (n - 1) / 2][k];
}

ll connected(int n, int k) {
  if (n < 0 || k < 0) return 0;
  if (mem[n][k] != -1) return mem[n][k];
  return mem[n][k] = (any(n, k) - disconnected(n, k) + MOD) % MOD;
}

int KingdomAndCities::howMany(int N, int M, int K) {
  init_cmb(2500);
  memset(mem, -1, sizeof(mem));

  ll ans = 0;
  if (M == 0) {
    ans = connected(N, K);
  } else if (M == 1) {
    (ans += connected(N - 1, K - 1) * (K - 1)) %= MOD;
    (ans += connected(N - 1, K - 2) * (K - 2)) %= MOD;
  } else if (M == 2){
    (ans += connected(N - 2, K - 3) * (N - 2)) %= MOD;

    (ans += connected(N - 2, K - 2) * (K - 2) * 2) %= MOD;
    (ans += connected(N - 2, K - 3) * (K - 3) * 2) %= MOD;

    (ans += connected(N - 2, K - 2) * (K - 2) * (K - 3)) %= MOD;
    (ans += connected(N - 2, K - 3) * (K - 3) * (K - 4)) %= MOD;
    (ans += connected(N - 2, K - 3) * (K - 3) * (K - 4)) %= MOD;
    (ans += connected(N - 2, K - 4) * (K - 4) * (K - 5)) %= MOD;

    (ans += connected(N - 2, K - 3) * (K - 3)) %= MOD;
    (ans += connected(N - 2, K - 4) * (K - 4)) %= MOD;
  }

  return (ans % MOD + MOD) % MOD;
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
			int N                     = 3;
			int M                     = 0;
			int K                     = 3;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = KingdomAndCities().howMany(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 4;
			int M                     = 1;
			int K                     = 4;
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = KingdomAndCities().howMany(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 5;
			int M                     = 2;
			int K                     = 11;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = KingdomAndCities().howMany(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 5;
			int M                     = 0;
			int K                     = 8;
			int expected__            = 45;

			clock_t start__           = clock();
			int received__            = KingdomAndCities().howMany(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 10;
			int M                     = 2;
			int K                     = 20;
			int expected__            = 150810825;

			clock_t start__           = clock();
			int received__            = KingdomAndCities().howMany(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int N                     = 49;
			int M                     = 1;
			int K                     = 29;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = KingdomAndCities().howMany(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int N                     = ;
			int M                     = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = KingdomAndCities().howMany(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int M                     = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = KingdomAndCities().howMany(N, M, K);
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
