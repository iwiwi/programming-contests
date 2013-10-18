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

class TreeUnion {
 public:
  double expectedCycles(vector <string> tree1, vector <string> tree2, int K);
};

vector<vector<int>> parse_tree(const vector<string> &tree) {
  string S = accumulate(all(tree), string());
  stringstream ss(S);

  vector<vector<int> > res(1);
  for (int i = 1, x; ss >> x; ++i) {
    res.eb(1, x);
    res[x].eb(i);
  }
  return res;
}

void dfs(int r, int v, int p, int d, const vector<vector<int>> &adj, vector<int> &cnt) {
  if (r < v) ++cnt[d];
  rep (i, adj[v].size()) if (adj[v][i] != p) dfs(r, adj[v][i], v, d + 1, adj, cnt);
}

double TreeUnion::expectedCycles(vector <string> tree1, vector <string> tree2, int K) {
  vector<vector<int>> adj1 = parse_tree(tree1);
  vector<vector<int>> adj2 = parse_tree(tree2);
  int N = adj1.size();
  assert(adj1.size() == adj2.size());

  vector<int> cnt1(N + 1), cnt2(N + 1);
  rep (i, N) dfs(i, i, -1, 0, adj1, cnt1);
  rep (i, N) dfs(i, i, -1, 0, adj2, cnt2);
  int T = accumulate(all(cnt1), 0);
  assert(T == N * (N - 1) / 2);

  double ans = 0;
  for (int k = 1; K - k - 2 >= 1; ++k) {
    ans += cnt1[k] * (cnt2[K - k - 2] / (double)T);
  }
  return ans;
}















// BEGIN CUT HERE
#include <algorithm>
#include <cmath>
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

	static const double MAX_DOUBLE_ERROR = 1e-9;
	static bool topcoder_fequ(double expected, double result) {
		if (std::isnan(expected)) {
			return std::isnan(result);
		} else if (std::isinf(expected)) {
			if (expected > 0) {
				return result > 0 && std::isinf(result);
			} else {
				return result < 0 && std::isinf(result);
			}
		} else if (std::isnan(result) || std::isinf(result)) {
			return false;
		} else if (std::fabs(result - expected) < MAX_DOUBLE_ERROR) {
			return true;
		} else {
			double mmin = std::min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			double mmax = std::max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			return result > mmin && result < mmax;
		}
	}
	double moj_relative_error(double expected, double result) {
		if (std::isnan(expected) || std::isinf(expected) || std::isnan(result) || std::isinf(result) || expected == 0) {
			return 0;
		}
		return std::fabs(result-expected) / std::fabs(expected);
	}

	int verify_case(int casenum, const double &expected, const double &received, std::clock_t elapsed) {
		std::cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received);
			if (rerr > 0) {
				std::sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			string tree1[]            = {"0"};
			string tree2[]            = {"0"};
			int K                     = 4;
			double expected__         = 1.0;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string tree1[]            = {"0 1"};
			string tree2[]            = {"0 1"};
			int K                     = 4;
			double expected__         = 1.3333333333333333;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string tree1[]            = {"0 1"};
			string tree2[]            = {"0 1"};
			int K                     = 6;
			double expected__         = 0.3333333333333333;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string tree1[]            = {"0 ", "1 1 1"};
			string tree2[]            = {"0 1 0 ", "1"};
			int K                     = 5;
			double expected__         = 4.0;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string tree1[]            = {"0 1 2 0 1 2 0 1 2 5 6 1", "0 11", " 4"};
			string tree2[]            = {"0 1 1 0 2 3 4 3 4 6 6", " 10 12 12"};
			int K                     = 7;
			double expected__         = 13.314285714285713;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string tree1[]            = ;
			string tree2[]            = ;
			int K                     = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string tree1[]            = ;
			string tree2[]            = ;
			int K                     = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string tree1[]            = ;
			string tree2[]            = ;
			int K                     = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
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
