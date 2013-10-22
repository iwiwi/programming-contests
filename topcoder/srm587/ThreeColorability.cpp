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

class ThreeColorability {
 public:
  vector <string> lexSmallest(vector <string> cells);
};

int W, H;
vector<string> F;

int adj[60][60], col[60];

void search(int y, int c) {
  if (col[y] != -1) {
    if (c != col[y]) throw 0;
  } else {
    col[y] = c;
    rep (ty, H) if (adj[y][ty]) {
      if (adj[y][ty] == 3) throw 0;
      search(ty, c ^ (adj[y][ty] - 1));
    }
  }
}

bool colorable() {
  memset(adj, 0, sizeof(adj));
  rep (y0, H) rep (y1, H) {
    rep (x, W) if (F[y0][x] != '?' && F[y1][x] != '?') {
      adj[y0][y1] |= 1 << (F[y0][x] == F[y1][x] ? 0 : 1);
    }
  }

  memset(col, -1, sizeof(col));
  try {
    rep (y, H) if (col[y] == -1) search(y, 0);
    return true;
  } catch (...) {
    return false;
  }
}

vector <string> ThreeColorability::lexSmallest(vector <string> cells) {
  W = cells[0].length();
  H = cells.size();
  F = cells;
  if (!colorable()) return vector<string>();

  rep (y, H) rep (x, W) if (F[y][x] == '?') {
    F[y][x] = 'N';
    if (!colorable()) {
      F[y][x] = 'Z';
      // assert(colorable());
    }
  }
  return F;
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

	template<typename T> std::ostream& operator<<(std::ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }
	template<> std::ostream& operator<<(std::ostream &os, const vector<string> &v) { os << "{"; for (vector<string>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " \"" << *vi << "\""; } os << " }"; return os; }

	int verify_case(int casenum, const vector <string> &expected, const vector <string> &received, std::clock_t elapsed) {
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
			string cells[]            = {"Z"};
			string expected__[]       = {"Z" };

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string cells[]            = {"??", "?N"};
			string expected__[]       = {"NN", "NN" };

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string cells[]            = {"ZZZ", "ZNZ"};
			string expected__[]       = { };

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string cells[]            = {"N?N??NN","??ZN??Z","NN???Z?","ZZZ?Z??","Z???NN?","N?????N","ZZ?N?NN"};
			string expected__[]       = { };

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			string cells[]            = {"ZZZZ","ZZZZ","ZZZZ"};
			string expected__[]       = {"ZZZZ", "ZZZZ", "ZZZZ" };

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string cells[]            = ;
			string expected__[]       = ;

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			string cells[]            = ;
			string expected__[]       = ;

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			string cells[]            = ;
			string expected__[]       = ;

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
