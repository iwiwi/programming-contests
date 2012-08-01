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

struct ConversionMachine {
  int countAll(string word1, string word2, vector <int> costs, int maxCost);
};

typedef long long ll;
const ll MOD = 1000000007;

typedef long long number;
typedef vector<number> vec_t;
typedef vector<vec_t> mat_t;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define IS0(x) ((x) == 0)
#define INV(x) inverse(x, MOD)
#define NOR(x) ((x) % MOD)

mat_t identity(int n) {
  mat_t A(n, vec_t(n));
  for (int i = 0; i < n; i++) A[i][i] = 1;
  return A;
}

// requirement: MOD * MOD * 16 < 2^64
mat_t multiply(const mat_t &A, mat_t B) {
  typedef unsigned long long ull;
  const ull MODMOD8 = MOD * MOD * 8;

  int n = A.size();
  rep (i, n) rep (j, i) swap(B[i][j], B[j][i]);

  mat_t C(n, vec_t(n));
  rep (i, n) rep (j, n) {
    const vec_t &a = A[i], &b = B[j];
    ull t = 0;
    int k;
    for (k = 0; k < n - 7; k += 8) {
      t += a[k + 0] * b[k + 0];
      t += a[k + 1] * b[k + 1];
      t += a[k + 2] * b[k + 2];
      t += a[k + 3] * b[k + 3];
      t += a[k + 4] * b[k + 4];
      t += a[k + 5] * b[k + 5];
      t += a[k + 6] * b[k + 6];
      t += a[k + 7] * b[k + 7];
      if (t > MODMOD8) t -= MODMOD8;
    }
    for (; k < n; ++k) {
      t += a[k + 0] * b[k + 0];
    }
    C[i][j] = t % MOD;
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

int L;
int id(int n0, int n1, int n2) {
  // return n0 * (L + 1) + n1;
  int s = n0 + n1;
  int t = s * (s + 1) / 2;
  return t + n0;
}

int ConversionMachine::countAll(string word1, string word2, vector <int> costs, int maxCost) {
  L = word1.length();

  int M = (L + 2) * (L + 1) / 2 + 1;
  mat_t A(M, vec_t(M));
  for (int n0 = 0; n0 <= L; ++n0) {
    for (int n1 = 0; n0 + n1 <= L; ++n1) {
      int n2 = L - n0 - n1;
      if (n1 > 0) A[id(n0, n1, n2)][id(n0, n1 - 1, n2 + 1)] = n2 + 1;
      if (n2 > 0) A[id(n0, n1, n2)][id(n0 + 1, n1, n2 - 1)] = n0 + 1;
      if (n0 > 0) A[id(n0, n1, n2)][id(n0 - 1, n1 + 1, n2)] = n1 + 1;
    }
  }
  A[M - 1][M - 1] = A[M - 1][id(L, 0, 0)] = 1;

  int n[3] = {}, s = 0;
  rep (i, L) {
    n[(word2[i] + 3 - word1[i]) % 3] += 1;
    while (word1[i] != word2[i]) {
      maxCost -= costs[word1[i] - 'a'];
      word1[i] = 'a' + (word1[i] - 'a' + 1) % 3;
      ++s;
      if (maxCost < 0) return 0;
    }
  }

  ll K = maxCost / (costs[0] + (ll)costs[1] + costs[2]);
  printf("s = %d, K = %lld, n = %d %d %d\n", s, K, n[0], n[1], n[2]);

  A = power(A, 1 + s + K * 3);
  return A[M - 1][id(n[0], n[1], n[2])];
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
			string word1              = "a";
			string word2              = "b";
			int costs[]               = {100,2,3};
			int maxCost               = 205;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = ConversionMachine().countAll(word1, word2, vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), maxCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string word1              = "abcba";
			string word2              = "abcba";
			int costs[]               = {67,23,43};
			int maxCost               = 0;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = ConversionMachine().countAll(word1, word2, vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), maxCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string word1              = "cccccccc";
			string word2              = "aaaaaaaa";
			int costs[]               = {10000000,1,1};
			int maxCost               = 100;
			int expected__            = 40320;

			clock_t start__           = clock();
			int received__            = ConversionMachine().countAll(word1, word2, vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), maxCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string word1              = "aa";
			string word2              = "cc";
			int costs[]               = {1,10,100};
			int maxCost               = 1787;
			int expected__            = 123611681;

			clock_t start__           = clock();
			int received__            = ConversionMachine().countAll(word1, word2, vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), maxCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string word1              = ;
			string word2              = ;
			int costs[]               = ;
			int maxCost               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ConversionMachine().countAll(word1, word2, vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), maxCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string word1              = ;
			string word2              = ;
			int costs[]               = ;
			int maxCost               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ConversionMachine().countAll(word1, word2, vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), maxCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string word1              = ;
			string word2              = ;
			int costs[]               = ;
			int maxCost               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ConversionMachine().countAll(word1, word2, vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), maxCost);
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
