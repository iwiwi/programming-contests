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

struct Mountains {
  int countPlacements(vector <int> heights, vector <string> visibility);
};

typedef long long ll;
typedef pair<ll, ll> pll;

const int MOD = 1000000009;

int W;

void decode(int h0, const pll &p, int *tmp) {
  int y = h0;
  rep (x, W) {
    y += (p.first  >> x) & 1;
    y -= (p.second >> x) & 1;
    tmp[x] = y;
  }
}

void encode(int &h0, pll &p, int *tmp) {
  int y = h0 = tmp[0];
  p.first = p.second = 0;
  rep (x, W) {
    int ty = tmp[x];
    if (ty > y) p.first  |= 1LL << x;
    if (ty < y) p.second |= 1LL << x;
    y = ty;
  }
}

int N, H;
int hei[60];
bool vis[60][60];

map<pll, int> mem[20][60];

int search(int k, int h0, const pll &p) {
  if (k == -1) return 1;
  pair<iter(mem[k][h0]), bool> pai = mem[k][h0].insert(mp(p, 0));
  if (!pai.second) return pai.first->second;

  iter(mem[k][h0]) ite = pai.first;
  int &res = ite->second;

  int org[60];
  decode(h0, p, org);

  rep (x0, W) {
    int tmp[60];
    rep (x, W) {
      int y = max(0, hei[k] - abs(x - x0));
      if ((y > org[x]) != vis[k][x]) goto dmp;
      tmp[x] = max(y, org[x]);
    }
    {
      int th0;
      pll tp;
      encode(th0, tp, tmp);
      res += search(k - 1, th0, tp);
      if (res > MOD) res -= MOD;
    }
 dmp:;
  }

  return res;
}

int Mountains::countPlacements(vector <int> heights, vector <string> visibility) {
  W = visibility[0].length();
  N = heights.size();
  H = *max_element(all(heights));

  rep (i, N) hei[i] = heights[i];
  rep (i, N) rep (x, W) vis[i][x] = visibility[i][x] == 'X';

  rep (i, N) rep (h0, H + 1) mem[i][h0].clear();
  return search(N - 1, 0, mp(0LL, 0LL));
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
			int heights[]             = {2, 3, 2};
			string visibility[]       = {"------",
 "XXXX--",
 "---XXX"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = Mountains().countPlacements(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])), vector <string>(visibility, visibility + (sizeof visibility / sizeof visibility[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int heights[]             = {4, 3, 4};
			string visibility[]       = {"XXXXX--------",
 "----------XXX",
 "----XXXXXXX--"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = Mountains().countPlacements(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])), vector <string>(visibility, visibility + (sizeof visibility / sizeof visibility[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int heights[]             = {13, 2, 3, 2};
			string visibility[]       = {"XXXXXXXXX",
 "-XXX-----",
 "----XXXXX",
 "-----XXX-"};
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = Mountains().countPlacements(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])), vector <string>(visibility, visibility + (sizeof visibility / sizeof visibility[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int heights[]             = {8, 2, 9, 3, 10};
			string visibility[]       = {"X------",
 "-------",
 "------X",
 "-------",
 "XXXXXXX"};
			int expected__            = 98;

			clock_t start__           = clock();
			int received__            = Mountains().countPlacements(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])), vector <string>(visibility, visibility + (sizeof visibility / sizeof visibility[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int heights[]             = {20, 20, 20, 20, 20, 20, 45, 50, 49, 50};
			string visibility[]       = {"-------------------",
 "-------------------",
 "-------------------",
 "-------------------",
 "-------------------",
 "-------------------",
 "-------------------",
 "------------XXXXXXX",
 "XXXXXXX------------",
 "XXXXXXXXXXXXXXXXXXX"}
;
			int expected__            = 973726691;

			clock_t start__           = clock();
			int received__            = Mountains().countPlacements(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])), vector <string>(visibility, visibility + (sizeof visibility / sizeof visibility[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int heights[]             = ;
			string visibility[]       = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Mountains().countPlacements(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])), vector <string>(visibility, visibility + (sizeof visibility / sizeof visibility[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int heights[]             = ;
			string visibility[]       = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Mountains().countPlacements(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])), vector <string>(visibility, visibility + (sizeof visibility / sizeof visibility[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int heights[]             = ;
			string visibility[]       = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Mountains().countPlacements(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])), vector <string>(visibility, visibility + (sizeof visibility / sizeof visibility[0])));
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
