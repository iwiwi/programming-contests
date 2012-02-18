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

struct MagicBoard {
  string ableToUnlock(vector <string> board);
};



const int MAX_N = 1000000;

int par[MAX_N], rank[MAX_N];

void init(int n) {
  for (int i = 0; i < n; i++) {
    par[i] = i;
    rank[i] = 0;
  }
}

int root(int x) {
  return par[x] == x ? x : par[x] = root(par[x]);
}

void unite(int x, int y) {
  x = root(x);
  y = root(y);
  if (x == y) return;

  if (rank[x] < rank[y]) {
    par[x] = y;
  } else {
    par[y] = x;
    if (rank[x] == rank[y]) rank[x]++;
  }
}

bool find(int x, int y) {
  return root(x) == root(y);
}




int V;
vector<int> adj[110];

string MagicBoard::ableToUnlock(vector <string> board) {
  int H = board.size();
  int W = board[0].size();
  V = W + H;
  rep (i, V) adj[i].clear();

  rep (y, H) rep (x, W) {
    if (board[y][x] == '#') {
      int vr = y;
      int vc = H + x;
      adj[vr].pb(vc);
      adj[vc].pb(vr);
    }
  }

  init(V);
  rep (v, V) rep (i, adj[v].size()) unite(v, adj[v][i]);
  rep (v, V) rep (w, V) if (adj[v].size() && adj[w].size() && find(v, w) == false) {
    puts("disconnected\n");
    return "NO";
  }

  int nor = 0, noc = 0;
  rep (y, H) if (adj[    y].size() % 2) nor++;
  rep (x, W) if (adj[H + x].size() % 2) noc++;

  if (nor + noc == 0) {
    return "YES";
  } if (nor + noc == 2) {
    if (noc == 0) {
      puts("no starting point");
      return "NO";
    } else {
      return "YES";
    }
  } else {
    puts("too many odd degrees");
    return "NO";
  }

  return "YES";
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
			string board[]            = {"##",
 ".#"};
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = MagicBoard().ableToUnlock(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"#.",
 ".#"};
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = MagicBoard().ableToUnlock(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"##",
 "##",
 "##"};
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = MagicBoard().ableToUnlock(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"###",
 "###",
 "###"};
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = MagicBoard().ableToUnlock(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"###",
 "..#",
 "###",
 "#..",
 "###"};
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = MagicBoard().ableToUnlock(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {"................",
 ".######..######.",
 ".######..######.",
 ".##......##..##.",
 ".##......##..##.",
 ".######..######.",
 ".######..######.",
 ".....##..##..##.",
 ".....##..##..##.",
 ".######..######.",
 ".######..######.",
 "................"};
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = MagicBoard().ableToUnlock(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string board[]            = {"#"};
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = MagicBoard().ableToUnlock(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string board[]            = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = MagicBoard().ableToUnlock(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string board[]            = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = MagicBoard().ableToUnlock(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string board[]            = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = MagicBoard().ableToUnlock(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
