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

struct CheckerExpansion {
  vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h);
};

typedef long long ll;

const ll MOD = 2;

ll fac[MOD], inv[MOD];

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}

void init() {
  fac[0] = 1;
  for (int i = 1; i < MOD; i++) {
    fac[i] = (fac[i - 1] * i) % MOD;
    inv[i] = inverse(i, MOD);
  }
}

ll choose_mod(ll n, ll m) {
  if (n == 0 && m == 0) return 1;
  int a = n % MOD, b = m % MOD;
  if (b > a) return 0;
  return (((((choose_mod(n / MOD, m / MOD) * fac[a]) % MOD)
            * inv[fac[b]]) % MOD) * inv[fac[a - b]]) % MOD;
}



char solve(ll x, ll y, ll t) {
  if (x < 0 || y < 0 || y > x) return '.';

  ll up = y;
  ll ri = x - up;
  if (ri % 2 != 0) return '.';
  ri /= 2;

  if (up + ri >= t || choose_mod(up + ri, ri) == 0) return '.';

  return "AB"[(up + ri) % 2];
}

vector <string> CheckerExpansion::resultAfter(long long t, long long x0, long long y0, int w, int h) {
  init();

  vector<string> ans(h, string(w, '.'));
  rep (i, h) rep (j, w) ans[i][j] = solve(x0 + j, y0 + h - i - 1, t);
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

	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }
	template<> ostream& operator<<(ostream &os, const vector<string> &v) { os << "{"; for (vector<string>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " \"" << *vi << "\""; } os << " }"; return os; }

	int verify_case(int casenum, const vector <string> &expected, const vector <string> &received, clock_t elapsed) {
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
			long long t               = 1;
			long long x0              = 0;
			long long y0              = 0;
			int w                     = 4;
			int h                     = 4;
			string expected__[]       = {"....", "....", "....", "A..." };

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			long long t               = 5;
			long long x0              = 4;
			long long y0              = 1;
			int w                     = 3;
			int h                     = 4;
			string expected__[]       = {"A..", "...", "B..", ".B." };

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			long long t               = 1024;
			long long x0              = 1525;
			long long y0              = 512;
			int w                     = 20;
			int h                     = 2;
			string expected__[]       = {"B...B...B...........", ".B.A.B.A.B.........." };

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			long long t               = 53;
			long long x0              = 85;
			long long y0              = 6;
			int w                     = 5;
			int h                     = 14;
			string expected__[]       = {".....", ".....", "B....", ".B.A.", ".....", ".....", ".....", ".....", ".....", ".....", "B....", ".B...", "..B..", ".A.B." };

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

      case 4: {
			long long t               = 3;
			long long x0              = 0;
			long long y0              = 0;
			int w                     = 10;
			int h                     = 10;
			string expected__[]       = {};

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
/*      case 5: {
			long long t               = ;
			long long x0              = ;
			long long y0              = ;
			int w                     = ;
			int h                     = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			long long t               = ;
			long long x0              = ;
			long long y0              = ;
			int w                     = ;
			int h                     = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
