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

struct LargestCircle {
  int radius(vector <string> grid);
};


inline int sqr(int x) { return x * x; }

int LargestCircle::radius(vector <string> grid) {
  int W = grid[0].length();
  int H = grid.size();

  int ans = 0;

  for (int cy = 1; cy < H; ++cy) {
    for (int cx = 1; cx < W; ++cx) {
      for (int r = 1; ; ++r) {
        if (cy - r < 0 || H < cy + r) break;
        if (cx - r < 0 || W < cx + r) break;

        for (int dy = -1; dy <= 1; dy += 2) {  // upper or lower
          for (int lx = 0; lx + 1 <= W; ++lx) {
            int rx = lx + 1;  // (lx, rx)
            if (rx <= cx - r || cx + r <= lx) continue;

            double ly = cy + dy * sqrt(sqr(r) - sqr(lx - cx));
            double ry = cy + dy * sqrt(sqr(r) - sqr(rx - cx));

            // double y0 = min(ly, ry), y1 = max(ly, ry);
            int y0 = floor(min(ly, ry));
            int y1 = ceil(max(ly, ry));
            for (int y = y0; y < y1; ++y) {
              if (grid[y][lx] == '#') goto ng;
            }
          }
        }

        ans = max(ans, r);
      ng:;
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
			string grid[]             = { "####",
  "#..#",
  "#..#",
  "####" };
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = LargestCircle().radius(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string grid[]             = { "############",
  "###......###",
  "##.######.##",
  "#.########.#",
  "#.##..####.#",
  "#.##..####.#",
  "#.########.#",
  "#.########.#",
  "#.########.#",
  "##.######.##",
  "###......###",
  "############" };
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = LargestCircle().radius(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string grid[]             = { ".........." };
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = LargestCircle().radius(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string grid[]             = { "#######",
  "#######",
  "#######",
  "#######",
  "#######" };
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = LargestCircle().radius(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string grid[]             = { "#####.......",
  "#####.......",
  "#####.......",
  "............",
  "............",
  "............",
  "............",
  "............",
  "............",
  "............" };
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = LargestCircle().radius(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string grid[]             = { "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  "...#...#...#...#...#...#...#...#...#...#...#...#..",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  ".#...#...#...#...#...#...#...#...#...#...#...#...#",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  "...#...#...#...#...#...#...#...#...#...#...#...#..",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  ".#...#...#...#...#...#...#...#...#...#...#...#...#",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  "...#...#...#...#...#...#...#...#...#...#...#...#.#",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#." }
;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = LargestCircle().radius(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string grid[]             = { ".........................#........................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  ".................................................." }
;
			int expected__            = 24;

			clock_t start__           = clock();
			int received__            = LargestCircle().radius(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string grid[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = LargestCircle().radius(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string grid[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = LargestCircle().radius(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string grid[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = LargestCircle().radius(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
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
