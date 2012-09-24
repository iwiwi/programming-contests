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

struct MeetInTheMaze {
  string getExpected(vector <string> maze);
};

typedef long long ll;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int W, H;
vector<string> fld;

void bfs(vector<vector<int> > &pot) {
  deque<pair<int, pair<int, int> > > start;
  rep (y, H) rep (x, W) if (pot[y][x] != -1) {
    start.pb(mp(pot[y][x], mp(x, y)));
  }
  sort(all(start));

  deque<pair<int, pair<int, int> > > que;
  for (int c = 0; !que.empty() || !start.empty(); ++c) {
    while (!start.empty() && start.front().first == c) {
      que.push_front(start[0]);
      start.pop_front();
    }

    while (!que.empty() && que.front().first == c) {
      int x = que.front().second.first;
      int y = que.front().second.second;
      que.pop_front();
      if (pot[y][x] != c) continue;

      rep (d, 4) {
        int tx = x + dx[d];
        int ty = y + dy[d];
        if (fld[ty][tx] == '#' || (pot[ty][tx] != -1 && pot[ty][tx] <= c + 1)) continue;
        pot[ty][tx] = c + 1;
        que.push_back(mp(c + 1, mp(tx, ty)));
      }
    }
  }
}

ll solve(int fx, int fy, int rx, int ry) {
  vector<vector<int> > fp(H, vector<int>(W, -1)); fp[fy][fx] = 0; bfs(fp);
  vector<vector<int> > rp(H, vector<int>(W, -1)); rp[ry][rx] = 0; bfs(rp);

  vector<vector<int> > mp(H, vector<int>(W, -1));
  rep (y, H) rep (x, W) {
    if (fp[y][x] != -1 && rp[y][x] != -1) mp[y][x] = fp[y][x] + rp[y][x];
  }

  ll res = 0;
  bfs(mp);
  rep (y, H) rep (x, W) if (fld[y][x] == 'L') {
    if (mp[y][x] == -1) throw "unreachable";
    res += mp[y][x];
  }
  return res;
}

ll gcd(ll a, ll b) {
  return a % b == 0 ? b : gcd(b, a % b);
}

string MeetInTheMaze::getExpected(vector <string> maze) {
  maze.insert(maze.begin(), string(maze[0].length(), '#'));
  maze.insert(maze.end(),   string(maze[0].length(), '#'));
  rep (y, maze.size()) maze[y] = '#' + maze[y] + '#';
  W = maze[0].length();
  H = maze.size();
  fld = maze;

  string all_maze = accumulate(all(maze), string());
  int F = count(all(all_maze), 'F');
  int R = count(all(all_maze), 'R');
  int L = count(all(all_maze), 'L');

  ll ans = 0;
  try {
    rep (fy, H) rep (fx, W) if (fld[fy][fx] == 'F') {
      rep (ry, H) rep (rx, W) if (fld[ry][rx] == 'R') {
        ans += solve(fx, fy, rx, ry);
      }
    }
  } catch (...) {
    return "";
  }

  ll den = F * R * L;
  ll g = gcd(ans, den);
  char buf[256];
  sprintf(buf, "%lld/%lld", ans / g, den / g);
  return buf;
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
			string maze[]             = { "#########",
  "####F####",
  "##L...R##",
  "####L####",
  "#########" }
;
			string expected__         = "9/2";

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string maze[]             = { "LR",
  "RF" }
;
			string expected__         = "2/1";

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string maze[]             = { "..F.#...",
  "L.F.#..L",
  "..F.#...",
  ".R.#..L.",
  "...#....",
  "..R#.L.." }
;
			string expected__         = "";

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string maze[]             = { ".L..L..L..",
  "..........",
  "..........",
  "..........",
  "........R.",
  "...R......",
  "..........",
  "..........",
  "..........",
  ".......F.." }
;
			string expected__         = "40/3";

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string maze[]             = { "#.#....#...#.#",
  "#...#..#......",
  ".L#...#R#..#F.",
  "#...#......#..",
  "#......#.....#",
  ".R.....F....L.",
  "##..#.......#.",
  "#........##...",
  ".F...##L#..#R#" }
;
			string expected__         = "362/27";

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string maze[]             = { "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLFLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFFLLLLLLLLLLRLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLFLLLLLLLLLLLLLLF",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLF",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFLLL",
  "LLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRRL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLR",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLFFLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "FLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLFLLLLLLLLLRLLLLLLLLLLLLLLLLLLLRLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLFLLLLLLLLLLLLLLLLRLLLLLLLLLRLLLLLLLLLLLLRLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLFLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "FLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL",
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLL" }
;
			string expected__         = "210623/4100";

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string maze[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string maze[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string maze[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
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
