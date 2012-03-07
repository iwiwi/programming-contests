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

struct BinaryPolynomialDivOne {
  int findCoefficient(vector <int> a, long long m, long long k);
};

typedef long long  ll;

map<ll, int> mem[110];
vector<ll> B, M;

int search(int i, ll r) {
  if (r < 0) return 0;

  if (i == (int)M.size()) {
    if (r == 0) return 1;
    else return 0;
  }

  if (r > 2 * (B.back() << M[i])) return 0;

  if (mem[i].count(r)) return mem[i][r];

  int res = 0;
  rep (j, B.size()) {
    res ^= search(i + 1, r - (B[j] << M[i]));
  }
  return mem[i][r] = res;
}

int BinaryPolynomialDivOne::findCoefficient(vector<int> a, long long m, long long k) {
  M.clear();
  B.clear();

  rep (i, 60) if (m & (1LL << i)) M.pb(i);
  reverse(all(M));
  rep (i, a.size()) if (a[i] == 1) B.pb(i);

  rep (i, M.size()) mem[i].clear();
  return search(0, k);
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
			int a[]                   = {1, 0, 1};
			long long m               = 3;
			long long k               = 4;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = BinaryPolynomialDivOne().findCoefficient(vector <int>(a, a + (sizeof a / sizeof a[0])), m, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {1, 0, 1};
			long long m               = 3;
			long long k               = 5;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = BinaryPolynomialDivOne().findCoefficient(vector <int>(a, a + (sizeof a / sizeof a[0])), m, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {0, 0, 1, 1, 0, 1};
			long long m               = 7;
			long long k               = 15;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = BinaryPolynomialDivOne().findCoefficient(vector <int>(a, a + (sizeof a / sizeof a[0])), m, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {1};
			long long m               = 1;
			long long k               = 0;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = BinaryPolynomialDivOne().findCoefficient(vector <int>(a, a + (sizeof a / sizeof a[0])), m, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1};
			long long m               = 2229508454872453LL;
			long long k               = 96130299655104846LL;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = BinaryPolynomialDivOne().findCoefficient(vector <int>(a, a + (sizeof a / sizeof a[0])), m, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int a[]                   = ;
			long long m               = ;
			long long k               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BinaryPolynomialDivOne().findCoefficient(vector <int>(a, a + (sizeof a / sizeof a[0])), m, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a[]                   = ;
			long long m               = ;
			long long k               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BinaryPolynomialDivOne().findCoefficient(vector <int>(a, a + (sizeof a / sizeof a[0])), m, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a[]                   = ;
			long long m               = ;
			long long k               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BinaryPolynomialDivOne().findCoefficient(vector <int>(a, a + (sizeof a / sizeof a[0])), m, k);
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
