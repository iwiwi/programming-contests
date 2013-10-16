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
#include <tuple>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define eb emplace_back
#define mp make_pair

class KeyDungeonDiv1 {
 public:
  int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys);
};

int dp[1 << 12][150];

int KeyDungeonDiv1::maxKeys(vector <int> doorR, vector <int> doorG,
                            vector <int> roomR, vector <int> roomG, vector <int> roomW,
                            vector <int> keys) {
  int N = doorR.size();
  int R = keys[0] + accumulate(all(roomR), 0);

  memset(dp, -1, sizeof(dp));
  dp[0][keys[0]] = keys[2];

  int ans = 0;
  rep (b, 1 << N) rep (r, R + 1) {
    int w = dp[b][r];
    if (w < 0) continue;

    // Restore the current number of keys
    int tr = keys[0], tg = keys[1], tw = keys[2];
    rep (i, N) if (b & (1 << i)) {
      tr = tr - doorR[i] + roomR[i];
      tg = tg - doorG[i] + roomG[i];
      tw = tw            + roomW[i];
    }
    int g = tg + ((tw - w) - (r - tr));
    ans = max(ans, r + g + w);

    // Open another door
    rep (i, N) if (!(b & (1 << i))) {
      int tb = b | (1 << i);

      // Pay for opening the door
      int dr = min(r, doorR[i]), tr = r - dr;
      int dg = min(g, doorG[i]), tg = g - dg;
      int tw = w - (doorR[i] - dr) - (doorG[i] - dg);
      if (tw < 0) continue;

      // Gain from the chumber
      tr += roomR[i];
      tg += roomG[i];
      tw += roomW[i];
      dp[tb][tr] = max(dp[tb][tr], tw);
    }
  }

  return ans;
}















// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
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
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}

	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) {
		std::cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;

		if (verdict == "FAILED") {
			std::cerr << "    Expected: " << expected << std::endl;
			std::cerr << "    Received: " << received << std::endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int doorR[]               = {1, 2, 3};
			int doorG[]               = {0, 4, 9};
			int roomR[]               = {0, 0, 10};
			int roomG[]               = {0, 8, 9};
			int roomW[]               = {1, 0, 8};
			int keys[]                = {3, 1, 2};
			int expected__            = 8;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int doorR[]               = {1, 1, 1, 2};
			int doorG[]               = {0, 2, 3, 1};
			int roomR[]               = {2, 1, 0, 4};
			int roomG[]               = {1, 3, 3, 1};
			int roomW[]               = {1, 0, 2, 1};
			int keys[]                = {0, 4, 0};
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int doorR[]               = {2, 0, 4};
			int doorG[]               = {3, 0, 4};
			int roomR[]               = {0, 0, 9};
			int roomG[]               = {0, 0, 9};
			int roomW[]               = {8, 5, 9};
			int keys[]                = {0, 0, 0};
			int expected__            = 27;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int doorR[]               = {5, 3, 0, 0};
			int doorG[]               = {0, 1, 2, 1};
			int roomR[]               = {0, 9, 2, 4};
			int roomG[]               = {2, 9, 2, 0};
			int roomW[]               = {0, 9, 1, 1};
			int keys[]                = {1, 1, 0};
			int expected__            = 32;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int doorR[]               = {9,5,10,8,4,3,0,8,4,1,3,9};
			int doorG[]               = {9,10,0,8,9,4,3,8,1,8,10,4};
			int roomR[]               = {1,2,0,2,3,3,5,3,1,3,0,5};
			int roomG[]               = {5,2,5,0,5,2,3,4,0,0,5,2};
			int roomW[]               = {1,5,1,2,0,4,4,0,3,3,1,3};
			int keys[]                = {5,0,1};
			int expected__            = 16;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int doorR[]               = ;
			int doorG[]               = ;
			int roomR[]               = ;
			int roomG[]               = ;
			int roomW[]               = ;
			int keys[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int doorR[]               = ;
			int doorG[]               = ;
			int roomR[]               = ;
			int roomG[]               = ;
			int roomW[]               = ;
			int keys[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int doorR[]               = ;
			int doorG[]               = ;
			int roomR[]               = ;
			int roomG[]               = ;
			int roomW[]               = ;
			int keys[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
