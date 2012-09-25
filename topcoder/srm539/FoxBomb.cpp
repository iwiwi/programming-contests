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

struct FoxBomb {
  int getMinimumCost(vector <string> grid);
};

const int INF = 987654;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int H, W;
vector<string> F;
int mem[60][60][5][3];

// s = 0: nothing
// s = 1: coming
// s = 2: necessasry
int search(int x, int y, int d, int s) {
  if (F[y][x] == '#') {
    if (s == 2) return INF;
    else return 0;
  }
  if (mem[y][x][d][s] != -1) return mem[y][x][d][s];

  int res = INF;

  // Place
  {
    int tmp = 1;
    rep (td, 4) if (d != (td + 2) % 4) tmp += search(x + dx[td], y + dy[td], td, 1);
    res = min(res, tmp);
  }

  // Don't place
  if (s == 1) {
    int tmp = 0;
    rep (td, 4) if (d != (td + 2) % 4) tmp += search(x + dx[td], y + dy[td], td, td == d ? 1 : 0);
    res = min(res, tmp);
  }
  rep (cd, 4) if (d != (cd + 2) % 4) {
    int tmp = 0;
    rep (td, 4) if (d != (td + 2) % 4) {
      int ts;
      if (td == cd) ts = 2;
      else if (td == (cd + 2) % 4) ts = 1;
      else if (td == d) ts = s;
      else ts = 0;
      tmp += search(x + dx[td], y + dy[td], td, ts);
    }
    res = min(res, tmp);
  }

  return mem[y][x][d][s] = res;
}

int FoxBomb::getMinimumCost(vector <string> grid) {
  grid.insert(grid.begin(), string(grid[0].length(), '#'));
  grid.insert(grid.end(),   string(grid[0].length(), '#'));
  rep (y, grid.size()) grid[y] = '#' + grid[y] + '#';
  H = grid.size();
  W = grid[0].length();
  F = grid;

  rep (y, H) rep (x, W) {
    if (grid[y][x] == '.') {
      memset(mem, -1, sizeof(mem));
      return search(x, y, 4, 0);
    }
  }
  return -1;
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
			string grid[]             = {"#..."
,"..##"
,"#.##"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = FoxBomb().getMinimumCost(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string grid[]             = {".#.#.#."
,"......."
,".#.#.#."};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = FoxBomb().getMinimumCost(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string grid[]             = {"######################################"
,"######################################"
,"###.....................##############"
,"###.###################.###....#...###"
,"###.###################.###.######.###"
,"###.###################.###.######.###"
,"###.###################.###.######.###"
,"###.###################.###.######.###"
,"###.###################.###.######.###"
,"###.........####........###.######.###"
,"###########.###########.###........###"
,"###########.###########.##########.###"
,"###########.###########.##########.###"
,"###########.###########.##########.###"
,"###########.###########.##########.###"
,"##..........##..........##########.###"
,"#######################............###"
,"######################################"};
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = FoxBomb().getMinimumCost(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string grid[]             = {".#."
,"..."
,"#.#"
,"..."
,".#."}
;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = FoxBomb().getMinimumCost(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string grid[]             = {"."};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = FoxBomb().getMinimumCost(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string grid[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxBomb().getMinimumCost(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string grid[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxBomb().getMinimumCost(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string grid[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxBomb().getMinimumCost(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
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
