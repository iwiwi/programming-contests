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

struct DengklekBuildingRoads {
  int numWays(int N, int M, int K);
};

typedef long long ll;
const ll MOD = 1000000007;

int mem[40][1 << 9][40][10];
int N, M, K;

int search(int p, int b, int m, int k) {
  if (k > K) {
    if (b & 1) return 0;
    else return search(p + 1, b >> 1, m, 1);
  }
  if (p == N) {
    if (m == 0) return 1;
    else return 0;
  }
  if (mem[p][b][m][k] != -1) return mem[p][b][m][k];

  ll res = 0;

  // connect
  if (m > 0 && p + k < N) res += search(p, b ^ 1 ^ (1 << k), m - 1, k);
  // don't connect
  res += search(p, b, m, k + 1);

  res %= MOD;
  return mem[p][b][m][k] = res;
}

int DengklekBuildingRoads::numWays(int N_, int M_, int K_) {
  N = N_;
  M = M_;
  K = K_;

  memset(mem, -1, sizeof(mem));
  return search(0, 0, M, 1);
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
			int N                     = 3;
			int M                     = 4;
			int K                     = 1;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = DengklekBuildingRoads().numWays(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 4;
			int M                     = 3;
			int K                     = 3;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = DengklekBuildingRoads().numWays(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 2;
			int M                     = 1;
			int K                     = 1;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = DengklekBuildingRoads().numWays(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 5;
			int M                     = 0;
			int K                     = 3;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = DengklekBuildingRoads().numWays(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 10;
			int M                     = 20;
			int K                     = 5;
			int expected__            = 26964424;

			clock_t start__           = clock();
			int received__            = DengklekBuildingRoads().numWays(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int N                     = 2;
			int M                     = 2;
			int K                     = 1;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = DengklekBuildingRoads().numWays(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

        /*      case 6: {
			int N                     = ;
			int M                     = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DengklekBuildingRoads().numWays(N, M, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int M                     = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DengklekBuildingRoads().numWays(N, M, K);
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
