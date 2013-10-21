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

class Excavations {
 public:
  long long count(vector <int> kind, vector <int> depth, vector <int> found, int K);
};

typedef long long ll;

ll cmb[60][60];
ll dp[60][60][60];

long long Excavations::count(vector <int> kind, vector <int> depth, vector <int> found, int K) {
  int N = kind.size();

  cmb[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    cmb[i][0] = 1;
    for (int j = 1; j <= i; ++j) cmb[i][j] = cmb[i - 1][j - 1] + cmb[i - 1][j];
  }

  map<int, int> sh;
  sh[0] = 0;
  for (int d : depth) sh[d] = 0;
  int D = 0;
  tr (sh, ite) ite->second = D++;
  for (int &d : depth) d = sh[d];

  vector<int> ds0;
  map<int, vector<int> > ds1;
  rep (i, N) {
    if (find(all(found), kind[i]) != found.end()) {
      ds1[kind[i]].eb(depth[i]);
    } else {
      ds0.eb(depth[i]);
    }
  }

  // Dynamic programming about found kinds
  memset(dp, 0, sizeof(dp));
  dp[0][0][0] = 1;
  int i = 0;
  tr (ds1, ite) {
    vector<int> &ds = ite->second;
    sort(all(ds));

    rep (j, ds.size()) {
      int r = (int)ds.size() - j - 1;
      rep (pd, D) {
        rep (k, K) {
          for (int rk = 0; rk <= r && k + 1 + rk <= K; ++rk) {
            dp[i + 1][max(ds[j], pd)][k + 1 + rk] += dp[i][pd][k] * cmb[r][rk];
          }
        }
      }
    }
    ++i;
  }

  // K-tuples without forbidden kinds
  ll ans = 0;
  rep (d, D) ans += dp[i][d][K];

  // K-tuples including forbidden kinds
  sort(all(ds0));
  reverse(all(ds0));
  rep (j, ds0.size()) {
    for (int d = 0; d < ds0[j]; ++d) {
      for (int k = 0; k <= K - 1; ++k) {
        ans += dp[i][d][k] * cmb[j][K - k - 1];
      }
    }
  }

  return ans;
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

	int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) {
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
			int kind[]                = {1, 1, 2, 2};
			int depth[]               = {10, 15, 10, 20};
			int found[]               = {1};
			int K                     = 2;
			long long expected__      = 3;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int kind[]                = {1, 1, 2, 2};
			int depth[]               = {10, 15, 10, 20};
			int found[]               = {1, 2};
			int K                     = 2;
			long long expected__      = 4;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int kind[]                = {1, 2, 3, 4};
			int depth[]               = {10, 10, 10, 10};
			int found[]               = {1, 2};
			int K                     = 3;
			long long expected__      = 0;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int kind[]                = {1, 2, 2, 3, 1, 3, 2, 1, 2};
			int depth[]               = {12512, 12859, 125, 1000, 99, 114, 125, 125, 114};
			int found[]               = {1, 2, 3};
			int K                     = 7;
			long long expected__      = 35;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int kind[]                = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
			int depth[]               = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3};
			int found[]               = {50};
			int K                     = 18;
			long long expected__      = 9075135300LL;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
        int kind[]                = {26, 18, 18, 18, 49, 10, 26, 49, 18, 27, 26, 10, 31, 26, 10, 28, 10, 18, 18, 18, 19};
        int depth[]               = {62714, 92615, 26348, 422, 92615, 26348, 81820, 62780, 95399, 4666, 95399, 62686, 92615, 82157, 422, 95399, 95399, 82157, 82157, 12525, 81820};
        int found[]               = {26, 10};
        int K                     = 18;
        long long expected__      = 0;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int kind[]                = ;
			int depth[]               = ;
			int found[]               = ;
			int K                     = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int kind[]                = ;
			int depth[]               = ;
			int found[]               = ;
			int K                     = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
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
