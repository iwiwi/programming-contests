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

struct MagicalHats {
  int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses);
};

const int INF = 987654321;

int W, H, C, G;
int N;

vector<int> row[20], col[20];

int hat[20];
int mem[1594323 + 100];

int search() {
  int e = 0;
  rep (i, N) e = e * 3 + hat[i];
  if (mem[e] != -1) return mem[e];

  int opened = 0;
  rep (k, N) if (hat[k] != 0) ++opened;

  if (opened == N) {
    // Magician's verification
    {
      int c = 0;
      rep (i, N) c += (hat[i] == 2 ? 1 : 0);
      if (c != C) return mem[e] = INF;
    }
    rep (y, H) {
      int c = 0;
      rep (i, row[y].size()) c += 1 + (hat[row[y][i]] == 2 ? 1 : 0);
      if (c % 2 != 0) return mem[e] = INF;
    }
    rep (x, W) {
      int c = 0;
      rep (i, col[x].size()) c += 1 + (hat[col[x][i]] == 2 ? 1 : 0);
      if (c % 2 != 0) return mem[e] = INF;
    }
    return mem[e] = 0;
  }
  else {
    bool reveal = opened < G;
    int res = 0;
    rep (k, N) if (hat[k] == 0) {  // Player
      int t1, t2;
      {
        hat[k] = 1;
        t1 = search();
        hat[k] = 0;
      }
      {
        hat[k] = 2;
        t2 = (reveal ? 1 : 0) + search();
        hat[k] = 0;
      }
      int tmp = min(t1, t2);  // Magician
      res = max(res, tmp);  // Player
    }
    return mem[e] = res;
  }
}

int MagicalHats::findMaximumReward(vector <string> board, vector <int> coins, int numGuesses) {
  H = board.size();
  W = board[0].length();
  C = coins.size();
  G = numGuesses;
  N = 0;

  rep (y, H) row[y].clear();
  rep (x, W) col[x].clear();

  rep (y, H) rep (x, W) {
    if (board[y][x] == 'H') {
      int myid = N++;
      row[y].pb(myid);
      col[x].pb(myid);
    }
  }

  memset(mem, -1, sizeof(mem));
  memset(hat, 0, sizeof(hat));
  int res = search();

  printf("N = %d, res = %d\n", N, res);

  if (res >= INF) return -1;
  sort(all(coins));
  return accumulate(coins.begin(), coins.begin() + res, 0);
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
			string board[]            = {"H"};
			int coins[]               = {1};
			int numGuesses            = 1;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"HHH",
 "H.H",
 "HH."};
			int coins[]               = {9};
			int numGuesses            = 1;
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"HH",
 "HH"};
			int coins[]               = {1,2,3,4};
			int numGuesses            = 3;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"HHH",
 "HHH",
 "H.H"};
			int coins[]               = {13,13,13,13};
			int numGuesses            = 2;
			int expected__            = 13;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"HHH",
 "HHH",
 "H.H"};
			int coins[]               = {13,13,13,13};
			int numGuesses            = 3;
			int expected__            = 26;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {"H.H.",
 ".H.H",
 "H.H."};
			int coins[]               = {17};
			int numGuesses            = 6;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string board[]            = {"HHH",
 "H.H",
 "HHH",
 "H.H",
 "HHH"};
			int coins[]               = {33,337,1007,2403,5601,6003,9999};
			int numGuesses            = 5;
			int expected__            = 1377;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			string board[]            = {".............",
 ".............",
 ".............",
 ".............",
 ".............",
 ".............",
 ".....H.H.....",
 "......H......",
 ".....H.H.....",
 ".............",
 ".............",
 ".............",
 "............."};
			int coins[]               = {22};
			int numGuesses            = 3;
			int expected__            = 22;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 8: {
			string board[]            = ;
			int coins[]               = ;
			int numGuesses            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string board[]            = ;
			int coins[]               = ;
			int numGuesses            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			string board[]            = ;
			int coins[]               = ;
			int numGuesses            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
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
