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

class TheExperiment {
 public:
  int countPlacements(vector <string> intensity, int M, int L, int A, int B);
};

typedef long long ll;
const ll MOD = 1000000009;

int N, S[310], M, L, A, B;
int sum[310];

inline int get_sum(int l, int r) {  // [l, r)
  return sum[r] - sum[l];
}

ll mem[310][310][3];

ll rig(int l, int m, int t) {  // [l, N), |m| sponges, need a full sponge?
  if (m == 0) return t != 1 ? 1 : 0;
  if (l >= N) return 0;
  if (mem[l][m][t] != -1) return mem[l][m][t];

  ll ans = 0;
  if (t != 1) ans += rig(l + 1, m, 0);

  for (int r = l + 1; r <= N && r - l <= L; ++r) {  // [l, r)
    ll d = get_sum(l, r);
    if (A <= d && d <= B) {
      ll tt = max(t, r - l == L ? 2 : 1);
      (ans += rig(r, m - 1, tt)) %= MOD;
    }
  }

  return mem[l][m][t] = ans;
}

int TheExperiment::countPlacements(vector <string> intensity, int M_, int L_, int A_, int B_) {
  {
    M = M_;
    L = L_;
    A = A_;
    B = B_;

    string s = accumulate(all(intensity), string());
    N = s.length();
    rep (i, N) S[i] = s[i] - '0';

    sum[0] = 0;
    rep (i, N) sum[i + 1] = sum[i] + S[i];
  }

  memset(mem, -1, sizeof(mem));
  return rig(0, M, 0);
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
			string intensity[]        = {"341156"};
			int M                     = 3;
			int L                     = 3;
			int A                     = 6;
			int B                     = 10;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string intensity[]        = {"999112999"};
			int M                     = 2;
			int L                     = 4;
			int A                     = 21;
			int B                     = 30;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string intensity[]        = {"111"};
			int M                     = 2;
			int L                     = 2;
			int A                     = 2;
			int B                     = 3;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string intensity[]        = {"59059", "110", "1132230231"};
			int M                     = 1;
			int L                     = 5;
			int A                     = 10;
			int B                     = 20;
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string intensity[]        = {"111111111111111111111111", "111111111111111111111111111", "11111111111111111111111"};
			int M                     = 12;
			int L                     = 8;
			int A                     = 4;
			int B                     = 2700;
			int expected__            = 418629948;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string intensity[]        = ;
			int M                     = ;
			int L                     = ;
			int A                     = ;
			int B                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string intensity[]        = ;
			int M                     = ;
			int L                     = ;
			int A                     = ;
			int B                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string intensity[]        = ;
			int M                     = ;
			int L                     = ;
			int A                     = ;
			int B                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
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
