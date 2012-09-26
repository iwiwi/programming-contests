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

struct Stackol {
  int countPrograms(vector <string> outputFragments, int k);
};

const int MOD = 1000000007;

typedef long long ll;

ll dp[2510][11];

string S;
int L;
int B[2510];

int countit(int f, int t) {  // [f, t)
  int b = B[t] - B[f];
  int res = 0;

  // Case 1
  {
    int m = t - b;
    int lb = B[m] - B[f];
    int ra = (t - m) - (B[t] - B[m]);
    if (lb == ra && (t - m == 0 || S[m] == 'A')) ++res;
  }

  // Case 2
  if (b >= 1) {
    int m = t - (b - 1);
    int lb = B[m] - B[f];
    int ra = (t - m) - (B[t] - B[m]);
    if (lb == ra + 1 && (m - f >= 1 && S[f] == 'B')) ++res;
  }

  return res;
}

int Stackol::countPrograms(vector <string> outputFragments, int K) {
  S = accumulate(all(outputFragments), string());
  L = S.length();

  B[0] = 0;
  rep (i, L) B[i + 1] = B[i] + (S[i] == 'B');

  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;

  for (int i = 0; i <= L; ++i) {
    for (int k = 0; k <= K; ++k) dp[i][k] %= MOD;

    for (int j = i; j <= L; ++j) {  // [i, j)
      int c = countit(i, j);
      if (c > 0) {
        for (int k = 0; k < K; ++k) dp[j][k + 1] += c * dp[i][k];
      }
    }
  }

  return accumulate(dp[L], dp[L] + (K + 1), 0LL) % MOD;
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
			string outputFragments[]  = {"A"};
			int k                     = 2;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = Stackol().countPrograms(vector <string>(outputFragments, outputFragments + (sizeof outputFragments / sizeof outputFragments[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string outputFragments[]  = {"AAAA","BABA"};
			int k                     = 1;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = Stackol().countPrograms(vector <string>(outputFragments, outputFragments + (sizeof outputFragments / sizeof outputFragments[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string outputFragments[]  = {"AB"};
			int k                     = 2;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = Stackol().countPrograms(vector <string>(outputFragments, outputFragments + (sizeof outputFragments / sizeof outputFragments[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string outputFragments[]  = {"AAABABABAABA", "AA", "BBAB"};
			int k                     = 3;
			int expected__            = 94;

			clock_t start__           = clock();
			int received__            = Stackol().countPrograms(vector <string>(outputFragments, outputFragments + (sizeof outputFragments / sizeof outputFragments[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string outputFragments[]  = {"AAAAAAAAAAAA","B"};
			int k                     = 4;
			int expected__            = 120;

			clock_t start__           = clock();
			int received__            = Stackol().countPrograms(vector <string>(outputFragments, outputFragments + (sizeof outputFragments / sizeof outputFragments[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string outputFragments[]  = ;
			int k                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Stackol().countPrograms(vector <string>(outputFragments, outputFragments + (sizeof outputFragments / sizeof outputFragments[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string outputFragments[]  = ;
			int k                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Stackol().countPrograms(vector <string>(outputFragments, outputFragments + (sizeof outputFragments / sizeof outputFragments[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string outputFragments[]  = ;
			int k                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Stackol().countPrograms(vector <string>(outputFragments, outputFragments + (sizeof outputFragments / sizeof outputFragments[0])), k);
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
