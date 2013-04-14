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

struct SpellCards {
  int maxDamage(vector <int> level, vector <int> damage);
};

int dp[110][110][110];  // dp[i][k][s] := [i, i + k), |s| free cards

int SpellCards::maxDamage(vector <int> level_, vector <int> damage_) {
  int org = level_.size();

  vector<int> L(all(level_ )); L.insert(L.end(), all(level_ ));
  vector<int> D(all(damage_)); D.insert(D.end(), all(damage_));
  int N = L.size();

  memset(dp, 0, sizeof(dp));
  int ans = 0;

  for (int k = 1; k <= org; ++k) {
    for (int i = 0; i + k <= N; ++i) {  // [i, i + k)
      for (int s = 0; s <= k; ++s) {
        // We don't use card |i|
        if (s > 0) {
          dp[i][k][s] = max(dp[i][k - 1][s - 1], dp[i + 1][k - 1][s - 1]);
        }

        // We use card |i|
        int ts = s + L[i] - 1;
        if (ts <= k - 1) {
          dp[i][k][s] = max(dp[i][k][s], D[i] + dp[i + 1][k - 1][ts]);
        }
        ans = max(ans, dp[i][k][s]);
      }
    }
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
			int level[]               = {1,1,1};
			int damage[]              = {10,20,30};
			int expected__            = 60;

			clock_t start__           = clock();
			int received__            = SpellCards().maxDamage(vector <int>(level, level + (sizeof level / sizeof level[0])), vector <int>(damage, damage + (sizeof damage / sizeof damage[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int level[]               = {3,3,3};
			int damage[]              = {10,20,30};
			int expected__            = 30;

			clock_t start__           = clock();
			int received__            = SpellCards().maxDamage(vector <int>(level, level + (sizeof level / sizeof level[0])), vector <int>(damage, damage + (sizeof damage / sizeof damage[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int level[]               = {4,4,4};
			int damage[]              = {10,20,30};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = SpellCards().maxDamage(vector <int>(level, level + (sizeof level / sizeof level[0])), vector <int>(damage, damage + (sizeof damage / sizeof damage[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int level[]               = {50,1,50,1,50};
			int damage[]              = {10,20,30,40,50};
			int expected__            = 60;

			clock_t start__           = clock();
			int received__            = SpellCards().maxDamage(vector <int>(level, level + (sizeof level / sizeof level[0])), vector <int>(damage, damage + (sizeof damage / sizeof damage[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int level[]               = {2,1,1};
			int damage[]              = {40,40,10};
			int expected__            = 80;

			clock_t start__           = clock();
			int received__            = SpellCards().maxDamage(vector <int>(level, level + (sizeof level / sizeof level[0])), vector <int>(damage, damage + (sizeof damage / sizeof damage[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int level[]               = {1,2,1,1,3,2,1};
			int damage[]              = {10,40,10,10,90,40,10};
			int expected__            = 170;

			clock_t start__           = clock();
			int received__            = SpellCards().maxDamage(vector <int>(level, level + (sizeof level / sizeof level[0])), vector <int>(damage, damage + (sizeof damage / sizeof damage[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int level[]               = {1,2,2,3,1,4,2};
			int damage[]              = {113,253,523,941,250,534,454};
			int expected__            = 1918;

			clock_t start__           = clock();
			int received__            = SpellCards().maxDamage(vector <int>(level, level + (sizeof level / sizeof level[0])), vector <int>(damage, damage + (sizeof damage / sizeof damage[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			int level[]               = ;
			int damage[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SpellCards().maxDamage(vector <int>(level, level + (sizeof level / sizeof level[0])), vector <int>(damage, damage + (sizeof damage / sizeof damage[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int level[]               = ;
			int damage[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SpellCards().maxDamage(vector <int>(level, level + (sizeof level / sizeof level[0])), vector <int>(damage, damage + (sizeof damage / sizeof damage[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int level[]               = ;
			int damage[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SpellCards().maxDamage(vector <int>(level, level + (sizeof level / sizeof level[0])), vector <int>(damage, damage + (sizeof damage / sizeof damage[0])));
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
