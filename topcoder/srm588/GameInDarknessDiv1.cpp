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
#include <tuple>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define eb emplace_back
#define mp make_pair

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

class GameInDarknessDiv1 {
 public:
  string check(vector <string> field);
};

int W, H;
vector<string> F;

void bfs(int sx, int sy, int dis[60][60]) {
  queue<pair<int, int> > que;
  rep (y, H) rep (x, W) dis[y][x] = -1;
  que.push({sx, sy});
  dis[sy][sx] = 0;
  while (!que.empty()) {
    int x, y;
    tie(x, y) = que.front();
    que.pop();

    rep (d, 4) {
      int tx = x + dx[d], ty = y + dy[d];
      if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
      if (F[ty][tx] == '#' || dis[ty][tx] != -1) continue;
      que.push({tx, ty});
      dis[ty][tx] = dis[y][x] + 1;
    }
  }
}

int sz[60][60][5];

int dfs_sz(int x, int y, int pd) {
  if (x < 0 || W <= x || y < 0 || H <= y) return INT_MIN;
  if (F[y][x] == '#') return INT_MIN;
  if (sz[y][x][pd] != -1) return sz[y][x][pd];

  int res = 1;
  rep (d, 4) {
    if ((d + 2) % 4 == pd) continue;
    res = max(res, 1 + dfs_sz(x + dx[d], y + dy[d], d));
  }
  return sz[y][x][pd] = res;
}

string GameInDarknessDiv1::check(vector <string> field) {
  H = field.size();
  W = field[0].length();
  F = field;

  int disA[60][60], disB[60][60];
  rep (y, H) rep (x, W) {
    if (F[y][x] == 'A') bfs(x, y, disA);
    if (F[y][x] == 'B') bfs(x, y, disB);
  }

  memset(sz, -1, sizeof(sz));
  rep (y, H) rep (x, W) if (F[y][x] != '#') {
    if (disA[y][x] <= disB[y][x] + 1) continue;

    int c = 0;
    rep (d, 4) if (dfs_sz(x + dx[d], y + dy[d], d) > 2) ++c;
    if (c >= 3) return "Bob wins";
    // printf("%d %d: %d\n", x, y, c);
  }

  return "Alice wins";
}















// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
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
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}

	int verify_case(int casenum, const string &expected, const string &received, std::clock_t elapsed) {
		std::cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;

		if (verdict == "FAILED") {
			std::cerr << "    Expected: \"" << expected << "\"" << std::endl;
			std::cerr << "    Received: \"" << received << "\"" << std::endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string field[]            = {"A.B..",
 "##.##",
 "##.##"};
			string expected__         = "Alice wins";

			std::clock_t start__      = std::clock();
			string received__         = GameInDarknessDiv1().check(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string field[]            = {"A.B..",
 ".#.#.",
 "#..##"};
			string expected__         = "Bob wins";

			std::clock_t start__      = std::clock();
			string received__         = GameInDarknessDiv1().check(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string field[]            = {"#...#",
 ".#A#.",
 "..B..",
 ".#.#.",
 "#...#"};
			string expected__         = "Alice wins";

			std::clock_t start__      = std::clock();
			string received__         = GameInDarknessDiv1().check(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string field[]            = {"##..#",
 "A.#..",
 "#B..#",
 "#.##.",
 "....."};
			string expected__         = "Alice wins";

			std::clock_t start__      = std::clock();
			string received__         = GameInDarknessDiv1().check(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string field[]            = {"##################################################",
 "###..................#................#........###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###..........#######........#.#######........#.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "###B.........#######..........#######..A.......###",
 "##################################################"}
;
			string expected__         = "Bob wins";

			std::clock_t start__      = std::clock();
			string received__         = GameInDarknessDiv1().check(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string field[]            = {"###.#",
 "###..",
 "A..B#",
 "###..",
 "###.#"};
			string expected__         = "Alice wins";

			std::clock_t start__      = std::clock();
			string received__         = GameInDarknessDiv1().check(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string field[]            = {".....#.##.##.#.#",
 ".###.#.##.##....",
 "#......B#...#.#.",
 "#.#A#.#.#.#..##.",
 "...#..#....#...."};
			string expected__         = "Alice wins";

			std::clock_t start__      = std::clock();
			string received__         = GameInDarknessDiv1().check(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			string field[]            = {"...#.....###....#.....#...#.#.",
 ".#..#.##..#..#.#..###...#.....",
 "..#..#..#...#.#..#....##.#.###",
 ".#.#...###.#..#.#..###....#...",
 "...##.###..#.#..#.#...#.##..#.",
 ".#..#..#..#...#.#.#.#.#..#.#..",
 "..#..#.#.#..#..##.#.#..#.##..#",
 ".#.###.#.##..#.....A##......#.",
 "#.........#.#..#.###..###.#...",
 "..###.#.#.#..#.#....#.....#.#.",
 ".#..#.#.####.#..#.#..#.#.###..",
 "..#...#...#..#.#...#.#..#.#..#",
 "#..#.#..#.#.#..###.#.#.#....#.",
 "..#..##.##...#....#..#.#.####.",
 "#..#...#...#..#.#..###.#......",
 "#.#.##...#..#..#.#....#..#.#.#",
 "....#..##.#..#....#.#.#.#...#.",
 ".#.#..#....#.#.##..#..##..#.#.",
 "..##.#..##.#..#..#..#...#.#...",
 "#.#..##..#..#..#..#..##.#.#.#.",
 "..#.#.#.#.#..#...##.#...#..#..",
 ".##.....#..#.#.#.#..#.##.#..#.",
 "...#.#.#..#..#.###.#..#...#.#.",
 ".#..#....#..#.#...###.#.#..#..",
 ".#.#.#####.#....#..#..#.##.#.#",
 ".#...#......#.#..###B#....#...",
 "..###..####.#..#.#...#.#.#..#.",
 "#.#..#.#..#.#.#..#.#..#....#..",
 "..#.##..#.#.#.####..#.#####..#",
 "#.....#...#.#......#.......#.."}
;
			string expected__         = "Bob wins";

			std::clock_t start__      = std::clock();
			string received__         = GameInDarknessDiv1().check(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 8: {
			string field[]            = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = GameInDarknessDiv1().check(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string field[]            = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = GameInDarknessDiv1().check(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			string field[]            = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = GameInDarknessDiv1().check(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
