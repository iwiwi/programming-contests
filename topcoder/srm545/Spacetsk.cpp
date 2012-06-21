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

struct Spacetsk {
  int countsets(int L, int H, int K);
};

typedef long long ll;
const ll MOD = 1000000007;

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}

inline ll absll(ll x) {
  return x >= 0 ? x : -x;
}

inline ll div_more(ll a, ll b) {  // a/b < x
  return (a < 0) ^ (b < 0) ? -(absll(a) + absll(b) - 1) / absll(b) + 1 : absll(a) / absll(b) + 1;
}


ll L, H, K;

ll fac[2100], inv[2100];
ll cho[2100], sum[2100];

ll cnt(ll ln, ll ld, ll rn, ll rd) {
  ll n = (ln + rn), d = (ld + rd);
  if (d > L) return 0;
  if (n > H) return 0;

  ll ans = cnt(ln, ld, n, d) + cnt(n, d, rn, rd);

  ll tmp = 0;

  ll x1 = min(L + 1, div_more(H * d, n));
  tmp += (L - x1 + 1) * cho[H / n + 1];

  ll x2 = x1 / d * d;
  tmp += (x1 - x2) * cho[x2 / d + 1];
  tmp += sum[x2 / d + 1] * d;

  return (ans + tmp) % MOD;
}

int Spacetsk::countsets(int L, int H, int K) {
  if (K == 1) return (L + 1) * (H + 1);

  ::L = L;
  ::H = H;
  ::K = K;

  int M = H + 10;

  fac[0] = inv[0] = 1;
  for (int i = 1; i <= M; ++i) {
    fac[i] = (fac[i - 1] * i) % MOD;
    inv[i] = inverse(fac[i], MOD);
  }

  memset(cho, 0, sizeof(cho));
  for (int i = K; i <= M; ++i) cho[i] = fac[i] * inv[K] % MOD * inv[i - K] % MOD;
  sum[0] = 0;
  for (int i = 0; i <= M; ++i) sum[i + 1] = sum[i] + cho[i];

  return ((L + 1) * cho[1 + H] + 2 * cnt(0, 1, 1, 0)) % MOD;
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
			int L                     = 1;
			int H                     = 1;
			int K                     = 2;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = Spacetsk().countsets(L, H, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int L                     = 1;
			int H                     = 1;
			int K                     = 1;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = Spacetsk().countsets(L, H, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int L                     = 2;
			int H                     = 2;
			int K                     = 1;
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = Spacetsk().countsets(L, H, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int L                     = 2;
			int H                     = 2;
			int K                     = 2;
			int expected__            = 23;

			clock_t start__           = clock();
			int received__            = Spacetsk().countsets(L, H, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int L                     = 5;
			int H                     = 5;
			int K                     = 3;
			int expected__            = 202;

			clock_t start__           = clock();
			int received__            = Spacetsk().countsets(L, H, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int L                     = 561;
			int H                     = 394;
			int K                     = 20;
			int expected__            = 786097180;

			clock_t start__           = clock();
			int received__            = Spacetsk().countsets(L, H, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int L                     = ;
			int H                     = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Spacetsk().countsets(L, H, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int L                     = ;
			int H                     = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Spacetsk().countsets(L, H, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int L                     = ;
			int H                     = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Spacetsk().countsets(L, H, K);
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
