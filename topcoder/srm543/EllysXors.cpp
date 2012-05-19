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

struct EllysXors {
  long long getXor(long long L, long long R);
};

typedef long long ll;

ll hoge(ll value) {
  value = value + 1;
  ll unit = 1;
  ll sum = (value % 4 >= 2) ? 1 : 0;
  for (ll index = 2; ; index++) {
    unit = unit * 2;
    if (unit >= value) break;
    ll num = value % (2 * unit);
    if (num > unit) {
      num -= unit;
      if (num % 2 == 1) sum += unit;
    }
  }
  return sum;
}

ll piyo(ll n) {
  ll res = 0;
  for (int i = 1; i <= 40; ++i) {
    if (n % 2 == 0) {
      res |= n & (1LL << i);
    }
  }
  res |= ((n & 2) >> 1) ^ (n & 1);
  return res;
}

ll cum_xor(ll n) {
  switch (n % 4) {
  case 0: return n;
  case 1: return 1;
  case 2: return n + 1;
  case 3: return 0;
  }
  assert(false);
}


long long EllysXors::getXor(long long L, long long R) {
  ll myans = cum_xor(R) ^ cum_xor(L - 1);

  //ll waros = hoge(R) ^ hoge(L - 1);
  ll waros = piyo(R) ^ piyo(L - 1);
  assert(myans == waros);

  return waros;
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
			long long L               = 3;
			long long R               = 10;
			long long expected__      = 8;

			clock_t start__           = clock();
			long long received__      = EllysXors().getXor(L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long L               = 5;
			long long R               = 5;
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = EllysXors().getXor(L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long L               = 13;
			long long R               = 42;
			long long expected__      = 39;

			clock_t start__           = clock();
			long long received__      = EllysXors().getXor(L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long L               = 666;
			long long R               = 1337;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = EllysXors().getXor(L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long L               = 1234567;
			long long R               = 89101112;
			long long expected__      = 89998783;

			clock_t start__           = clock();
			long long received__      = EllysXors().getXor(L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			long long L               = ;
			long long R               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = EllysXors().getXor(L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			long long L               = ;
			long long R               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = EllysXors().getXor(L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long L               = ;
			long long R               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = EllysXors().getXor(L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
  while (true) {
    int l = rand() % 10000 + 1;
    int r = rand() % 10000 + 1;
    if (l > r) swap(l, r);
    EllysXors().getXor(l, r + 1);
  }

	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
