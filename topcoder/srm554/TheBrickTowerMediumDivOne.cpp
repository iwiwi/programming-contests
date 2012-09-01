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

struct TheBrickTowerMediumDivOne {
  vector <int> find(vector <int> heights);
};


vector <int> TheBrickTowerMediumDivOne::find(vector <int> heights) {

  int N = heights.size();

  vector<bool> usd(N);
  vector<int> ans(N, -1);

  int i = 0;

  int l = INT_MAX;
  for (; i < N; ++i) {
    rep (j, N) {
      if (!usd[j] && heights[j] <= l) {
        ans[i] = j;
        usd[j] = true;
        l = heights[j];
        goto done;
      }
    }
    break;
 done:;
  }

  for (; i < N; ++i) {
    int mih = INT_MAX, mij = -1;
    rep (j, N) {
      if (!usd[j] && heights[j] < mih) {
        mih = heights[j];
        mij = j;
      }
    }
    assert(mij != -1);
    ans[i] = mij;
    usd[mij] = true;
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

	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, clock_t elapsed) {
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
			int heights[]             = {4, 7, 5};
			int expected__[]          = {0, 2, 1 };

			clock_t start__           = clock();
			vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int heights[]             = {4, 4, 4, 4, 4, 4, 4};
			int expected__[]          = {0, 1, 2, 3, 4, 5, 6 };

			clock_t start__           = clock();
			vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int heights[]             = {2, 3, 3, 2};
			int expected__[]          = {0, 3, 1, 2 };

			clock_t start__           = clock();
			vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int heights[]             = {13, 32, 38, 25, 43, 47, 6};
			int expected__[]          = {0, 6, 3, 1, 2, 4, 5 };

			clock_t start__           = clock();
			vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int heights[]             = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 5: {
			int heights[]             = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			int heights[]             = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}

void show(vector<int> v, vector<int> h) {
  rep (i, v.size()) printf("%d(%d) ", v[i], h[v[i]]);
  puts("");
}

int main(int argc, char *argv[]) {
  for (;;) {
    int N = 10;
    vector<int> v(N);
    rep (i, N) v[i] = 1 + rand() % 47;

    rep (i, N) printf("%d,", v[i]); puts("");
    show(TheBrickTowerMediumDivOne().find(v), v);
    show(smylic(v), v);
    assert(TheBrickTowerMediumDivOne().find(v) == smylic(v));
  }

	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
