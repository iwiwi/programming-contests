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

struct GogoXBallsAndBins {
  int solve(vector <int> T, int moves);
};

typedef long long ll;

const ll MOD = 1000000009;

int N, M;
vector<int> T;
map<int, int> mem[60][60][60];

ll search(int k, int l, int r, int m) {
  if (k == N) {
    if (l == 0 && r == 0 && m == M * 2) return 1;
    else return 0;
  }
  if (mem[k][l][r].count(m)) return mem[k][l][r][m];

  ll res = 0;

  // immediately place left
  if (l > 0) {
    if (r > 0) {  // immediately come from left
      res += l * r * search(k + 1, l - 1, r - 1, m + T[k] + T[k]);
    }
    {  // will come from right
      res += l * search(k + 1, l, r, m + T[k] - T[k]);
    }
  }

  // will place right
  if (r + 1 <= N - k) {
    {  // immediately come from left (or myself)
      res += (r + 1) * search(k + 1, l, r, m - T[k] + T[k]);
    }
    {  // will come from right
      res += search(k + 1, l + 1, r + 1, m - T[k] - T[k]);
    }
  }

  res %= MOD;
  return mem[k][l][r][m] = res;
}

int GogoXBallsAndBins::solve(vector <int> T_, int moves) {
  T = T_;
  N = T.size();
  M = moves;

  rep (i, N) rep (j, N) rep (k, N) mem[i][j][k].clear();
  return search(0, 0, 0, 0);
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
			int T[]                   = {1, 2, 3};
			int moves                 = 1;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int T[]                   = {1, 2, 3};
			int moves                 = 2;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int T[]                   = {1, 2, 3};
			int moves                 = 3;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int T[]                   = {1, 2, 3};
			int moves                 = 0;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int T[]                   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
			int moves                 = 64;
			int expected__            = 625702391;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int T[]                   = ;
			int moves                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int T[]                   = ;
			int moves                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int T[]                   = ;
			int moves                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
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
