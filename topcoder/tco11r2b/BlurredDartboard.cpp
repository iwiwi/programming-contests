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

struct BlurredDartboard {
  int minThrows(vector <int> points, int P);
};

int BlurredDartboard::minThrows(vector <int> points, int P) {
  int N = points.size();
  vector<bool> b(N + 1);
  rep (i, N) b[points[i]] = true;

  int pmax = *max_element(all(points));

  vector<int> zs;
  for (int x = 1; x <= N; ++x) if (!b[x]) zs.pb(x);
  sort(all(zs));
  int znum = zs.size();
  int zsum = accumulate(all(zs), 0);

  if (pmax * znum >= zsum) {
    return P / pmax + (P % pmax ? 1 : 0);
  } else {
    int base = (P / zsum) * znum;
    int ans = INT_MAX;
    P %= zsum;

    for (int i = 0; i <= znum; ++i) {
      int tp = P - accumulate(zs.begin(), zs.begin() + i, 0);

      int c = i;
      if (tp > 0) {
        if (pmax == 0) continue;
        c += P / pmax + (P % pmax ? 1 : 0);
      }
      ans = min(ans, base + c);
    }

    return ans;
  }
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
			int points[]              = {0, 3, 4, 0, 0};
			int P                     = 8;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int points[]              = {0, 0, 0, 0, 0};
			int P                     = 15;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int points[]              = {4, 7, 8, 1, 3, 2, 6, 5};
			int P                     = 2012;
			int expected__            = 252;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int points[]              = {0, 0, 5, 0, 0, 0, 1, 3, 0, 0};
			int P                     = 2012;
			int expected__            = 307;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int points[]              = {0, 2, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 6, 0, 0, 0, 4, 0, 0, 0};
			int P                     = 1000000000;
			int expected__            = 84656087;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
        int points[]              = {0, 0, 0, 1, 2, 3};
        int P                     = 19;
        int expected__            = 4;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int points[]              = ;
			int P                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int points[]              = ;
			int P                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
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
