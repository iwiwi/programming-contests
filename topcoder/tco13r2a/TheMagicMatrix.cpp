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

struct TheMagicMatrix {
  int find(int n, vector <int> rows, vector <int> columns, vector <int> values);
};

typedef long long ll;
const ll MOD = 1234567891;

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}

ll pow_mod(ll a, ll k, ll m) {
  if (k == 0) return 1;
  ll t = pow_mod(a, k / 2, m);
  return mod(mod(t * t, m) * (k % 2 ? a : 1), m);
}

typedef long long number;
typedef vector<number> vec_t;
typedef vector<vec_t> mat_t;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define IS0(x) ((x) == 0)

int rank(mat_t A) {
  int n = A[0].size(), m = A.size(), i, j, k, r = 0;
  for (i = 0; i < n && r < m; i++) {
    int piv = r;
    for (j = r + 1; j < m; j++)
      if (ABS(A[j][i]) > ABS(A[piv][i])) piv = j;
    swap(A[r], A[piv]);

    if (IS0((A[r][i]))) continue;

    for (j = r + 1; j < m; j++)
      for (k = n - 1; k >= i; k--)
        A[j][k] = mod(A[j][k] * A[r][i] - A[r][k] * A[j][i], 10);

    r++;
  }
  return r;
}

int TheMagicMatrix::find(int N, vector <int> rows, vector <int> columns, vector <int> values) {
  if (N > 10) {
    return pow_mod(10, (N - 1) * (N - 1) - rows.size(), MOD) * 10 % MOD;
  }

  int C[20][20];
  memset(C, -1, sizeof(C));
  rep (i, rows.size()) C[rows[i]][columns[i]] = values[i];
  int F = 0;
  rep (i, N) rep (j, N) if (C[i][j] < 0) C[i][j] = ~(F++);

  ll ans = 0;
  for (int d = 0; d <= 9; ++d) {
    mat_t A1;
    vec_t b;

    // yoko
    rep (i, N) {
      int s = 0;
      vec_t r(F);
      rep (j, N) {
        if (C[i][j] >= 0) s += C[i][j];
        else r[~C[i][j]] = 1;
      }
      A1.pb(r);
      b.pb(mod(d - s, 10));
    }

    // tate
    rep (j, N) {
      int s = 0;
      vec_t r(F);
      rep (i, N) {
        if (C[i][j] >= 0) s += C[i][j];
        else r[~C[i][j]] = 1;
      }
      A1.pb(r);
      b.pb(mod(d - s, 10));
    }

    int r1 = rank(A1);

    mat_t A2 = A1;
    rep (i, A2.size()) A2[i].pb(b[i]);
    int r2 = rank(A2);
    printf("%d -> rank: %d %d\n", d, r1, r2);

    if (r1 == r2) {
      int z = F; // min(A1.size(), A1[0].size());
      (ans += pow_mod(10, z - r1, MOD)) %= MOD;
    }
  }

  return mod(ans, MOD);
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
			int n                     = 2;
			int rows[]                = {0, 1};
			int columns[]             = {1, 0};
			int values[]              = {4, 4};
			int expected__            = 10;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 2;
			int rows[]                = {0, 1};
			int columns[]             = {1, 0};
			int values[]              = {4, 7};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 4;
			int rows[]                = {0, 0, 0, 1, 2, 2, 2, 3, 3, 3};
			int columns[]             = {0, 1, 2, 3, 0, 1, 2, 0, 1, 2};
			int values[]              = {3, 5, 1, 9, 5, 1, 8, 6, 7, 1};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 474;
			int rows[]                = {44, 77};
			int columns[]             = {47, 74};
			int values[]              = {4, 7};
			int expected__            = 83494518;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
			int n                     = 2;
			int rows[]                = {};
			int columns[]             = {};
			int values[]              = {};
			int expected__            = pow_mod(10, 1, MOD) * 10 % MOD;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 5: {
			int n                     = 3;
			int rows[]                = {};
			int columns[]             = {};
			int values[]              = {};
			int expected__            = pow_mod(10, 4, MOD) * 10 % MOD;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int n                     = ;
			int rows[]                = ;
			int columns[]             = ;
			int values[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
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
