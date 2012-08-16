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

struct ColorfulWolves {
  int getmin(vector <string> colormap);
};



int ColorfulWolves::getmin(vector <string> colormap) {
  int N = colormap.size();

  int pot[60];
  rep (i, N) pot[i] = INT_MAX;
  pot[0] = 0;
  bool done[60] = {};

  for (;;) {
    int v = -1, p = INT_MAX;
    rep (w, N) {
      if (!done[w] && pot[w] < p) {
        v = w;
        p = pot[w];
      }
    }
    if (v == -1) break;

    done[v] = true;

    int c = 0;
    rep (w, N) {
      if (colormap[v][w] == 'N') continue;
      pot[w] = min(pot[w], p + c);
      ++c;
    }
  }

  if (pot[N - 1] == INT_MAX) return -1;
  else return pot[N - 1];
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
			string colormap[]         = {"NYN","YNY","NNN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = ColorfulWolves().getmin(vector <string>(colormap, colormap + (sizeof colormap / sizeof colormap[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string colormap[]         = {"NNNNNNNY","NNNNYYYY","YNNNNYYN","NNNNNYYY","YYYNNNNN","YNYNYNYN","NYNYNYNY","YYYYYYYN"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = ColorfulWolves().getmin(vector <string>(colormap, colormap + (sizeof colormap / sizeof colormap[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string colormap[]         = {"NYYYYN","YNYYYN","YYNYYN","YYYNYN","YYYYNN","YYYYYN"};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = ColorfulWolves().getmin(vector <string>(colormap, colormap + (sizeof colormap / sizeof colormap[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string colormap[]         = {
"NYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYN"
};
			int expected__            = 48;

			clock_t start__           = clock();
			int received__            = ColorfulWolves().getmin(vector <string>(colormap, colormap + (sizeof colormap / sizeof colormap[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string colormap[]         = {
"NYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
"YYNYYYYYYYYYNNNNNYYYYYYNNNNNYYYYYNNYYYNNYYYYYYYYYY",
"YYYNYYYYYYYNYYYYYYYYYYYNYYYYNYYYYNYNYNYNYYYYYYYYYY",
"YNNNNYYYYYYNYYYYYYYYYYYNYYYYNYYYYNYNYNYNYYYYYYYYYY",
"YYYYYNYYYYYYNNNNNYYYYYYNNNNNYYYYYNYYNYYNYYYYYYYYYY",
"YYYYNNNNNYYYYYYYYNYYYYYNYYYNYYYYYNYYNYYNYYYYYYYYYY",
"YYYYYYYNYYYYYYYYYNYYYYYNYYYYNYYYYNYYYYYNYYYYYYYYYY",
"YYYYYYYYNYYYNNNNNYYYYYYNYYYYNYYYYNYYYYYNYYYYYYNYYY",
"YYNNNYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYY",
"YYYYYYYYYYNYYNNNNNNNNYYYYYYYYNNNNNNYYYYYYYYYNNYYYY",
"YYYYYYYYYYYNYYYYYYYYYYNNNNNNYNYYYYYYYYYYYYYYYNYYYY",
"YYYNNNNNYYYYNYYYYYYYYYYYYYYYYYYYYNNNNNYYYYYNNYYYYY",
"YYYYYYYYYYYYYNYYYYYNNNNYYYYYYNNNNNYYYYYNNNNYYYYYYY",
"YYYYNNNNYYYYYYNYYYYYYYYYYYYYYYYYYYNNNNNYYYYYYYYYYY",
"YYYYYYYYYYYYYYYNYYNNNNNNNNNYYYYYYYYYYYYYYYYYYYYYYY",
"YYNNNNNNYYYYYYYYNYYYYYYYYYYYNNNNYYYYYYYYYYNNNNNYYY",
"YYNYYYYYNNNYYYYYYNYYYYYYNNNNNNNNNYYYYYYYYYYYYYYYYY",
"YYYYNYYYYYYYNNNYYYNYYYYYYYYYYYYYNNNNNNYYYYYYYYYYYY",
"YYYYYYNYYYNNNNYYYYYNYYYYYYYYYYYYYYYYYNNNNNYYYYYYYY",
"NNNNNYYYYYYYNYYYYYYYNYYYYYYYYYYYNNNNNNNNYYYYYYYYYY",
"YYYYYYYYYYYYYNNNNYYYYNYYYNNNNYYYYYYYYYYYYNNNNNNYYY",
"YYYYNNNYYYYNNNNYYYYYYYNYYYYYYYYYYYYYNNNNNNYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYNYYYNNNYYYYNNNNYYYYYYYYYYYY",
"YYYYYYYYYNNNNNYYYYYYYYYYNYYYYYNNNNYYYYYYYYYYYYYYYY",
"YYYNNNNYYYYYYYYYYYYYYYYYYNYYYYYNNNNYYYYYNNNNNYYYYY",
"YYYYYYYYYYYNNNNNYYYYYYYYYYNYYYYYYYYYYNNNNNYYYYYYYY",
"YYYNNNNNNYYYYYYNNNNNYYYYYYYNYYYYYYYYYYYYYYYYYYYYYY",
"YYYYYNNNNNYYYYYYNNNNNYYYYYYYNYYYYYYYNNNNNNYYYYYYYY",
"YYNNNNNYYYYYYYYYYYYYYYYYYYNNNNNNYYYYYYYYYYYYYNNNYY",
"YYYYNNNNNYYYYYYYYYNNNNNNNNNYYYNYYYYYYNNNNNYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYNNNNNNYYYYYYYYY",
"YYYYYYYYYYYYYNNNNNNYYYYYYNNNNNNYNYYYYYYYYYNNNYYYYN",
"YYYYYNNNNNNNNYYYYYYNNNNNYYYYYYYYYNYYYYYYYYNNNNNYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYNNNNYYYYYYNYYYYYYYYYYYYYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNNNNNNNYYYYYYYNNNNNY",
"YYYNNNNNNNNYYYNNNNNNNNYYYYNYYYYYYYYYNYYYYYYYYYYYYY",
"YYYNYYYYYYYYYYNYYYYYYYYYNNNYYYYYYYYYYNYYYYYYYYYYYY",
"YYYNYYYYYYYYYYNYYYYYYYYYYYNYYYYYYNNNNNNYYYNNNNNYYY",
"YYYNYYYYYYYYYYNYYYYYYYYYYYNYYYYYYYYYYYYNYYYYYYYYYY",
"YYYNYNNNNYYYYYNYNNNNYYYYYYNYYYYYYYYYNNNNNNYYYYYYYY",
"YYYNNYYYYNYYYYNNYYYYNYYYYYNYYYYYYYYYYYYYYNYYYYYYYY",
"YYYNYYYYYYNYYYNYYYYYYNYYYYNYYYYYYYYYYYYYYYNYYNNNNY",
"YYYYYYYYYYNYYYYYYYYYYNYYYYNYYYYYNNNNNNYYYYYNYYYYYY",
"YYYYYYYYYYNYYYYYYYYYYNYYYYNYYYYYYYYYYYNNNNNNNYYYYY",
"YYYNYYYYYNYYYYNYYYYYNYYYYYNYYYNNNNNNNNNNNNYYYNYYYY",
"YYYYNNNNNYYYYYYNNNNNYYYYNNNNNYYYNNNNNNYYYNNNNYNYYY",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYY",
"YYYYNNNNYYYYNNNNNNNNNNNNYYYYYNNNNNNNNNYYYYYYYYYYNY",
"YYYYYYNYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYNYYYYYN"
};
			int expected__            = 35;

			clock_t start__           = clock();
			int received__            = ColorfulWolves().getmin(vector <string>(colormap, colormap + (sizeof colormap / sizeof colormap[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string colormap[]         = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorfulWolves().getmin(vector <string>(colormap, colormap + (sizeof colormap / sizeof colormap[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string colormap[]         = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorfulWolves().getmin(vector <string>(colormap, colormap + (sizeof colormap / sizeof colormap[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string colormap[]         = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorfulWolves().getmin(vector <string>(colormap, colormap + (sizeof colormap / sizeof colormap[0])));
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
