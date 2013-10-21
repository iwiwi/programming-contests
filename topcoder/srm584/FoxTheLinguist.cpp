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

class FoxTheLinguist {
 public:
  int minimalHours(int n, vector <string> courseInfo);
};

const int MAX_N = 100000;

int N;
vector<int> adj[MAX_N], rev[MAX_N];

bool vis[MAX_N];
int ord[MAX_N], num, id[MAX_N];

void dfs1(int v) {
  if (vis[v]) return;
  vis[v] = true;
  for (int i = 0; i < (int)adj[v].size(); i++) dfs1(adj[v][i]);
  ord[num++] = v;
}

void dfs2(int v) {
  if (vis[v]) return;
  vis[v] = true; id[v] = num;
  for (int i = 0; i < (int)rev[v].size(); i++) dfs2(rev[v][i]);
}

void scc() {
  memset(vis, 0, sizeof(vis)); num = 0;
  for (int i = 0; i < N; i++) dfs1(i);
  memset(vis, 0, sizeof(vis)); num = 0;
  for (int i = N-1; i >= 0; i--) if (!vis[ord[i]]) dfs2(ord[i]), num++;
}




int saiki(int v) {
  if (vis[v]) return 0;
  vis[v] = true;
  int res = 1;
  for (int i = 0; i < (int)adj[v].size(); i++) res += saiki(adj[v][i]);
  return res;
}

const double EPS = 1E-10;

double minimum_spanning_arborescence(int n, int r, vector<int> *ra, vector<double> *rw) {
  double c, res = 0;
  for (int i = 0; i < n; i++) { adj[i].clear(); rev[i].clear(); }
  for (int i = 0; i < n; i++) {
    if (i == r) continue;
    if (rw[i].empty()) throw -1;
    res += (c = *min_element(rw[i].begin(), rw[i].end()));
    for (int j = 0; j < (int)ra[i].size(); j++)
      if ((rw[i][j] -= c) < EPS) {
        adj[ra[i][j]].push_back(i);
        rev[i].push_back(ra[i][j]);
      }
  }
  memset(vis, 0, sizeof(vis));
  if (saiki(r) == n) return res;
  N = n;
  scc();
  int m = num;
  vector<int> nra[m];
  vector<double> nrw[m];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (int)ra[i].size(); j++) {
      if (id[i] == id[ra[i][j]]) continue;
      nra[id[i]].push_back(id[ra[i][j]]);
      nrw[id[i]].push_back(rw[i][j]);
    }
  }
  return res += minimum_spanning_arborescence(m, id[r], nra, nrw);
}

int V;
vector<int> radj[110];
vector<double> rwgh[110];

void add_edge(int u, int v, double w) {
  radj[v].eb(u);
  rwgh[v].eb(w);
}

void add_edge(int c0, int l0, int c1, int l1, double w) {
  add_edge(c0 * 10 + l0, c1 * 10 + l1, w);
}

int FoxTheLinguist::minimalHours(int n, vector <string> courseInfo) {
  V = n * 10 + 1;
  int S = n * 10;
  rep (v, V) radj[v].clear(), rwgh[v].clear();

  rep (c, n) {
    add_edge(S, c * 10, 0);
    rep (l, 9) add_edge(c, l + 1, c, l, 0);
  }

  stringstream ss(accumulate(all(courseInfo), string()));
  for (string s; ss >> s; ) {
    add_edge(s[0] - 'A', s[1] - '0', s[4] - 'A', s[5] - '0', atoi(s.substr(7).c_str()));
  }

  try {
    return minimum_spanning_arborescence(V, S, radj, rwgh);
  } catch (...) {
    return -1;
  }
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
			int n                     = 1;
			string courseInfo[]       = {"A0->A9:1000 A0->A6:0300 A3->A9:0600"};
			int expected__            = 900;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 2;
			string courseInfo[]       = {"A0->A9:1000 B0->B9:1000 A1->B9:0300 B1->A9:0200"};
			int expected__            = 1200;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 3;
			string courseInfo[]       = {"C0->A6:00", "01 A3", "->B9:0001 A3->C6:000", "1",
" C3->A9:0001 A9->C9:0001 A0->A9:9999",
" B0->B9:9999 C0->C9:9999 A6->A9:9999"};
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 4;
			string courseInfo[]       = {"A0->A6:6666 A0->A9:9999",
" B0->B6:6666 B0->B9:9999",
" C0->C6:6666 C0->C9:9999",
" D0->D6:6666 D0->D9:9999",
" A6->B6:0666 B6->C6:0666",
" C6->D6:0666 D6->A6:0666",
" A9->B9:0099 B9->C9:0099",
" C9->D9:0099 D9->A9:0099"};
			int expected__            = 10296;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 1;
			string courseInfo[]       = {"A0->A9:9999 A0->A9:8888"};
			int expected__            = 8888;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int n                     = 1;
			string courseInfo[]       = {"A9->A9:0000",
" A9->A0:0000"};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int n                     = ;
			string courseInfo[]       = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int n                     = ;
			string courseInfo[]       = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int n                     = ;
			string courseInfo[]       = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
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
