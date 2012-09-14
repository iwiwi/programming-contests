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

struct XorTravelingSalesman {
  int maxProfit(vector <int> cityValues, vector <string> roads);
};

bool vis[60][3000];

int XorTravelingSalesman::maxProfit(vector <int> A, vector <string> roads) {
  int N = A.size();

  queue<pair<int, int> > que;
  memset(vis, 0, sizeof(vis));

  que.push(mp(0, A[0]));
  vis[0][A[0]] = true;

  int ans = 0;

  while (!que.empty()) {
    int v = que.front().first;
    int x = que.front().second;
    que.pop();

    ans = max(ans, x);

    rep (tv, N) if (roads[v][tv] == 'Y') {
      int tx = x ^ A[tv];
      if (vis[tv][tx]) continue;
      que.push(mp(tv, tx));
      vis[tv][tx] = true;
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
			int cityValues[]          = {0, 7, 11, 5, 2};
			string roads[]            = {"NYNYY",
 "YNYNN",
 "NYNNN",
 "YNNNN",
 "YNNNN"};
			int expected__            = 14;

			clock_t start__           = clock();
			int received__            = XorTravelingSalesman().maxProfit(vector <int>(cityValues, cityValues + (sizeof cityValues / sizeof cityValues[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int cityValues[]          = {556};
			string roads[]            = {"N"};
			int expected__            = 556;

			clock_t start__           = clock();
			int received__            = XorTravelingSalesman().maxProfit(vector <int>(cityValues, cityValues + (sizeof cityValues / sizeof cityValues[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int cityValues[]          = {0, 4, 8, 32, 512};
			string roads[]            = {"NYYYY",
 "YNNNN",
 "YNNNN",
 "YNNNN",
 "YNNNN"};
			int expected__            = 556;

			clock_t start__           = clock();
			int received__            = XorTravelingSalesman().maxProfit(vector <int>(cityValues, cityValues + (sizeof cityValues / sizeof cityValues[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int cityValues[]          = {37, 1, 19, 64, 42, 41, 64, 64, 54, 16, 256, 36, 64, 2, 4, 2, 62, 29, 58, 64, 1, 32, 16, 256, 17, 2, 17, 4, 1, 64, 21, 8, 256, 63, 3, 1, 43, 15, 8, 39, 41, 8, 16, 8, 16, 256, 64, 512, 45, 64};
			string roads[]            = {"NNNNNNYYYYNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNYNNNNNNNYNNNNNNNNNNNNNNNNYYNNNYYNN",
 "NNNNNYYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNYNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNYNNYNYNNNNNNYNNNNNNNNNNYNNNNNNNNNNN",
 "NNYNNNYNNNNNNNNYNNYNNNYYNNNYNYNNNNYNNNNNNNNYNNNNNN",
 "YNYNNYNYNNNNNNNYNNNNNNNNNNNNNNNNNNNYNNNNNNNNYNNYNN",
 "YNNYNNYNYNYYNNNNNNNNNNNNNNNNNNNNNNYNNYNNNNNNNNNNNN",
 "YNNNNNNYNNNNNNNNNNNNNNYNYNNNNNNNNNNYYYNNNNNNNYNNNY",
 "YNNNNNNNNNNNNNNNNYNYNYNYYNNNYNNNNYNNNNNNNNNNNNNNNY",
 "NNNNNNNYNNNNYNNNNNNNNYYNNNYYNNNNYNYYNNNNNNNNNNNNNN",
 "NNNNNNNYNNNNNNYNNNNYYNNNYNNYYNNNNNNNNNNNNNYNYNNNNN",
 "NNNNNNNNNNYNNNNNYNNNNYNNNNNNNNNNYNYNNYNYNNNYNYNNNN",
 "NNNNNNNNNNNNNNNYNNNNNNNNNYNNNNNNNNNNNNYNNNNNNNNYNN",
 "NNNNNNNNNNNYNNNNNYNYNNYYNNNNNYNNNNNNNNNYNNYNNYNNNN",
 "NNNNYYYNNNNNNYNNNYYNNYNNNYNYYNNNNNNNNNYYYNNYNNYNYN",
 "NYNNNNNNNNNNYNNNNNNNYNNNYYNNNYNNNNYNNNNNNNNNNNNNNN",
 "NNNNNNNNNYNNNNYYNNNNNNYNNNYNNNNNYNNYNYYNNNNYNNNYNN",
 "NNNYYYNNNNNNNNNYNNNNNYNYNYNNNNNNNNYNNNNNNNNNNNNNNN",
 "NNNNNNNNNYNYNNYNNNNNNYNYYYNNNNNNNNNNNYNNYNNNNNYNNN",
 "NNNNYNNNNNNYNNNNYNNNNYNNNYYNNNYNNNYNNNNNNNNNNYNYNY",
 "NNNNNNNNNYYNYNNYNNYYYNYNNNNNNNNYNYNNNNNNNNNNYNNNNN",
 "NNNNNYNNYNYNNNYNNYNNNYNNNNNNNNNNNYNNYNYNNYNNNNNNNN",
 "NNNNNYNNNYNNNNYNNNYYNNNNNNNNNNNNNNNNNNNNNNYNNNYNNN",
 "NYNNNNNNYYNYNNNNYNNYNNNNNNNNNNYNNNNNNYNNNYNNYNNNNN",
 "NNNNNNNNNNNNNYNYYNYYYNNNNNNYNNNNNNNNNNNYYNNNNNNNYN",
 "NNNNNNNNNNYNNNNNNYNNYNNNNNNNNYNNNNYNNNNNNYYNNNNYNN",
 "NNNNYYNNNNYYNNNYNNNNNNNNNYNNNYYNYNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNYNYNNNYNNNNNNNNNNNNNYNNNNYNNNNNNNNYNNYNYN",
 "NNNNNYNNNNNNNNYNYNNNNNNNNNYYYNNNNNNNNYNNNNYNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNYNNNYNNYNNNNNYNNNNNNNNNNNNNNNY",
 "NNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNYNNNNNNNNNYNNNNNNN",
 "NNNNNNNNNNYNYNNNNYNNNNNNNNNYNNNYNNNYYNNNNNYNNNYNNN",
 "NNNNNNNNNYNNNNNNNNNNNYYNNNNNNNYNNNNNNNYNNYNNNNNNNN",
 "NNNNNYNYNNYNYNNNYNYNYNNNNNYNYNNNNNNYYNYNYNYNNNNNYN",
 "YNNNNNYNYNYNNNNNNYNNNNNNNNNNNNNNYNYNNNNNYNNYNNNYNN",
 "NNNNNNNNYNNNNNNNNNNNNNYNNNNNNNNNYNYNNNNNNYNNNNNNYN",
 "NNNNNNNYYNNNYNNNNYNYNNNNYNNNNYNNNNNNNNNNNYNNNNYNNN",
 "NNNNYNNNNNNNNYNYNYNNNNYNNNNNNNNNNYYNNNNYNNNNNNNNNY",
 "NNNNNNNNNNNNYNYYNNNNNNNNNYNNNNNNNNNNNNYNNNNNYNYYNN",
 "NNNNNNNNNNNNNNNYNNNYNNNNNYNNNNNNNNYYNNNNNNNNNNNNNN",
 "NYNNNNNNNNNNNNNNNNNNNNYNYNYNNNNNNYNNYYNNNNNNNNNNNN",
 "NYNNNNNNNNNYNNYNNNNNNNNYNNYNNYNYYNYNNNNNNNNNYNNNNN",
 "NNNNNYNNNNNNYNNYNYNNNNNNNNNNYNNNNNNYNNNNNNNNNNNNNY",
 "NNNNNNYNNNNYNNNNNNNNNYNNYNNNNNNNNNNNNNNYNNYNNYNNNY",
 "NNNNNNNNYNNNYNYNNNNNYNNNNNNNNNNNNNNNNNNNNNNNYNNNNN",
 "NYNNNNNNNNNNNNNYNNNYNNNYNNNNYNNNYNNNNYNYNNNNNNNNNN",
 "NYNNNNYNNNNNNYNNNYNNYNNNNNYNNNNNNNNYNNNYNNNNNNNNNN",
 "NNNNNNNNNNNNNNNYNNNNNNNNNYNNYNNNNNYNYNNNNNNNNNNNNN",
 "NNNNNNNNYYNNNNNNNNNNYNNNNNNNNNYNNNNNNNYNNNNYYNNNNN"};
			int expected__            = 895;

			clock_t start__           = clock();
			int received__            = XorTravelingSalesman().maxProfit(vector <int>(cityValues, cityValues + (sizeof cityValues / sizeof cityValues[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int cityValues[]          = ;
			string roads[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XorTravelingSalesman().maxProfit(vector <int>(cityValues, cityValues + (sizeof cityValues / sizeof cityValues[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int cityValues[]          = ;
			string roads[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XorTravelingSalesman().maxProfit(vector <int>(cityValues, cityValues + (sizeof cityValues / sizeof cityValues[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int cityValues[]          = ;
			string roads[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XorTravelingSalesman().maxProfit(vector <int>(cityValues, cityValues + (sizeof cityValues / sizeof cityValues[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
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
