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

const int MAX_V = 20010;

struct e_t { int to, cap, rev; };

int V, S, T;
vector<e_t> adj[MAX_V];

int lev[MAX_V], done[MAX_V];

void add_edge(int i, int j, int c) {
  adj[i].push_back((e_t){j, c, adj[j].size()});
  adj[j].push_back((e_t){i, 0, adj[i].size() - 1});
}

bool levelize() {
  memset(lev, -1, sizeof(lev));
  queue<int> que;
  lev[S] = 0;
  que.push(S);
  while (!que.empty()) {
    int v = que.front(); que.pop();
    rep (i, adj[v].size()) {
      e_t &e = adj[v][i];
      if (!e.cap || lev[e.to] != -1) continue;
      lev[e.to] = lev[v] + 1;
      que.push(e.to);
    }
  }
  return lev[T] != -1;
}

int augment(int v, int f) {
  if (v == T || !f) return f;
  for (; done[v] < (int)adj[v].size(); done[v]++) {
    e_t &e = adj[v][done[v]];
    if (lev[e.to] <= lev[v]) continue;
    int t = augment(e.to, min(f, e.cap));
    if (t > 0) {
      e.cap -= t;
      adj[e.to][e.rev].cap += t;
      return t;
    }
  }
  return 0;
}

int max_flow() {
  int f = 0, t;
  while (levelize()) {
    memset(done, 0, sizeof(done));
    while (t = augment(S, INT_MAX)) f += t;
  }
  return f;
}

struct BoardPainting {
  int minimalSteps(vector <string> target);
};

const int INF = 1000;
int W, H, id[60][60];

int vid(int x, int y, int i) {
  return (y * W + x) * 2 + i;
}

int BoardPainting::minimalSteps(vector <string> F) {
  H = F.size();
  W = F[0].length();

  int N = H * W;
  V = N * 2 + 2;
  S = N * 2;
  T = N * 2 + 1;
  rep (v, V) adj[v].clear();

  rep (y, H) rep (x, W) if (F[y][x] == '#') {
    // Start
    add_edge(vid(x, y, 0), vid(x, y, 1), 1);

    // Left
    if (x == 0 || F[y][x - 1] == '.') {
      add_edge(S, vid(x, y, 0), INF);
    } else {
      add_edge(vid(x - 1, y, 1), vid(x, y, 0), INF);
    }

    // Up
    if (y == 0 || F[y - 1][x] == '.') {
      add_edge(vid(x, y, 1), T, INF);
    } else {
      add_edge(vid(x, y, 1), vid(x, y - 1, 0), INF);
    }

    // Right & Bottom
    if (y + 1 < H && F[y + 1][x] == '#' &&
        x + 1 < W && F[y][x + 1] == '#') {
      add_edge(vid(x, y + 1, 1), vid(x + 1, y, 0), INF);
    }
  }

  return max_flow();
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
			string target[]           = {"#####"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string target[]           = {"#####",
 ".....",
 "#####",
 ".....",
 "#####"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string target[]           = {"..#..",
 "..#..",
 "#####",
 "..#..",
 "..#.."};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string target[]           = {"#####",
 "..#..",
 "#####",
 "..#..",
 "#####"};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string target[]           = {".#.#.",
 "#####",
 ".#.#.",
 "#####",
 ".#.#."};
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string target[]           = {".##.####.####.#########.##..",
 "##.#.####################.##",
 ".##.###.##.###.###.###.###..",
 "#..###..#########..###.##.##",
 "####..#######.#.#####.######",
 "##.######.#..#.#############",
 "##.######.###########.######",
 "#######.#######.#..###.#.###",
 "#####..#######.#####.#.###.#",
 "#..#################.#.####.",
 "##.######..#.#####.######.##",
 "..#.#############.#.##....#.",
 "....##..##..#.#####.#.###.##",
 "##.#########...#..#.#.######",
 "##.#..###########..#..####.#",
 "#.####.###.########.########",
 "#####.#########.##.##.######",
 ".##.####..###.###...######.#"};
			int expected__            = 88;

			clock_t start__           = clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string target[]           = {"...................."};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string target[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string target[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string target[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
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
