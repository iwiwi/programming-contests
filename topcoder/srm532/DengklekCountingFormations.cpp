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

struct DengklekCountingFormations {
  int numFormations(int N, int M, int K);
};

typedef long long ll;
const ll MOD = 1000000007;

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}

ll inv[1010];

ll fact[1010];
ll inv_fact[1010];



int N, M, K;
vector<int> divs;

ll dp[60];

void doit(ll c, ll o) {
  int n = divs.size();
  if (n > K) return;
  c = c * inv_fact[K - n] % MOD;

  for (int m = M; m >= 0; --m) {
    ll p = 1;
    for (int dm = 1; m + dm <= M; ++dm) {
      p = p * (c - dm + 1) % MOD;
      p = p * inv[dm] % MOD;
      p = p * o % MOD;

      dp[m + dm] += dp[m] * p;
      dp[m + dm] %= MOD;
    }
  }
}

void search(int n, int u, int s, ll c, ll o) {
  if (n == 0) {
    doit(c, o);
    return;
  }

  for (int k = u; k <= n; ++k) {
    divs.push_back(k);

    ll to = o * inv_fact[k] % MOD;
    int ts = u == k ? s + 1 : 1;
    ll tc = c * inverse(ts, MOD) % MOD;

    search(n - k, k, ts, tc, to);
    divs.pop_back();
  }
}

int DengklekCountingFormations::numFormations(int N_, int M_, int K_) {
  N = M_;
  M = N_;
  K = K_;

  fact[0] = inv_fact[0] = 1;
  for (int i = 1; i <= 1000; ++i) {
    fact[i] = fact[i - 1] * i % MOD;
    inv_fact[i] = inverse(fact[i], MOD);

    inv[i] = inverse(i, MOD);
  }

  memset(dp, 0, sizeof(dp));
  dp[0] = 1;
  search(N, 1, 0, fact[K], fact[N]);

  ll ans = dp[M] * fact[M] % MOD;
  ans = (ans + MOD) % MOD;
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
			int N                     = 2;
			int M                     = 2;
			int K                     = 2;
			int expected__            = 10;

			clock_t start__           = clock();
			int received__            = DengklekCountingFormations().numFormations(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 1;
			int M                     = 1;
			int K                     = 58;
			int expected__            = 58;

			clock_t start__           = clock();
			int received__            = DengklekCountingFormations().numFormations(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 5;
			int M                     = 3;
			int K                     = 2;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = DengklekCountingFormations().numFormations(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 3;
			int M                     = 5;
			int K                     = 7;
			int expected__            = 894953467;

			clock_t start__           = clock();
			int received__            = DengklekCountingFormations().numFormations(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 7;
			int M                     = 47;
			int K                     = 74;
			int expected__            = 778075142;

			clock_t start__           = clock();
			int received__            = DengklekCountingFormations().numFormations(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int N                     = 2;
			int M                     = 35;
			int K                     = 11;
			int expected__            = 827591288;

			clock_t start__           = clock();
			int received__            = DengklekCountingFormations().numFormations(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 6: {
			int N                     = 3;
			int M                     = 18;
			int K                     = 13;
			int expected__            = 940249024;

			clock_t start__           = clock();
			int received__            = DengklekCountingFormations().numFormations(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			int N                     = ;
			int M                     = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DengklekCountingFormations().numFormations(N, M, K);
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
