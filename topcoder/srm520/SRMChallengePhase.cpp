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

struct SRMChallengePhase {
  int countWays(vector <string> codersAttempted, vector <string> codersChallenged);
};

typedef long long ll;

const ll MOD = 1000000007;

ll fac[2510];

void init_fac(int N) {
  fac[0] = 1;
  for (int i = 1; i <= N; ++i) fac[i] = fac[i - 1] * i % MOD;
}

int cmb[2510][2510];

void init_cmb(int N) {
  cmb[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    cmb[i][0] = 1;
    for (int j = 1; j <= i; ++j) cmb[i][j] = (cmb[i-1][j-1] + cmb[i-1][j]) % MOD;
  }
}

int dp[2510][2510];

int SRMChallengePhase::countWays(vector <string> codersAttempted, vector <string> codersChallenged) {
  string A = accumulate(all(codersAttempted), string());
  string B = accumulate(all(codersChallenged), string());
  int N = A.size();
  init_cmb(N);
  init_fac(N);

  int AY = count(all(A), 'Y'), BY = count(all(B), 'Y');
  int YY = 0;
  rep (i, N) if (A[i] == 'Y' && B[i] == 'Y') ++YY;
  if (BY > AY) return 0;

  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;
  for (int n = 1; n <= AY; ++n) {
    dp[n][0] = 1;
    for (int yy = 1; yy <= min(n, YY); ++yy) {
      dp[n][yy] = (dp[n - 1][yy] + ll(n - yy) * dp[n - 1][yy - 1]) % MOD;
    }
  }

  ll ans = dp[AY][YY];
  (ans *= fac[YY]) %= MOD;
  (ans *= fac[AY - YY]) %= MOD;
  (ans *= cmb[AY - YY][BY - YY] * fac[BY - YY] % MOD) %= MOD;
  rep (i, AY - BY) (ans *= N - 1) %= MOD;
  return (ans + MOD) % MOD;
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
			string codersAttempted[]  = {"YY"};
			string codersChallenged[] = {"NY"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string codersAttempted[]  = {"YY", "NN"};
			string codersChallenged[] = {"N", "NYY"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string codersAttempted[]  = {"YNNN"};
			string codersChallenged[] = {"NYY", "Y"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string codersAttempted[]  = {"N"};
			string codersChallenged[] = {"N"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string codersAttempted[]  = {"YYY"};
			string codersChallenged[] = {"NNY"};
			int expected__            = 24;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string codersAttempted[]  = {"YY", "N", "YYYY", "NN", "YYYYY"};
			string codersChallenged[] = {"N", "YYYYY", "N", "Y", "N", "YYYY", "N"};
			int expected__            = 807026001;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
        string codersAttempted[]  = {"YY"};
        string codersChallenged[] = {"YY"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			string codersAttempted[]  = ;
			string codersChallenged[] = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string codersAttempted[]  = ;
			string codersChallenged[] = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
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
