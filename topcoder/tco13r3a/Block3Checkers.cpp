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

struct Block3Checkers {
  int blockThem(vector <string> board);
};

int W, H;
char B[50][50];

vector<vector<int> > dis;

void bfs(int sx, int sy) {
  deque<pair<pair<int, int>, int> > que;
  dis.clear();
  dis = vector<vector<int> >(H, vector<int>(W, INT_MAX));

  que.pb(mp(mp(sx, sy), 0));
  dis[sy][sx] = 0;
  while (!que.empty()) {
    int x = que.front().first.first;
    int y = que.front().first.second;
    int d = que.front().second;
    que.pop_front();
    if (d > dis[y][x]) continue;

    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        int tx = x + dx;
        int ty = y + dy;
        if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
        if (B[ty][tx] == 'A' || B[ty][tx] == 'Z') continue;

        int td = d + (B[y][x] == 'N' ? 0 : 1);
        if (td < dis[ty][tx]) {
          if (td == d) que.push_front(mp(mp(tx, ty), td));
          else         que.push_back (mp(mp(tx, ty), td));
          dis[ty][tx] = td;
        }
      }
    }
  }
}

bool is_boundary(int x, int y) {
  return y == 0 || y == H - 1 || x == 0 || x == W - 1;
}

int Block3Checkers::blockThem(vector <string> board) {
  memset(B, 'N', sizeof(B));
  rep (y, board.size()) rep (x, board[0].length()) {
    B[y + 1][x + 1] = board[y][x];
  }
  H = board.size() + 2;
  W = board[0].size() + 2;
  B[0][0] = B[0][W - 1] = B[H - 1][0] = B[H - 1][W - 1] = 'Z';

  {
    const int dx[4] = {1, 0, -1, 0};
    const int dy[4] = {0, 1, 0, -1};
    rep (y, H) rep (x, W) if (B[y][x] == 'A') {
      rep (d, 4) {
        int tx = x + dx[d];
        int ty = y + dy[d];
        if (B[ty][tx] == 'A') return 100;  // Impossible
        if (is_boundary(tx, ty) && B[ty][tx] == 'N') B[ty][tx] = 'Z';
      }
    }
  }

  rep (y, H) { rep (x, W) printf("%c", B[y][x]); puts(""); }

  vector<vector<vector<int> > > ds;
  rep (y, H) rep (x, W) {
    if (!(y == 0 || y == H - 1 || x == 0 || x == W - 1)) continue;
    if (B[y][x] != 'N') continue;

    rep (i, ds.size()) if (ds[i][y][x] == 0) goto done;

    printf("%d %d\n", x, y);
    bfs(x, y);
    ds.pb(dis);

    // rep (ty, H) rep (tx, W) printf("%d ", dis[ty][tx]); puts("");
 done:;
  }

  printf("ds: %d\n", (int)ds.size());
  // assert(ds.size() <= 3);

  int ans = INT_MAX;
  rep (y, H) rep (x, W) {
    int tmp = (B[y][x] == 'N' ? 0 : 1);
    rep (i, ds.size()) {
      int d = ds[i][y][x];
      if (d == INT_MAX) goto dmp;
      tmp += d;
    }
    if (tmp < ans) {
      ans = tmp;
      printf("ans %d %d: %d\n", x, y, tmp);
    }
 dmp:;
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
			string board[]            = {"A......A",
 "...N.N..",
 ".NNN.NN.",
 "NNNN.N.N",
 "N.NN.NNN",
 ".NNN.NNN",
 "NNN...NN",
 ".NN.A..N"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = Block3Checkers().blockThem(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {".....A",
 "......",
 "......",
 "NNNNNN",
 "A.....",
 "A....."};
			int expected__            = 100;

			clock_t start__           = clock();
			int received__            = Block3Checkers().blockThem(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"A.N",
 "NNA",
 "AN."};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = Block3Checkers().blockThem(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"......NA",
 ".NNNN.N.",
 ".N......",
 "....NNNN",
 "........",
 ".N..NNN.",
 "......N.",
 "A.N....A"}
;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = Block3Checkers().blockThem(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Block3Checkers().blockThem(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Block3Checkers().blockThem(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Block3Checkers().blockThem(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
  const int N = 20;
  rep (iter, 100) {
    vector<string> board(N, string(N, '.'));
    board[0][0] = 'A';
    board[N / 2][0] = 'A';
    board[N - 1][N / 2] = 'A';
    rep (i, N) rep (j, N) if (board[i][j] != 'A') board[i][j] = "....N"[rand() % 5];
    printf("ans = %d\n", Block3Checkers().blockThem(board));
  }

	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
