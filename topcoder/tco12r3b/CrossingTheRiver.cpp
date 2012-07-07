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

struct CrossingTheRiver {
  string isItEvenPossible(int waterWidth, int landWidth, vector <int> blockHeight, int depth);
};

string CrossingTheRiver::isItEvenPossible(int W, int L, vector <int> A, int D) {
  int N = A.size();

  for (int h1 = 0; h1 <= 100; ++h1) {
    for (int h2 = h1; h2 <= 100; ++h2) {
      vector<int> cnt(110);
      rep (i, N) ++cnt[A[i]];

      int w = 0, l = 0;
      for (int y = D + 1; y <= D + h1 - 1; ++y) {
        if (cnt[y]-- == 0) goto ng;
        ++w;
      }
      for (int y = h1; y <= h2 - 1; ++y) {
        if (cnt[y]-- == 0) goto ng;
        ++l;
      }
      if (w > W || l > L) goto ng;

      {
        int tw = 0, tl = 0, twl = 0;
        if (h1 == 0) tl += L;

        for (int y = 0; y <= 100; ++y) {
          while (cnt[y]-- > 0) {
            bool bw = D <= y && y <= D + h1;
            bool bl = h1 <= y && y <= h2;
            if (bw && bl) ++twl;
            else if (bw) ++tw;
            else if (bl) ++tl;
          }
        }

        if (w + tw + twl < W) goto ng;
        if (w + tw < W) twl -= W - (w + tw);

        if (l + tl + twl < L) goto ng;

        return "POSSIBLE";
      }
   ng:;
    }
  }

  return "IMPOSSIBLE";
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

	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) {
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
			cerr << "    Expected: \"" << expected << "\"" << endl;
			cerr << "    Received: \"" << received << "\"" << endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int waterWidth            = 3;
			int landWidth             = 3;
			int blockHeight[]         = {3,4,4,5,5, 6};
			int depth                 = 2;
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int waterWidth            = 3;
			int landWidth             = 3;
			int blockHeight[]         = {3,4,4,5,6, 6};
			int depth                 = 2;
			string expected__         = "IMPOSSIBLE";

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int waterWidth            = 5;
			int landWidth             = 2;
			int blockHeight[]         = {4,4,4,4,4};
			int depth                 = 4;
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int waterWidth            = 5;
			int landWidth             = 5;
			int blockHeight[]         = {5,5,5,5,5,5, 2,3,4,4,6, 7, 3, 2};
			int depth                 = 2;
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int waterWidth            = 5;
			int landWidth             = 7;
			int blockHeight[]         = {6,6,6,6,6,6,6, 6,6,6,6,6,7,8,9,10};
			int depth                 = 5;
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int waterWidth            = 1;
			int landWidth             = 1;
			int blockHeight[]         = {5,3,4};
			int depth                 = 2;
			string expected__         = "IMPOSSIBLE";

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int waterWidth            = ;
			int landWidth             = ;
			int blockHeight[]         = ;
			int depth                 = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int waterWidth            = ;
			int landWidth             = ;
			int blockHeight[]         = ;
			int depth                 = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int waterWidth            = ;
			int landWidth             = ;
			int blockHeight[]         = ;
			int depth                 = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
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
