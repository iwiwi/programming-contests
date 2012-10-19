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

struct Stamp {
  int getMinimumCost(string desiredColor, int stampCost, int pushCost);
};

typedef long long ll;
const int INF = 987654321;

int N, L;
string S;
ll mem[60];

ll search(int k) {
  if (k == N) return 0;
  if (mem[k] != -1) return mem[k];

  int cnt[256] = {};

  ll res = INF;
  for (int i = k + 1; i <= N; ++i) {  // [k, i)
    cnt[int(S[i - 1])] = 1;
    if (cnt['R'] + cnt['G'] + cnt['B'] > 1) break;

    int l = i - k;
    if (l < L) continue;

    int c = l / L + (l % L ? 1 : 0);
    res = min(res, c + search(i));
  }

  return mem[k] = res;
}

int Stamp::getMinimumCost(string desiredColor, int stampCost, int pushCost) {
  S = desiredColor;
  N = S.length();

  ll ans = INF;
  for (L = 1; L <= N; ++L) {
    memset(mem, -1, sizeof(mem));
    ans = min(ans, L * (ll)stampCost + pushCost * search(0));
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
			string desiredColor       = "RRGGBB";
			int stampCost             = 1;
			int pushCost              = 1;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = Stamp().getMinimumCost(desiredColor, stampCost, pushCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string desiredColor       = "R**GB*";
			int stampCost             = 1;
			int pushCost              = 1;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = Stamp().getMinimumCost(desiredColor, stampCost, pushCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string desiredColor       = "BRRB";
			int stampCost             = 2;
			int pushCost              = 7;
			int expected__            = 30;

			clock_t start__           = clock();
			int received__            = Stamp().getMinimumCost(desiredColor, stampCost, pushCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string desiredColor       = "R*RR*GG";
			int stampCost             = 10;
			int pushCost              = 58;
			int expected__            = 204;

			clock_t start__           = clock();
			int received__            = Stamp().getMinimumCost(desiredColor, stampCost, pushCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string desiredColor       = "*B**B**B*BB*G*BBB**B**B*";
			int stampCost             = 5;
			int pushCost              = 2;
			int expected__            = 33;

			clock_t start__           = clock();
			int received__            = Stamp().getMinimumCost(desiredColor, stampCost, pushCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string desiredColor       = "*R*RG*G*GR*RGG*G*GGR***RR*GG";
			int stampCost             = 7;
			int pushCost              = 1;
			int expected__            = 30;

			clock_t start__           = clock();
			int received__            = Stamp().getMinimumCost(desiredColor, stampCost, pushCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string desiredColor       = ;
			int stampCost             = ;
			int pushCost              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Stamp().getMinimumCost(desiredColor, stampCost, pushCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string desiredColor       = ;
			int stampCost             = ;
			int pushCost              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Stamp().getMinimumCost(desiredColor, stampCost, pushCost);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string desiredColor       = ;
			int stampCost             = ;
			int pushCost              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Stamp().getMinimumCost(desiredColor, stampCost, pushCost);
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
