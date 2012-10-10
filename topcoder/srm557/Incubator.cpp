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

#define F first
#define S second

struct Incubator {
  int maxMagicalGirls(vector <string> love);
};

const int MAX_V = 510;

int L, R;
bool adj[MAX_V][MAX_V];

int mat[MAX_V];
bool vis[MAX_V];

int augment(int r) {
  rep (l, L) if (adj[l][r] && !vis[l]) {
    vis[l] = true;
    if (mat[l] < 0 || augment(mat[l])) {
      mat[l] = r;
      return 1;
    }
  }
  return 0;
}

int bipartite_matching() {
  int res = 0;
  memset(mat, -1, sizeof(mat));
  rep (r, R) {
    memset(vis, 0, sizeof(vis));
    res += augment(r);
  }
  return res;
}

int Incubator::maxMagicalGirls(vector <string> love) {
  int N = love.size();
  rep (i, N) rep (j, N) adj[i][j] = love[i][j] == 'Y';
  rep (k, N) rep (i, N) rep (j, N) adj[i][j] |= adj[i][k] & adj[k][j];

  L = R = N;
  return N - bipartite_matching();
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
			string love[]             = {"NY","NN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls(vector <string>(love, love + (sizeof love / sizeof love[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string love[]             = {"NYN", "NNY", "NNN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls(vector <string>(love, love + (sizeof love / sizeof love[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string love[]             = {"NNYNN","NNYNN","NNNYY","NNNNN","NNNNN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls(vector <string>(love, love + (sizeof love / sizeof love[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string love[]             = {"NNNNN","NYNNN","NYNYN","YNYNN","NNNNN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls(vector <string>(love, love + (sizeof love / sizeof love[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string love[]             = {"NNNNN","NNNNN","NNNNN","NNNNN","NNNNN"};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls(vector <string>(love, love + (sizeof love / sizeof love[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string love[]             = {"NNYNNNNN","NNNYNNNN","NNNNYNNN","NNYNNNNN","NNNNNYYN","NNNYNNNY","NNNNNNNN","NNNNNNNN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls(vector <string>(love, love + (sizeof love / sizeof love[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string love[]             = {"Y"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls(vector <string>(love, love + (sizeof love / sizeof love[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 7: {
			string love[]             = {"NNNNNYNNNNNNNYYNYNNNNNYNNNNNNNYNNYNNNYNNYYNNNNN", "NNNNNNNNNNYNYNNNNNNNNYYNNNYYNNYNNNNNNNNNYNYNNNN", "NNNNYNNNNNNNNNNNNNNNNYNNYYNNNNNNNNNNNNNNNNNYNNN", "NNNYNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNYNYNNNN", "NNNNYNNYNNNNYNYNNNNNNNNNNNNYNNNNNYNNYYNNNNYNNNY", "NNNNNNNNNNNNNYNNNNNNNNNNNYNNNNNNNYNNYNNNNNNNNNN", "NNNYNNNNNNNNNNNNNNNNNNNNYNNNNNNYNNNNYNNNNNYYNYN", "NNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNN", "NNNNNNYNNNNNYNNNNNNNNYNNNNYNNNNNNYNNNNYNYNNNNYN", "NNYNNNNNNNYNNYNNNYNNNNYNNNNNNYNNNNNNYNNNNNNNNYN", "NNNNNNNNNNNNNNNNNNNNYNYNNYNNNNNNNNNNNNNNNYYNNNN", "YNYNNYYNYYNNNNYNNNNNNNYNYNNYNNNNNNNNNNNNNNNNNNN", "NNNNNYYNNNNYNNNNNNNYNNYNNNYNNNYNNYYNNYNNNNNNNNN", "YNNYNNYNNNNNYYNNNNNNNNYNNYNNNNNYNNNNNNNYNYNYNNN", "NNYNYYNNNNNNYNNNNNNYNNNYYNYNNNNNNNYNNNNNNYNNNNN", "NNYNNNYYYNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNN", "NNNNNNNNNNNYNNNNNNNNNNNNNYNNNNNNNYYNNNNNNNNNNNN", "NYNNYNNNNNNYYNNNYNNNNNNNNNNNYNNNYYNNNYNNYNNNNNN", "NNYNNYNNYNNNNNNNNNNYNNYNNNNNYNYNNNNNNNNNNNNNNNN", "NNNNNNNNNYYNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNYYNNNNNYNYNNNNNNNNNYNNNNNNNNNNNNNYNNNNYNYNNNN", "NNNNNNNNNNNNNNNNNNNNNNYNNNNNNYNNNYNNNNNNNNNNNNN", "NNNYNNNNNNNYNNNNNNYNNNNNYNNNNNNNNNNNNNNNYNNNNNN", "NNYNNNNYNNNYNNNNYNNNNNNNNNNNNNNNNNNYNNNNYYYYNYN", "NNNNNNYNNNNNNNNYNNNYNNNNNNNNNNYYNNNNYNNNNNNYNNN", "NNNYYNNNNNNNNNNYYNYYNYNNNYNYNNNNNNNNNNYNYNNNNNN", "YNNNYNNNNNYNYYNNNNNNNNNNNNNNNNNNNNNYNNNNYNNNNNN", "YNNNNYNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYYNNNN", "NNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNY", "NNYYNNNNNNNYNNNYNNNNNNYNNNNNNNNYNNNNNNNNNNNNNNN", "NNNNYNNNNNNYYYYNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNYYNNNNNNNNNNNNNNNNNNYNNNNN", "NNNNYNNYNNNNYNNNYNNNYNYNNNNNNNNNNNNNNNNNYNNNNNN", "NNNNNYNNNNNNYYNNNNNNNYNNNNNNNNNNYNNNYNNYYNNYNNN", "NNNNNNNYYYYNNNNYNYNNNNNYNNNNNNNNNNNNNYYNNNNNNNN", "YNNNNNNNYNNNNNNNNNNNNNNNNNYNNNNNNNNNNNYNYYNNNNN", "NNNNNNNNNNNYNNNYNNNNYYNYNNNYNNNNYNNNNNNNNNNYNNN", "NYNNNNNNNNYNNNNNNYNNNNNNYYNNNNNNNNNYNYYNNYNYNNN", "YNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNYYYNNNNYNNNNNNN", "NNNNNNNNYNNNNNNYNNNNNNNNNNYNNNYNNNNNNYNNNYNNNYN", "NNNNNYNNNNNNNNNNNNNYNNYYNNNNYNNNNNNNNNNNNNYNNNN", "NNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNYNNYYNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNYNNYNNNNN", "YNYYNYNNNNNNYYNYNNNNNYNYNNNNNYNNNNNNNNNNYNNNNNN", "NNNNNNNNNNYNNNNNNYYNNNNNNNNNYNNYNNNNNNYYNNNNNNN", "NYNYNYNNNNNNNNNNNNNYNNNYYNNNNNNNNNNNNNNNNNNNNNN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls(vector <string>(love, love + (sizeof love / sizeof love[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 8: {
			string love[]             = {"NYNNNYNYNYNNNNNYNNN", "NYNNNNNNNNNNNNYNNNN", "NNNNNYNNNNNNNNNNNNN", "NNNYNNNNYNNNNNNNNNN", "NNNNNYNNNYNNNNNYNYN", "NNNNNNNYNNNNNNNNNNN", "NNNNNNNNNNYNNNNNNNN", "NNNNNNNNYNNNNNNNNNN", "NYNNNNNYNYYNNNNNNNN", "NYNNNNNNNYNNNNNNNNN", "NNNNNNNYNNNNNNNNNNN", "NNNNYYYNNNYYNNNNNNN", "NNYNNYNNYNNNYYNNNNN", "NNYNNYYYNNNNYYYNYNN", "NNNNNNNNYNNNNNNNNNN", "YYNNNNYNNNNYNYNYNNN", "YYNNNNNYNNNNNNYNNNN", "NNNYNNNNNNNNNNNNNYN", "YNNNNNNNNNNNNNYNNNN"}
;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls(vector <string>(love, love + (sizeof love / sizeof love[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 9: {
			string love[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls(vector <string>(love, love + (sizeof love / sizeof love[0])));
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
