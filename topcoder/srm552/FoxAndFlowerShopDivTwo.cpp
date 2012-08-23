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

struct FoxAndFlowerShopDivTwo {
  int theMaxFlowers(vector <string> flowers, int r, int c);
};



int FoxAndFlowerShopDivTwo::theMaxFlowers(vector <string> flowers, int r, int c) {
  int H = flowers.size();
  int W = flowers[0].length();
  flowers[r][c] = 'J';

  int score[256] = {};
  score['F'] = 1;
  score['J'] = -99999;

  int ans = 0;
  rep (y0, H) for (int y1 = y0; y1 <= H; ++y1) {
    rep (x0, W) for (int x1 = x0; x1 <= W; ++x1) {
      int s = 0;
      for (int y = y0; y < y1; ++y) {
        for (int x = x0; x < x1; ++x) {
          s += score[flowers[y][x]];
        }
      }
      ans = max(ans, s);
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
			string flowers[]          = {"F.F",
 ".F.",
 ".F."};
			int r                     = 1;
			int c                     = 1;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivTwo().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), r, c);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string flowers[]          = {"F..",
 "...",
 "..."};
			int r                     = 0;
			int c                     = 0;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivTwo().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), r, c);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string flowers[]          = {".FF.F.F",
 "FF...F.",
 "..FF.FF"};
			int r                     = 1;
			int c                     = 2;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivTwo().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), r, c);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string flowers[]          = {"F",
 ".",
 "F",
 "F",
 "F",
 ".",
 "F",
 "F"};
			int r                     = 4;
			int c                     = 0;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivTwo().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), r, c);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string flowers[]          = {".FFF..F...",
 "FFF...FF.F",
 "..F.F.F.FF",
 "FF..F.FFF.",
 "..FFFFF...",
 "F....FF...",
 ".FF.FF..FF",
 "..F.F.FFF.",
 ".FF..F.F.F",
 "F.FFF.FF.F"};
			int r                     = 4;
			int c                     = 3;
			int expected__            = 32;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivTwo().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), r, c);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string flowers[]          = ;
			int r                     = ;
			int c                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivTwo().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), r, c);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string flowers[]          = ;
			int r                     = ;
			int c                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivTwo().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), r, c);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string flowers[]          = ;
			int r                     = ;
			int c                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivTwo().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), r, c);
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
