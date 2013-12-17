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

class CoinsOfByteland {
 public:
  int countCoinSystems(vector <int> maxSum);
};

const int MOD = 1000000007;

int N;
map<vector<int>, int> mem[1 << 4];

inline int get(int b, int i) {
  return (b >> i) & 1;
}

int search(vector<int> &ub, int m) {
  if (count(all(ub), 0) == N) return m == ((1 << (N - 1)) - 1) ? 1 : 0;
  if (mem[m].count(ub)) return mem[m][ub];

  int ans = 0;
  rep (b, 1 << N) {
    int tm = 0;
    rep (i, N - 1) tm |= (get(b, i) * 2 + get(m, i) > get(b, i + 1) * 2) << i;

    vector<int> tub(N);
    int s = 0;
    rep (i, N) {
      s += get(b, i);
      if (ub[i] - s < 0) goto dmp;
      tub[i] = (ub[i] - s) / 2;
    }

    (ans += search(tub, tm)) %= MOD;
 dmp:;
  }

  return mem[m][ub] = ans;
}

int CoinsOfByteland::countCoinSystems(vector <int> A) {
  N = A.size();
  rep (i, N) A[i] -= i + 1;
  return search(A, 0);
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
			int maxSum[]              = {7, 11, 15, 18, 20};
			int expected__            = 7;

			std::clock_t start__      = std::clock();
			int received__            = CoinsOfByteland().countCoinSystems(vector <int>(maxSum, maxSum + (sizeof maxSum / sizeof maxSum[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int maxSum[]              = {10, 19};
			int expected__            = 45;

			std::clock_t start__      = std::clock();
			int received__            = CoinsOfByteland().countCoinSystems(vector <int>(maxSum, maxSum + (sizeof maxSum / sizeof maxSum[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int maxSum[]              = {10000};
			int expected__            = 10000;

			std::clock_t start__      = std::clock();
			int received__            = CoinsOfByteland().countCoinSystems(vector <int>(maxSum, maxSum + (sizeof maxSum / sizeof maxSum[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int maxSum[]              = {1326549, 3212423, 6546565, 8785456};
			int expected__            = 546494632;

			std::clock_t start__      = std::clock();
			int received__            = CoinsOfByteland().countCoinSystems(vector <int>(maxSum, maxSum + (sizeof maxSum / sizeof maxSum[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int maxSum[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CoinsOfByteland().countCoinSystems(vector <int>(maxSum, maxSum + (sizeof maxSum / sizeof maxSum[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int maxSum[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CoinsOfByteland().countCoinSystems(vector <int>(maxSum, maxSum + (sizeof maxSum / sizeof maxSum[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int maxSum[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CoinsOfByteland().countCoinSystems(vector <int>(maxSum, maxSum + (sizeof maxSum / sizeof maxSum[0])));
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
