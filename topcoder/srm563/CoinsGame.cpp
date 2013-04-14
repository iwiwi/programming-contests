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

struct CoinsGame {
  int ways(vector <string> board);
};

typedef long long ll;
const ll MOD = 1000000009;

int H, W;
vector<string> fld;
bool vis[50][50];

int sx, sy;
vector<int> rs;
int wall, fall;
vector<int> wds[4];

int rel(int x, int y) {
  return 1000000 + ((y - sy) * W + (x - sx));
}

void dfs(int x, int y, int pd) {
  if (x < 0 || W <= x || y < 0 || H <= y) {
    fall |= 1 << pd;
    rs.pb(~rel(x, y));
    return;
  }
  if (fld[y][x] == '#') {
    wall |= 1 << pd;
    wds[pd].pb(pd % 2 == 0 ? (x - sx) : (y - sy));
    return;
  }

  if (vis[y][x]) return;
  vis[y][x] = true;
  rs.pb(rel(x, y));

  const int dx[4] = {1, 0, -1, 0};
  const int dy[4] = {0, 1, 0, -1};
  rep (d, 4) dfs(x + dx[d], y + dy[d], d);
}

int CoinsGame::ways(vector <string> board) {
  fld = board;
  H = fld.size();
  W = fld[0].length();

  map<vector<int>, int> cnt;
  ll tot = 1;

  rep (y, H) rep (x, W) {
    if (board[y][x] == '#') continue;
    (tot *= 2) %= MOD;

    memset(vis, 0, sizeof(vis));
    sx = x;
    sy = y;
    rs.clear();
    wall = fall = 0;
    rep (d, 4) wds[d].clear();
    dfs(x, y, -1);

    { // Process special cases (rectangles)
      int p = __builtin_popcount(fall);
      if (p != 1 && p != 2) goto normal;
      int w = ((1 << 4) - 1) ^ fall;
      if (w != wall) goto normal;

      rep (d, 4) {
        sort(all(wds[d]));
        wds[d].erase(unique(all(wds[d])), wds[d].end());
        if (wds[d].size() > 1) goto normal;
      }

      rs.clear();
      rs.pb(fall);
      rs.pb((fall & 5) ? x : y);
      rep (d, 4) if (fall & (1 << ((d + 2) % 4))) {
        rs.insert(rs.end(), all(wds[d]));;
      }
    }

    if (0) {
   normal:
      if (!fall) rs.clear();  // Empty sequence denotes absolutely safe cells
    }

    ++cnt[rs];
  }
  --tot;  // Nothing

  ll ans = tot;
  tr (cnt, ite) {
    int n = ite->second;
    ll t = 1;
    rep (i, n) (t *= 2) %= MOD;
    --t;  // Nothing

    (ans -= t) %= MOD;
  }

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
			string board[]            = {".."};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = CoinsGame().ways(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"##.#",
 ".###",
 "###.",
 "#.##"};
			int expected__            = 11;

			clock_t start__           = clock();
			int received__            = CoinsGame().ways(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"####",
 "#..#",
 "#..#",
 "####"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = CoinsGame().ways(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"#.#.#"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = CoinsGame().ways(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........"};
			int expected__            = 688856388;

			clock_t start__           = clock();
			int received__            = CoinsGame().ways(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			string board[]            = {"#..#", "#..#", "####"};
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = CoinsGame().ways(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 6: {
			string board[]            = {"....#....#..#.#.........#...#...........", "....#....#..#.#.........#...#.........##", "....#....#..#.#.........#...#........#..", "....#....#..#.#.........#...#........#..", "....#....#..#.#.........#...#.........##", "....######..###.........#####........#..", "......................................##", "........................................", "........................................", ".............................###########", "##...........................#..........", ".##..........................#..........", "..#..........................#..........", "..#..........................#..........", ".##........#######...........#..........", "##.........#.....#...........#..........", "...........#.....#...........###########", "...........#.....#......................", "##.........#######......................", ".##.....................................", "..#..........................###########", "..#..........................#..........", ".##..........................#..........", "##...........................#..........", ".................##..........#..........", "...............###.##........#..........", "..............#......##......###########", "............##..#...#..#................", ".............#....#....#.....###########", "#####.........##......#......#..........", "....#...........##.###.......#..........", "....#..###.......##..........###########", "#####..#.#..............................", "....#..#.###............................", "#####..#.#.#............................", "....#..#.#.#....##########..###.#####...", "#####..#.#.######..#.....#..#.#.#...#...", ".......#.#.#.#..#..#.....#..#.#.#...#...", ".......#.#.#.#..#..#.....#..#.#.#...#...", ".......#.#.#.#..#..#.....#..#.#.#...#..."}
;
			int expected__            = 194136388;

			clock_t start__           = clock();
			int received__            = CoinsGame().ways(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 7: {
			string board[]            = {"###################################", ".................#.................", ".................#.................", ".................#.................", ".................#.................", "###################################", "......#............................", "......#............................", "###################################", ".................#.................", ".................#.................", ".................#.................", ".................#.................", ".................#.................", "###################################", "......#............................", "......#............................", "......#............................", "###################################", ".................#.................", ".................#.................", ".................#.................", ".................#.................", ".................#.................", ".................#.................", "###################################", "......#............................", "......#............................", "......#............................", "......#............................", "......#............................", "......#............................", "......#............................", "......#............................", "###################################"}
;
			int expected__            = 156369431;

			clock_t start__           = clock();
			int received__            = CoinsGame().ways(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
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
