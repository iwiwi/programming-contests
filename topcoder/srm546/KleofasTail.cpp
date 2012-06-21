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

struct KleofasTail {
  long long countGoodSequences(long long K, long long A, long long B);
};

typedef long long ll;

ll solve(ll X, ll lim) {
  ll last = 0;  // [0, last)
  ll ans = 0;

  for (int k = 0; (X << k) < lim; ++k) {
    ll lb = X << k;
    ll ub = (X + 1) << k;
    // [lb, ub)

    lb = max(lb, last);
    ub = min(ub, lim);
    ans += ub - lb;
  }

  return ans;
}

ll solve2(ll X, ll lim) {
  if (X == 0) return lim;

  ll res = solve(X, lim);
  if (X % 2 == 0) res += solve(X + 1, lim);
  return res;
}

long long KleofasTail::countGoodSequences(long long K, long long A, long long B) {
  return solve2(K, B + 1) - solve2(K, A);
}


ll naive(ll K, ll A, ll B) {
  ll ans = 0;
  for (ll X = A; X <= B; ++X) {
    ll t = X;
    while (t > K) {
      if (t % 2 == 1) --t;
      else t /= 2;
    }
    if (t == K) ++ans;
  }
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
			long long K               = 3;
			long long A               = 4;
			long long B               = 8;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long K               = 1;
			long long A               = 23457;
			long long B               = 123456;
			long long expected__      = 100000;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long K               = 1234567890123456LL;
			long long A               = 10;
			long long B               = 1000000;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long K               = 0;
			long long A               = 0;
			long long B               = 2;
			long long expected__      = 3;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long K               = 2;
			long long A               = 3;
			long long B               = 3;
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			long long K               = 13;
			long long A               = 12345;
			long long B               = 67890123;
			long long expected__      = 8387584;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			long long K               = ;
			long long A               = ;
			long long B               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long K               = ;
			long long A               = ;
			long long B               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			long long K               = ;
			long long A               = ;
			long long B               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
  // #pragma omp parallel
  // rep (iter, 10000) {
  //   ll k = rand() % 1000000;
  //   ll a = rand() % 1000000;
  //   ll b = rand() % 1000000;
  //   if (a <= b) {
  //     assert(naive(k, a, b) == KleofasTail().countGoodSequences(k, a, b));
  //   }
  // }

	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
