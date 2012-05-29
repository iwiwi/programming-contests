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

struct SplittingFoxes {
  int sum(long long n, int S, int L, int R);
};


typedef long long ll;

const ll MOD = 1000000007;

typedef long long number;
typedef vector<number> vec_t;
typedef vector<vec_t> mat_t;

#define NOR(x) ((x) % MOD)

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

mat_t identity(int n) {
  mat_t A(n, vec_t(n));
  for (int i = 0; i < n; i++) A[i][i] = 1;
  return A;
}

mat_t multiply(const mat_t &A, const mat_t &B) {
  mat_t C(A.size(), vec_t(B[0].size()));
  rep (i, C.size()) rep (k, A[i].size()) rep (j, C[i].size()) {
    C[i][j] = NOR(C[i][j] + A[i][k] * B[k][j]);
  }
  return C;
}

mat_t power(const mat_t &A, long long p) {
  if (p == 0) return identity(A.size());
  if (p == 1) return A;
  mat_t B = power(multiply(A, A), p / 2);
  if (p % 2 == 1) B = multiply(B, A);
  return B;
}

int SplittingFoxes::sum(long long n, int S_, int L_, int R_) {
  ll S = S_, L = L_, R = R_;

  mat_t A(4, vec_t(4));
  A[0][0] = S - L - R; A[0][2] = S;
  A[1][1] = S;         A[1][2] = -L + R; A[1][3] = S;
  A[2][1] = L - R;     A[2][2] = S;
  A[3][3] = S + L + R;

  A = power(A, n);
  return (A[0][3] % MOD + MOD) % MOD;
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
			long long n               = 58;
			int S                     = 2;
			int L                     = 0;
			int R                     = 0;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = SplittingFoxes().sum(n, S, L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long n               = 3;
			int S                     = 1;
			int L                     = 1;
			int R                     = 0;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = SplittingFoxes().sum(n, S, L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long n               = 5;
			int S                     = 1;
			int L                     = 3;
			int R                     = 2;
			int expected__            = 34;

			clock_t start__           = clock();
			int received__            = SplittingFoxes().sum(n, S, L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long n               = 5;
			int S                     = 1;
			int L                     = 2;
			int R                     = 3;
			int expected__            = 999999973;

			clock_t start__           = clock();
			int received__            = SplittingFoxes().sum(n, S, L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long n               = 123456789;
			int S                     = 987654321;
			int L                     = 544;
			int R                     = 544;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = SplittingFoxes().sum(n, S, L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			long long n               = 65536;
			int S                     = 1024;
			int L                     = 512;
			int R                     = 4096;
			int expected__            = 371473914;

			clock_t start__           = clock();
			int received__            = SplittingFoxes().sum(n, S, L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			long long n               = ;
			int S                     = ;
			int L                     = ;
			int R                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SplittingFoxes().sum(n, S, L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long n               = ;
			int S                     = ;
			int L                     = ;
			int R                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SplittingFoxes().sum(n, S, L, R);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			long long n               = ;
			int S                     = ;
			int L                     = ;
			int R                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SplittingFoxes().sum(n, S, L, R);
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
