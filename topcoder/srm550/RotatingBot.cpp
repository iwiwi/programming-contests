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

struct RotatingBot {
  int minArea(vector <int> moves);
};



int RotatingBot::minArea(vector <int> moves) {
  set<pair<int, int> > se;

  int x = 0, y = 0;
  se.insert(mp(x, y));

  set<int> kabe[4];
  int minx = 0, maxx = 0;
  int miny = 0, maxy = 0;
  rep (i, moves.size()) {
    const int dx[4] = {1, 0, -1, 0};
    const int dy[4] = {0, -1, 0, 1};

    rep (j, moves[i]) {
      x += dx[i % 4];
      y += dy[i % 4];
      if (se.count(mp(x, y))) return -1;
      se.insert(mp(x, y));
    }

    minx = min(minx, x); maxx = max(maxx, x);
    miny = min(miny, y); maxy = max(maxy, y);

    // terminated
    if (i + 1 == (int)moves.size()) continue;

    // visited
    if (se.count(mp(x + dx[i % 4], y + dy[i % 4]))) continue;

    // wall
    kabe[i % 4].insert(i % 2 == 0 ? x : y);
  }

  rep (d, 4) {
    switch (d) {
      case 0: kabe[d].insert(maxx); break;
      case 1: kabe[d].insert(miny); break;
      case 2: kabe[d].insert(minx); break;
      case 3: kabe[d].insert(maxy); break;
    }
    if (kabe[d].size() >= 2) return -1;
  }

  return (*kabe[0].begin() - *kabe[2].begin() + 1) * (*kabe[3].begin() - *kabe[1].begin() + 1);
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
			int moves[]               = {15};
			int expected__            = 16;

			clock_t start__           = clock();
			int received__            = RotatingBot().minArea(vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int moves[]               = {3,10};
			int expected__            = 44;

			clock_t start__           = clock();
			int received__            = RotatingBot().minArea(vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int moves[]               = {1,1,1,1};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = RotatingBot().minArea(vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int moves[]               = {9,5,11,10,11,4,10};
			int expected__            = 132;

			clock_t start__           = clock();
			int received__            = RotatingBot().minArea(vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int moves[]               = {12,1,27,14,27,12,26,11,25,10,24,9,23,8,22,7,21,6,20,5,19,4,18,3,17,2,16,1,15};
			int expected__            = 420;

			clock_t start__           = clock();
			int received__            = RotatingBot().minArea(vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int moves[]               = {8,6,6,1};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = RotatingBot().minArea(vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int moves[]               = {8,6,6};
			int expected__            = 63;

			clock_t start__           = clock();
			int received__            = RotatingBot().minArea(vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			int moves[]               = {5,4,5,3,3};
			int expected__            = 30;

			clock_t start__           = clock();
			int received__            = RotatingBot().minArea(vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 8: {
			int moves[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = RotatingBot().minArea(vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int moves[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = RotatingBot().minArea(vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			int moves[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = RotatingBot().minArea(vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
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
