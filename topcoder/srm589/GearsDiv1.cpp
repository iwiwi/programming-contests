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

class GearsDiv1 {
 public:
  int getmin(string color, vector <string> graph);
};

const int MAX_V = 60;

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

int GearsDiv1::getmin(string color, vector <string> graph) {
  int N = color.size();

  int ans = INT_MAX;
  for (auto p : {"RG", "RB", "GB"}) {
    char Lc = p[0], Rc = p[1];
    L = count(all(color), Lc);
    R = count(all(color), Rc);

    int l = 0;
    rep (i, N) if (color[i] == Lc) {
      int r = 0;
      rep (j, N) if (color[j] == Rc) adj[l][r++] = graph[i][j] == 'Y';
      ++l;
    }
    ans = min(ans, bipartite_matching());
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
			string color              = "RGB";
			string graph[]            = {"NYY","YNY","YYN"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string color              = "RGBR";
			string graph[]            = {"NNNN","NNNN","NNNN","NNNN"};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string color              = "RGBR";
			string graph[]            = {"NYNN","YNYN","NYNY","NNYN"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string color              = "RRRRRGRRBGRRGBBGGGBRRRGBRGRRGG";
			string graph[]            = {"NNNNNYNNNYNNYNNNYNNNNNNNNYNNYY",
 "NNNNNNNNYNNNYNYNNYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNNNNYNNNNNNYNNNY",
 "NNNNNNNNNYNNYNNYYYNNNNYNNYNNNN",
 "NNNNNNNNNYNNYNNYYYNNNNYNNNNNNN",
 "YNYNNNYYYNNYNYYNNNNNYYNYNNYYNN",
 "NNNNNYNNNNNNNNNYYYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNYNNNNNNNNNNNNYN",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "YNNYYNNNYNNNNYYNNNYNYYNYNNNNNN",
 "NNNNNNNNNNNNYNNYNYNNNNYNNNNNNY",
 "NNNNNYNNNNNNYNNYYYNNNNNNNNNNYN",
 "YYNYYNNNYNYYNYYNNNYNYNNYNNNNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNYNYYY",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "NNNYYNYYYNYYNYYNNNYNYNNYYNYYNN",
 "YNNYYNYNYNNYNYYNNNYNNNNYYNNYNN",
 "NYNYYNYNYNYYNYYNNNNYYNNYYNYNNN",
 "NNYNNNNNNYNNYNNYYNNNNNYNNYNNNY",
 "NNNNNNNNNNNNNNNNNYNNNNYNNYNNNY",
 "NNNNNYNNNYNNYNNYNYNNNNYNNNNNYY",
 "NNNNNYNNNYNNNNNNNNNNNNYNNNNNNN",
 "NYNYYNYNYNYNNYYNNNYYYYNYYNYNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNNNNNY",
 "NNNNNNNNNNNNNNNYYYNNNNYNNYNNYY",
 "YYYYNNYNYNNNNYYNNNYYNNNNYNYYNN",
 "NNNNNYNNNNNNNNNYNYNNNNYNNYNNYN",
 "NNNNNYNNNNNNNYNYYNNNNNNNNYNNYY",
 "YYNNNNYYYNNYNYYNNNNNYNNNYNYYNN",
 "YYYNNNYNYNYNNYYNNNYYYNNYYNNYNN"};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
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
