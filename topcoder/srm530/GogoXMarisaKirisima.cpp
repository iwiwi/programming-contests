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

struct GogoXMarisaKirisima {
  int solve(vector <string> choices);
};

const int INF = 99999;

int adj[60][60], mat[60][60], prv[60][60];

void doit(int s, int t) {
  while (s != t) {
    int v = prv[s][t];
    adj[v][t] = 0;
    t = v;
  }
}

int GogoXMarisaKirisima::solve(vector <string> choices) {
  int N = choices.size();
  rep (i, N) rep (j, N) adj[i][j] = i == j ? 0 : choices[i][j] == 'Y' ? 1 : INF;

  int ans = 0;
  for (;;) {
    rep (i, N) rep (j, N) {
      mat[i][j] = adj[i][j];
      prv[i][j] = i;
    }

    rep (k, N) rep (i, N) rep (j, N) {
      if (mat[i][j] > mat[i][k] + mat[k][j]) {
        mat[i][j] = mat[i][k] + mat[k][j];
        prv[i][j] = prv[k][j];
      }
    }

    int bst = INF;
    rep (i, N) rep (j, N) if (adj[i][j] == 1) {
      bst = min(bst, mat[0][i] + 1 + mat[j][N - 1]);
    }
    if (bst >= INF) break;

    rep (i, N) rep (j, N) if (adj[i][j] == 1) {
      if (bst == mat[0][i] + 1 + mat[j][N - 1]) {
        adj[i][j] = 0;
        doit(0, i);
        doit(j, N - 1);
        goto done;
      }
    }
 done:
    ++ans;
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
			string choices[]          = {"NYN"
,"YNY"
,"NNN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = GogoXMarisaKirisima().solve(vector <string>(choices, choices + (sizeof choices / sizeof choices[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string choices[]          = {"NNY"
,"YNY"
,"YNN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = GogoXMarisaKirisima().solve(vector <string>(choices, choices + (sizeof choices / sizeof choices[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string choices[]          = {"NN"
,"NN"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = GogoXMarisaKirisima().solve(vector <string>(choices, choices + (sizeof choices / sizeof choices[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string choices[]          = {"NYYY"
,"NNNY"
,"NNNY"
,"NNNN"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = GogoXMarisaKirisima().solve(vector <string>(choices, choices + (sizeof choices / sizeof choices[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string choices[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GogoXMarisaKirisima().solve(vector <string>(choices, choices + (sizeof choices / sizeof choices[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string choices[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GogoXMarisaKirisima().solve(vector <string>(choices, choices + (sizeof choices / sizeof choices[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string choices[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GogoXMarisaKirisima().solve(vector <string>(choices, choices + (sizeof choices / sizeof choices[0])));
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
