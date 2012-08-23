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

struct Suminator {
  int findMissing(vector <int> program, int wantedResult);
};

typedef long long ll;
typedef pair<ll, ll> pll;

pll doit(vector<ll> P) {
  int N = P.size();

  stack<pll> stk;
  rep (i, N * 2) stk.push(mp(0, 0));
  rep (i, N) {
    if (P[i] == 0) {
      pll a = stk.top(); stk.pop();
      pll b = stk.top(); stk.pop();
      stk.push(mp(a.first + b.first, a.second + b.second));
    } else if (P[i] == -1) {
      stk.push(mp(0, 1));
    } else {
      stk.push(mp(P[i], 0));
    }
  }
  return stk.top();
}

int Suminator::findMissing(vector <int> program_, int wantedResult_) {
  vector<ll> P(all(program_));
  int N = P.size();
  ll W = wantedResult_;

  // == zero?
  vector<ll> P2(N);
  rep (i, N) P2[i] = P[i] == -1 ? 0 : P[i];
  if (doit(P2).first == W) return 0;

  // > zero?
  pll a = doit(P);
  if (a.second == 0) {
    if (a.first == W) return 1;  // any
    else return -1;
  } else {
    ll x = W - a.first;
    if (x > 0) return x;
    else return -1;
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
			int program[]             = {7,-1,0};
			int wantedResult          = 10;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int program[]             = {100, 200, 300, 0, 100, -1};
			int wantedResult          = 600;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int program[]             = {-1, 7, 3, 0, 1, 2, 0, 0};
			int wantedResult          = 13;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int program[]             = {-1, 8, 4, 0, 1, 2, 0, 0};
			int wantedResult          = 16;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int program[]             = {1000000000, 1000000000, 1000000000, 1000000000, -1, 0, 0, 0, 0};
			int wantedResult          = 1000000000;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int program[]             = {7, -1, 3, 0};
			int wantedResult          = 3;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int program[]             = ;
			int wantedResult          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int program[]             = ;
			int wantedResult          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int program[]             = ;
			int wantedResult          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
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
