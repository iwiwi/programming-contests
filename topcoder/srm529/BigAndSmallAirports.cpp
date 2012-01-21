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

struct BigAndSmallAirports {
  long long solve(int Nlo, int Nhi, int Blo, int Bhi, int Slo, int Shi);
};

typedef long long ll;

ll sumsum(ll a, ll b, ll t) {
  ll c = min(b, t);
  if (c < a) return 0;
  return (c - a + 1) * t - c * (c + 1) / 2 + a * (a - 1) / 2;
}

long long BigAndSmallAirports::solve(int Nlo, int Nhi, int Blo, int Bhi, int Slo, int Shi) {
  ll ans = 0;
  for (ll S = Slo; S <= Shi; ++S) {
    for (ll B = Blo; B <= Bhi; ++B) {
      if (S < B) {
        // n = 0 (all small)
        if (S > 1) ans += Nhi - Nlo + 1;
        else ans += max(min(Nhi, 2) - max(Nlo, 1) + 1, 0);

        // n in [1, min(1 + B, Nhi)]
        for (ll n = 1; n <= min(1 + B, ll(Nhi)); ++n) {
          ll t = -n * n + (1 + B) * n;
          ll d = min(S, n);

          ll Mlo = t / d + (t % d ? 1 : 0);
          Mlo = max(Mlo, max(ll(Nlo), B + 1) - n);

          ll Mhi = Nhi - n;

          // [Mlo, Mhi]
          ans += max(Mhi - Mlo + 1, 0LL);
        }

        // n in [2 + B, Nhi]
        ans += sumsum(2 + B, Nhi, Nhi);
        ans -= sumsum(2 + B, Nhi, Nlo);
        ans += max(Nhi - (2 + B) + 1, 0LL);
      }
    }
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
			int Nlo                   = 20;
			int Nhi                   = 20;
			int Blo                   = 3;
			int Bhi                   = 3;
			int Slo                   = 2;
			int Shi                   = 2;
			long long expected__      = 21;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int Nlo                   = 1;
			int Nhi                   = 1;
			int Blo                   = 10;
			int Bhi                   = 10;
			int Slo                   = 2;
			int Shi                   = 2;
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int Nlo                   = 10;
			int Nhi                   = 10;
			int Blo                   = 8;
			int Bhi                   = 8;
			int Slo                   = 3;
			int Shi                   = 3;
			long long expected__      = 6;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int Nlo                   = 10;
			int Nhi                   = 100;
			int Blo                   = 13;
			int Bhi                   = 15;
			int Slo                   = 18;
			int Shi                   = 22;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int Nlo                   = 30;
			int Nhi                   = 32;
			int Blo                   = 8;
			int Bhi                   = 10;
			int Slo                   = 6;
			int Shi                   = 8;
			long long expected__      = 768;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

        case 5: {
			int Nlo                   = 1;
			int Nhi                   = 10000000;
			int Blo                   = 1;
			int Bhi                   = 200;
			int Slo                   = 1;
			int Shi                   = 200;
			long long expected__      = 995000296045760393;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int Nlo                   = ;
			int Nhi                   = ;
			int Blo                   = ;
			int Bhi                   = ;
			int Slo                   = ;
			int Shi                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int Nlo                   = ;
			int Nhi                   = ;
			int Blo                   = ;
			int Bhi                   = ;
			int Slo                   = ;
			int Shi                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
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
