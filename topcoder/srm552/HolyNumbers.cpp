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

struct HolyNumbers {
  long long count(long long upTo, int maximalPrime);
};

const int MAX_N = 1000010;

int prime[MAX_N], prime_n;
bool is_composite[MAX_N + 1];

void sieve(int n) {
  is_composite[0] = is_composite[1] = true;
  for (int i = 2; i * i <= n; i++) {
    if (is_composite[i]) continue;
    for (int j = i; i * j <= n; j++) is_composite[i * j] = true;
  }
  prime_n = 0;
  for (int i = 2; i <= n; i++) {
    if (!is_composite[i]) prime[prime_n++] = i;
  }
}

typedef long long ll;
map<ll, ll> mem[100010];

const int T = 0;

ll search(int k, ll n) {
  if (k == prime_n) return 1;

  ll p = prime[k];

  if (p * p > n) {
    int t = upper_bound(prime + k, prime + prime_n, n) - prime - k;
    return t + 1;
  }

  if (p > n) return 1;

  pair<iter(mem[k]), bool> ite;
  if (n <= T) {
    ite = mem[k].insert(mp(n, 0));
    if (ite.second == false) return ite.first->second;
  }

  ll ans = 0;
  ans += search(k + 1, n);

  ll t = 1;
  for (int i = 1; ; ++i) {
    t *= p;
    if (t > n) break;
    if (i % 2 == 1) {
      ans += search(k + 1, n / t);
    }
  }

  if (n <= T) ite.first->second = ans;
  return ans;
}

long long HolyNumbers::count(long long upTo, int maximalPrime) {
  sieve(maximalPrime);
  rep (i, prime_n) mem[i].clear();
  return search(0, upTo);
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
			long long upTo            = 10;
			int maximalPrime          = 100;
			long long expected__      = 8;

			clock_t start__           = clock();
			long long received__      = HolyNumbers().count(upTo, maximalPrime);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long upTo            = 10;
			int maximalPrime          = 3;
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = HolyNumbers().count(upTo, maximalPrime);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long upTo            = 123;
			int maximalPrime          = 12;
			long long expected__      = 32;

			clock_t start__           = clock();
			long long received__      = HolyNumbers().count(upTo, maximalPrime);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long upTo            = 123;
			int maximalPrime          = 456;
			long long expected__      = 88;

			clock_t start__           = clock();
			long long received__      = HolyNumbers().count(upTo, maximalPrime);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long upTo            = 123456789;
			int maximalPrime          = 12345;
			long long expected__      = 25994500;

			clock_t start__           = clock();
			long long received__      = HolyNumbers().count(upTo, maximalPrime);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			long long upTo            = 10000000000;
			int maximalPrime          = 1000000;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = HolyNumbers().count(upTo, maximalPrime);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			long long upTo            = ;
			int maximalPrime          = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = HolyNumbers().count(upTo, maximalPrime);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long upTo            = ;
			int maximalPrime          = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = HolyNumbers().count(upTo, maximalPrime);
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
