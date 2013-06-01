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

struct WallGameDiv1 {
  int play(vector <string> costs);
};

int W, H, C[60][60];
int dp[60][60], sum[60][60];
int eel[60][60], rab[60][60];  // [a][b] -> [a, b) or (b, a], token is on |a|

inline int move(int y, int x0, int x1) {
  if (x0 < x1) return sum[y][x1 + 1] - sum[y][x0 + 1];
  else         return sum[y][x0    ] - sum[y][x1    ];
}

void do_row(int y) {
  memset(rab, 0, sizeof(rab));

  rep (iter, 60) {
    // Eel's turn
    for (int x0 = 1; x0 <= W; ++x0) {
      for (int x1 = 0; x1 <= W + 1; ++x1) {
        int t = dp[y + 1][x0];  // Fall
        if (max(x1, x0) - min(x1, x0) < W) {  // Wall
          t = max(t, rab[x0][x1]);
        }
        eel[x0][x1] = t;
      }
    }

    // Rabbit's turn
    for (int x0 = 1; x0 <= W; ++x0) {
      for (int x1 = 0; x1 <= W + 1; ++x1) {
        int t = INT_MAX;
        int tx0 = x0 < x1 ? x0 - 1 : x0 + 1;
        if (1 <= tx0 && tx0 <= W) t = min(t, eel[tx0][x1] + move(y, x0, tx0));
        if (1 <=  x1 &&  x1 <= W) t = min(t, eel[x1][tx0] + move(y, x0,  x1));
        rab[x0][x1] = t;
      }
    }
  }
}

int WallGameDiv1::play(vector <string> costs) {
  W = costs[0].length();
  H = costs.size();

  for (int y = 1; y <= H; ++y) {
    sum[y][1] = 0;
    for (int x = 1; x <= W; ++x) {
      C[y][x] = costs[y - 1][x - 1] - '0';
      sum[y][x + 1] = sum[y][x] + C[y][x];
    }
  }

  // Last row
  for (int x = 1; x <= W; ++x) dp[H][x] = C[H][x];

  // Normal rows
  for (int y = H - 1; y >= 1; --y) {
    do_row(y);
    for (int x = 1; x <= W; ++x) {
      dp[y][x] = C[y][x] + min(eel[x][x + 1], eel[x][x - 1]);
    }
  }

  return *min_element(&dp[1][1], &dp[1][W] + 1);
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
			string costs[]            = {"12"
,"34"};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string costs[]            = {"99999"
,"99999"
,"99999"};
			int expected__            = 99;

			clock_t start__           = clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string costs[]            = {"11111"
,"90005"};
			int expected__            = 10;

			clock_t start__           = clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string costs[]            = {"4417231387449337370319219832088987579792"
,"3117295688208899006196193430472892512797"
,"0835796222361526836944954410684516919758"
,"1988200069973565052900745230547016216225"
,"8080511471118865780390486996601082102418"
,"4229084185957675819725844582167613108400"
,"9068653877952162764545674979144308771754"
,"8551565425951612499712254182109991511690"
,"7090525592007482152807163656647658543093"
,"9198968742256995592729889137556032960142"
,"2071864379877766468141740053503050313101"
,"1055375249261868472993219156394129253481"
,"2461178270502857106406495509025426298874"
,"8216781259733537757203421037984512664825"
,"4693452554407216935375049784445568498482"
,"2709693439640250842244170297203200674391"
,"5122217695676372684217182241705137947908"
,"6668814191410691246849638388008228444294"
,"4952122070212780440963814752538149378639"
,"9827737761436134120332969866554332504400"
,"3412406588339828249986707470540386748886"
,"7521506848088506994554600408372456405830"
,"1916926179183007872881163173153907665999"
,"6636166791472761992310264951474925339024"
,"6679667717747231380196787943691121008076"
,"3218993234115685151069259138068533004433"
,"4920152552986426962081492913852060211795"
,"0365186235986445521382132973036266396894"
,"3205351414936828189305188614651974318855"
,"3144278971529524658788277656125598825426"
,"5525287537572356662391582052968411726245"
,"2130137226726919525622574701068062252930"
,"2369996694245544770519574837226971226841"
,"6806769058165410189286521891570936341547"
,"0448109211631660241710734664066810078242"
,"4622919135804954122810530631429501069659"
,"0235247446548732490429856705369583140671"
,"2193399741215975228987754171460722199304"
,"1203037020703833716225328076959743850915"
,"5419885193880826109484912489603262199432"};
			int expected__            = 7366;

			clock_t start__           = clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string costs[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string costs[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string costs[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
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
