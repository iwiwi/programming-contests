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

struct XorLife {
  long long countAliveCells(vector <string> field, int K);
};

typedef long long ll;

const int dx[5] = {0, 1, 0, -1, 0};
const int dy[5] = {0, 0, 1, 0, -1};

vector<string> naive(vector<string> field) {
  int h = field.size() + 2, w = field[0].length() + 2;
  vector<string> res(h, string(w, '.'));

  rep (y, h) rep (x, w) {
    int c = 0;
    rep (d, 5) {
      int tx = x + dx[d];
      int ty = y + dy[d];
      if (tx <= 0 || w - 1 <= tx || ty <= 0 || h - 1 <= ty) continue;
      if (field[ty - 1][tx - 1] == 'o') ++c;
    }
    res[y][x] = c % 2 ? 'o' : '.';
  }
  return res;
}


map<pair<int, vector<string> >, ll> mem;

const int L = 5;

long long XorLife::countAliveCells(vector <string> field, int K) {
  if (K % 2) {
    field = naive(field);
    --K;
  }

  int h = field.size(), w = field[0].length();

  if (K == 0) {
    ll r = 0;
    rep (y, h) rep (x, w) if (field[y][x] == 'o') ++r;
    return r;
  }
  if (h <= L && w <= L && mem.count(mp(K, field))) return mem[mp(K, field)];

  int th = h / 2 + h % 2, tw = w / 2 + w % 2;
  vector<string> next[2][2];
  rep (i, 2) rep (j, 2) next[i][j] = vector<string>(th, string(tw, '.'));
  rep (y, h) rep (x, w) next[y % 2][x % 2][y / 2][x / 2] = field[y][x];

  ll r = 0;
  rep (i, 2) rep (j, 2) r += countAliveCells(next[i][j], K / 2);

  if (h <= L && w <= L) mem[mp(K, field)] = r;
  return r;
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

	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) {
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
			string field[]            = {"oo"
,"o."};
			int K                     = 3;
			long long expected__      = 23;

			clock_t start__           = clock();
			long long received__      = XorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string field[]            = {".."
,".."};
			int K                     = 23;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = XorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string field[]            = {"o"};
			int K                     = 1234567;
			long long expected__      = 11018125;

			clock_t start__           = clock();
			long long received__      = XorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string field[]            = {"o.oo.ooo"
,"o.o.o.oo"
,"ooo.oooo"
,"o.o..o.o"
,"o.o..o.o"
,"o..oooo."
,"..o.o.oo"
,"oo.ooo.o"};
			int K                     = 987654321;
			long long expected__      = 447104494375LL;

			clock_t start__           = clock();
			long long received__      = XorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);

			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
        string field[]            = {"o"};
        int K                     = 50;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = XorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 5: {
        string field[]            = {"o.....o..ooo..o...o.o.......o.........oo.ooo...oo.", "oo..oo.ooo..ooo.....oo.o.....oo.oo..oooooo..o.....", "......oo.oo...o.o...oo.oo..o.oo....o.oooo..o..o...", "o.oo..ooo..o..o.oo..oo.o....ooo...o...ooo.....o.o.", "o.o.......o..ooo.o..ooooo.o.........o.ooo..o..o.o.", ".oo.......o.o.o...o...o......o....o....o.o.o.....o", "o..o.ooooo..oo...oo.o...o.ooo..o.o.o..oooo..oooo..", "o.o.oo..ooo..oo......o.o.ooo.o.ooo...o.oooo.o.....", "..o...oo.....o.o....o...o..ooo...o......o....ooo.o", ".........o.o....oo...o....oo.o....o.....o..ooooooo", ".ooooo.o..o.oo.....oo..o.oo..oooo...o.ooo...o..ooo", ".ooo..o..o...oo.....oo.o.o..oo....oo.o.ooo...oooo.", "..o.oo....ooo.oo.ooo...o.o...o...oooo.ooo.ooo...oo", "oo..o....oooo..o..o....o...o....oo.o....oo.o.oo...", "o..o...o...o.oo...o....o..o.o.o..oo.o.o.o.ooooo.o.", "oo.oo.o.....ooo.o......o..o...oo....o..o...oo.ooo.", "..oo.o.o...oo....oo.o.ooo..oo.........o..oo.oo....", "ooo..oo......oo.o.oo.oo...o....o....o...o.........", "oo...oo...oo..oo......o.o..oo.o.o..o.....ooooo....", "..ooo.....oooo....oooo...o.o...ooo.ooo.o..o.......", ".o..o..o.oo..o...o....o.o...oo......ooo.o...oo.ooo", ".o...oo...oo.o.oo.o..oo.o.oo.oo.o.o.o.o...ooo..o.o", ".o..o.o.o.o..o.o....oo..o..oooo....oo....o.oo.o.o.", "...o.........o..o........o.oooo.......o....o..o...", ".o.oo.ooo....oo....o.oo.o.o.....ooo.oo.o.ooo.....o", ".......o.......ooo...oo.o..o...o.....o...o...o...o", "oo..o.o.o..........ooo.....o...o.o...o.......o.o.o", "..o..oo.oo.....oo..o...ooo..oo..oooo.oo...oooo....", "oo..oo.o...o...oo..o...o..oo.o.....o..o.o.o.oo..o.", "o..o....ooo.o...oo.....oo..oooo...o.o....oo..o.o.o", "oo.o.ooooo....o.ooooo....o....oo..o.oo..o..oo.oo..", "...ooo.o.o..oo..oooo..o..ooo....ooo...ooo.....o.o.", ".ooo......ooooo..o..o.o..oo..o.oo..oooo.oo.o....oo", ".....o..o..ooo.....o....oo.....oooo.o.o...o.......", "ooo...ooo.o.....o.oo....o..oo...oooo....ooo..ooo..", "...oo...o....o.oo..ooo..o..ooo...o.ooo.....oo..ooo", ".ooooo.o.o..o..oo.o.o....o...oo.o...o....ooo...ooo", "o.o.ooooo..o..o........o......ooo..o..o...o.oooo..", "o...o.oo.o...o..oooooooo.o...oo.o.oo..o..o.o..o.o.", "..oooo.ooooo.o.oo...o.o..o....oo.o....o.o.o.o.oo..", "oo....o...oo..........oo.o.o....o.o..o..o..o...o..", ".o....o..o..oo..o...o..o...o.ooo.ooo....oooo....oo", "..o..o...o.oo..o.o...o.o.o.o..oooo...oo.oo.....o..", "o....o....o.o....o.o..oo.o.ooo........o..o.......o", "oo.oo..o.......o.o.o..o.o.o..ooo..o.oo..o..oooo.o.", "o.oo.o...oooo.o..oo...oo...o...o.o...oo..o..o.oooo", ".o.ooo.......o..oo.oo..oooo.ooo..oo.oo.o.ooo..oooo", "o.o.ooo....o...o......o.o....o....oo..o......o.o..", "o..oo..o...o.oo..o...o.o.....oo.....o.o......o..o.", "o....o...o..o...oo...o.o.ooo.oooo...o..o.o......o."};
        int K                     = 989276141;
			long long expected__      = 68743538033450;

			clock_t start__           = clock();
			long long received__      = XorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 6: {
        string field[]            = {".", "o", ".", ".", "o", ".", "o", ".", ".", ".", ".", ".", "o", ".", ".", "o", ".", "o", ".", ".", ".", "o", ".", "o", ".", ".", "o", "o", "o", ".", "o", ".", "o", ".", ".", ".", ".", "o", ".", "o", ".", ".", ".", ".", ".", ".", "o", ".", ".", "."};
			int K                     = 8143;
			long long expected__      = 9114880;

			clock_t start__           = clock();
			long long received__      = XorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
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
    for (int i=1; i<argc; ++i) {
      moj_harness::run_test(atoi(argv[i]));
    }
  }
}
// END CUT HERE
