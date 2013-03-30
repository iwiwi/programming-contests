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

struct DirectionBoard {
  int getMinimum(vector <string> board);
};

const int MAX_V = 1010;
struct e_t { int to, init, cap, cst, rev; };
int V;

vector<e_t> adj[MAX_V];
double h[MAX_V];
int ex[MAX_V], iter[MAX_V];;
bool visit[MAX_V];

void add_edge(int i, int j, int cap, int cst) {
  adj[i].push_back((e_t){j, cap, cap, +cst, adj[j].size()});
  adj[j].push_back((e_t){i,   0,   0, -cst, adj[i].size() - 1});
}

void dfs(int v) {
  visit[v] = true;
  rep (i, adj[v].size()) {
    e_t &e = adj[v][i];
    if (e.cap > 0 && !visit[e.to] && e.cst + h[v] - h[e.to] < 0) dfs(e.to);
  }
}

int dfs(int v, int f) {
  if (ex[v] < 0) {
    int d = min(f, -ex[v]);
    ex[v] += d;
    return d;
  }
  for (; iter[v] < (int)adj[v].size(); ++iter[v]) {
    e_t &e = adj[v][iter[v]];
    if (e.cap > 0 && e.cst + h[v] - h[e.to] < 0) {
      int d = dfs(e.to, min(f, e.cap));
      if (d > 0) {
        e.cap -= d;
        adj[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int min_cost_circulation() {
  double eps = 0;
  rep (v, V) rep (i, adj[v].size()) if (adj[v][i].cap > 0) eps = max(eps, -(double)adj[v][i].cst);
  while (eps * (V + 1) > 1) {
    eps /= 4;
    rep (v, V) rep (i, adj[v].size()) {
      e_t &e = adj[v][i];
      if (e.cap > 0 && e.cst + h[v] - h[e.to] < 0) {
        ex[e.to] += e.cap;
        ex[v] -= e.cap;
        adj[e.to][e.rev].cap += e.cap;
        e.cap = 0;
      }
    }
    for (;;) {
      rep (v, V) visit[v] = false;
      rep (v, V) if (ex[v] > 0) dfs(v);
      rep (v, V) if (visit[v]) h[v] -= eps;
      rep (v, V) iter[v] = 0;
      bool ok = true;
      rep (v, V) {
        for (int f; ex[v] > 0 && (f = dfs(v, ex[v])) > 0; ) ex[v] -= f;
        if (ex[v] > 0) ok = false;
      }
      if (ok) break;
    }
  }
  int res = 0;
  rep (v, V) rep (i, adj[v].size()) {
    e_t &e = adj[v][i];
    if (e.init > e.cap) res += e.cst * (e.init - e.cap);
  }
  return res;
}

int H, W;
int vid(int x, int y, bool i) {
  x = (x + W) % W;
  y = (y + H) % H;
  return (x * H + y) * 2 + i;
}

int DirectionBoard::getMinimum(vector <string> board) {
  H = board.size();
  W = board[0].length();

  const int A = 1000;

  V = W * H * 2;
  rep (v, V) adj[v].clear();

  rep (y, H) rep (x, W) {
    add_edge(vid(x, y, 0), vid(x, y, 1), 1, -A);

    const int dx[4] = {1, 0, -1, 0};
    const int dy[4] = {0, 1, 0, -1};
    const char *dc = "RDLU";

    rep (d, 4) {
      add_edge(vid(x, y, 1), vid(x + dx[d], y + dy[d], 0), 1, dc[d] == board[y][x] ? 0 : 1);
    }
  }

  int c = min_cost_circulation();
  return c + A * W * H;;
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
			string board[]            = {"RRRD",
 "URDD",
 "UULD",
 "ULLL"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"RRRD",
 "URLL",
 "LRRR"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"RRD",
 "URD",
 "ULL"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"ULRLRD",
 "UDDLRR"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"UDLRLDLD",
 "DLDLLDLR",
 "LLLLLDLD",
 "UUURRRDD"};
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {"UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUUDDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "RRRDLDURDURUDDR"}
;
			int expected__            = 73;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
