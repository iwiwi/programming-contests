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
#include <bitset>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

struct XorAndSum {
  long long maxSum(vector<long long> number);
};

typedef long long ll;

typedef long long number;
typedef vector<number> vec_t;
typedef vector<vec_t> mat_t;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define IS0(x) ((x) == 0)
#define INV(x) 1
#define NOR(x) abs(x)

int gauss(mat_t &A) {
  int n = A[0].size(), m = A.size(), i, j, k, r = 0;
  for (i = 0; i < n && r < m; i++) {
    int piv = r;
    for (j = r + 1; j < m; j++) if (ABS(A[j][i]) > ABS(A[piv][i])) piv = j;
    swap(A[r], A[piv]);

    if (IS0((A[r][i]))) continue;

    for (j = 0; j < m; j++) {
      if (j != r) {
        for (k = n - 1; k >= i; k--)
          A[j][k] = NOR(A[j][k] - NOR(NOR(A[r][k] * A[j][i]) * INV(A[r][i])));
      }
    }

    r++;
  }
  return r;
}


const int B = 60;

long long XorAndSum::maxSum(vector<long long> number) {
  int N = number.size();

  mat_t A(N, vec_t(B));
  rep (i, N) {
    ll x = number[i];
    rep (j, B) A[i][j] = (x >> (B - j - 1)) & 1;
  }

  int r = gauss(A);
  printf("r = %d\n", r);

  // rep (i, N) { rep (j, B) printf("%lld", A[i][j]);puts(""); }

  vector<ll> ys(N);
  rep (i, N) rep (j, B) ys[i] |= ll(A[i][j]) << (B - j - 1);

  ll ma = 0;
  rep (i, N) ma ^= ys[i];
  // printf("ma = %lld\n", ma);

  ll ans = 0;
  rep (i, N) {
    ll z;
    if (i < r - 1) z = ma ^ ys[i + 1];
    else z = ma;
    // cout << bitset<10>((int)z) << endl;
    ans += z;
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
			long long number[]        = {1, 0};
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long number[]        = {1, 2, 3};
			long long expected__      = 8;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long number[]        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long number[]        = {2, 3, 5, 7, 11, 13, 17, 19};
			long long expected__      = 233;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long number[]        = {123456789012345LL, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			long long expected__      = 1234567890123450LL;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			long long number[]        = {627, 674, 281, 272, 289, 877, 62, 122, 603, 189, 615};
			long long expected__      = 10742;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			long long number[]        = {557};
			long long expected__      = 557;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			long long number[]        = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			long long number[]        = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			long long number[]        = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
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
