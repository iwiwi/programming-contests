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

struct XorBoard {
  int count(int H, int W, int Rcount, int Ccount, int S);
};

typedef long long ll;
const ll MOD = 555555555;

int cmb[2010][2010];

void init_cmb(int N) {
  cmb[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    cmb[i][0] = 1;
    for (int j = 1; j <= i; ++j) cmb[i][j] = (cmb[i-1][j-1] + cmb[i-1][j]) % MOD;
  }
}


int mem[2000][2000];

ll solve2(int r, int n) {
  if (r == 0) {
    if (n > 0) return 0;
    else return 1;
  }

  if (mem[r][n] != -1) {
    return mem[r][n];
  }
  else {
    ll res = solve2(r - 1, n);
    if (n > 0) (res += solve2(r, n - 1)) %= MOD;
    return mem[r][n] = res;
  }
}


ll solve1(int R, int r, int n) {
  if (n < r) return 0;
  n -= r;

  if (n % 2 != 0) return 0;
  n /= 2;

  ll res = 0;
  for (int k = 0; k <= n; ++k) {
    (res += solve2(r, k) * solve2(R - r, n - k)) %= MOD;
  }
  (res *= cmb[R][r]) %= MOD;
  return res;
}


ll row[2000], col[2000];

int XorBoard::count(int R, int C, int Rcount, int Ccount, int S) {
  init_cmb(2000);
  memset(mem, -1, sizeof(mem));

  for (int r = 0; r <= R; ++r) row[r] = solve1(R, r, Rcount);
  for (int c = 0; c <= C; ++c) col[c] = solve1(C, c, Ccount);

  ll res = 0;
  for (int r1 = 0; r1 <= R; ++r1) {
    int r0 = R - r1;

    if (r0 == r1) {
      if (S - r1 * C == 0) {
        for (int c1 = 0; c1 <= C; ++c1) {
          (res += row[r1] * col[c1]) %= MOD;
        }
      }
    } else {
      int t = S - r1 * C;
      if (t % (r0 - r1) == 0) {
        int c1 = t / (r0 - r1);
        if (0 <= c1 && c1 <= C) (res += row[r1] * col[c1]) %= MOD;
      }
    }
  }

  return res;
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
			int Rcount                = 2;
			int Ccount                = 2;
			int S                     = 4;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int H                     = 2;
			int W                     = 2;
			int Rcount                = 0;
			int Ccount                = 0;
			int S                     = 1;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int H                     = 10;
			int W                     = 20;
			int Rcount                = 50;
			int Ccount                = 40;
			int S                     = 200;
			int expected__            = 333759825;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int H                     = 1200;
			int W                     = 1000;
			int Rcount                = 800;
			int Ccount                = 600;
			int S                     = 4000;
			int expected__            = 96859710;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int H                     = 555;
			int W                     = 555;
			int Rcount                = 555;
			int Ccount                = 555;
			int S                     = 5550;
			int expected__            = 549361755;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int H                     = ;
			int W                     = ;
			int Rcount                = ;
			int Ccount                = ;
			int S                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int H                     = ;
			int W                     = ;
			int Rcount                = ;
			int Ccount                = ;
			int S                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int H                     = ;
			int W                     = ;
			int Rcount                = ;
			int Ccount                = ;
			int S                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
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
