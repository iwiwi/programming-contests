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

struct CasketOfStar {
  int maxEnergy(vector <int> weight);
};

int mem[60][60];
int N;
vector<int> W;

int search(int l, int r) {
  if (r - l == 1) return 0;
  if (mem[l][r] != -1) return mem[l][r];

  int res = 0;
  for (int i = l + 1; i < r; ++i) {
    res = max(res, search(l, i) + search(i, r));
  }

  res += W[l] * W[r];
  return mem[l][r] = res;
}

int CasketOfStar::maxEnergy(vector <int> weight) {
  W = weight;
  N = W.size();

  memset(mem, -1, sizeof(mem));
  return search(0, N - 1);
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
			int weight[]              = {1,2,3,4};
			int expected__            = 12;

			clock_t start__           = clock();
			int received__            = CasketOfStar().maxEnergy(vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int weight[]              = {100,2,1,3,100};
			int expected__            = 10400;

			clock_t start__           = clock();
			int received__            = CasketOfStar().maxEnergy(vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int weight[]              = {2,2,7,6,90,5,9};
			int expected__            = 1818;

			clock_t start__           = clock();
			int received__            = CasketOfStar().maxEnergy(vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int weight[]              = {477,744,474,777,447,747,777,474};
			int expected__            = 2937051;

			clock_t start__           = clock();
			int received__            = CasketOfStar().maxEnergy(vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int weight[]              = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
			int expected__            = 13;

			clock_t start__           = clock();
			int received__            = CasketOfStar().maxEnergy(vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int weight[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CasketOfStar().maxEnergy(vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int weight[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CasketOfStar().maxEnergy(vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int weight[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CasketOfStar().maxEnergy(vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
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
