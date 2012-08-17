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

struct RandomColoring {
  double getProbability(int N, int maxR, int maxG, int maxB, int startR, int startG, int startB, int d1, int d2);
};

int R, G, B;
double val[60][60][60];
double sum[60][60][60];

void compute_sum() {
  rep (r, R) rep (g, G) rep (b, B) sum[r + 1][g + 1][b + 1] = val[r][g][b];
  rep (g, G + 1) rep (b, B + 1) rep (r, R) sum[r + 1][g][b] += sum[r][g][b];
  rep (b, B + 1) rep (r, R + 1) rep (g, G) sum[r][g + 1][b] += sum[r][g][b];
  rep (r, R + 1) rep (g, G + 1) rep (b, B) sum[r][g][b + 1] += sum[r][g][b];
}

double get_sum(int r, int g, int b) {  // [0, r) x [0, g) x [0, b)
  if (r <= 0 || g <= 0 || b <= 0) return 0;
  else return sum[min(r, R)][min(g, G)][min(b, B)];
}

double get_sum(int r0, int r1, int g0, int g1, int b0, int b1) {  // [r0, r1) x [g0, g1) x [b0, b1)
  int rs[] = {r0, max(r0, r1)}, gs[] = {g0, max(g0, g1)}, bs[] = {b0, max(b0, b1)};
  double s = 0;
  rep (ri, 2) rep (gi, 2) rep (bi, 2) s += get_sum(rs[ri], gs[gi], bs[bi]) * ((ri ^ gi ^ bi) ? +1 : -1);
  return s;
}


int D1, D2;

double get_sum2(int r, int g, int b) {
  return
      get_sum(r - D2, r + D2 + 1, g - D2, g + D2 + 1, b - D2, b + D2 + 1) -
      get_sum(r - D1 + 1, r + D1, g - D1 + 1, g + D1, b - D1 + 1, b + D1);
}

double to[60][60][60];

double RandomColoring::getProbability(int N, int maxR, int maxG, int maxB,
                                      int startR, int startG, int startB, int d1, int d2) {
  R = maxR;
  G = maxG;
  B = maxB;
  D1 = d1;
  D2 = d2;

  rep (r, R) rep (g, G) rep (b, B) val[r][g][b] = 1;
  compute_sum();
  rep (r, R) rep (g, G) rep (b, B) to[r][g][b] = max(1.0, get_sum2(r, g, b));

  memset(val, 0, sizeof(val));
  val[startR][startG][startB] = 1.0;

  rep (i, N - 1) {
    rep (r, R) rep (g, G) rep (b, B) val[r][g][b] /= to[r][g][b];
    compute_sum();
    rep (r, R) rep (g, G) rep (b, B) val[r][g][b] = get_sum2(r, g, b);
  }

  compute_sum();
  return 1.0 - get_sum2(startR, startG, startB);
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

	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ(double expected, double result) { if (isnan(expected)) { return isnan(result); } else if (isinf(expected)) { if (expected > 0) { return result > 0 && isinf(result); } else { return result < 0 && isinf(result); } } else if (isnan(result) || isinf(result)) { return false; } else if (fabs(result - expected) < MAX_DOUBLE_ERROR) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }

	int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) {
		cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received);
			if (rerr > 0) {
				sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int maxR                  = 5;
			int maxG                  = 1;
			int maxB                  = 1;
			int startR                = 2;
			int startG                = 0;
			int startB                = 0;
			int d1                    = 0;
			int d2                    = 1;
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = RandomColoring().getProbability(N, maxR, maxG, maxB, startR, startG, startB, d1, d2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 3;
			int maxR                  = 5;
			int maxG                  = 1;
			int maxB                  = 1;
			int startR                = 2;
			int startG                = 0;
			int startB                = 0;
			int d1                    = 0;
			int d2                    = 1;
			double expected__         = 0.22222222222222227;

			clock_t start__           = clock();
			double received__         = RandomColoring().getProbability(N, maxR, maxG, maxB, startR, startG, startB, d1, d2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 7;
			int maxR                  = 4;
			int maxG                  = 2;
			int maxB                  = 2;
			int startR                = 0;
			int startG                = 0;
			int startB                = 0;
			int d1                    = 3;
			int d2                    = 3;
			double expected__         = 1.0;

			clock_t start__           = clock();
			double received__         = RandomColoring().getProbability(N, maxR, maxG, maxB, startR, startG, startB, d1, d2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 10;
			int maxR                  = 7;
			int maxG                  = 8;
			int maxB                  = 9;
			int startR                = 1;
			int startG                = 2;
			int startB                = 3;
			int d1                    = 0;
			int d2                    = 10;
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = RandomColoring().getProbability(N, maxR, maxG, maxB, startR, startG, startB, d1, d2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 10;
			int maxR                  = 7;
			int maxG                  = 8;
			int maxB                  = 9;
			int startR                = 1;
			int startG                = 2;
			int startB                = 3;
			int d1                    = 4;
			int d2                    = 10;
			double expected__         = 0.37826245943967396;

			clock_t start__           = clock();
			double received__         = RandomColoring().getProbability(N, maxR, maxG, maxB, startR, startG, startB, d1, d2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int N                     = 3;
			int maxR                  = 3;
			int maxG                  = 2;
			int maxB                  = 2;
			int startR                = 1;
			int startG                = 0;
			int startB                = 0;
			int d1                    = 1;
			int d2                    = 2;
			double expected__         = 0.09090909090909148;

			clock_t start__           = clock();
			double received__         = RandomColoring().getProbability(N, maxR, maxG, maxB, startR, startG, startB, d1, d2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int N                     = ;
			int maxR                  = ;
			int maxG                  = ;
			int maxB                  = ;
			int startR                = ;
			int startG                = ;
			int startB                = ;
			int d1                    = ;
			int d2                    = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RandomColoring().getProbability(N, maxR, maxG, maxB, startR, startG, startB, d1, d2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int maxR                  = ;
			int maxG                  = ;
			int maxB                  = ;
			int startR                = ;
			int startG                = ;
			int startB                = ;
			int d1                    = ;
			int d2                    = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RandomColoring().getProbability(N, maxR, maxG, maxB, startR, startG, startB, d1, d2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int N                     = ;
			int maxR                  = ;
			int maxG                  = ;
			int maxB                  = ;
			int startR                = ;
			int startG                = ;
			int startB                = ;
			int d1                    = ;
			int d2                    = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RandomColoring().getProbability(N, maxR, maxG, maxB, startR, startG, startB, d1, d2);
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
