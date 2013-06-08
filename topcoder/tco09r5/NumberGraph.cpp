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

struct NumberGraph {
  int largestSet(vector <string> graphSet, vector <int> joiningSet);
};

const int MAX_LR = 3010;

int L, R;
vector<int> adj[MAX_LR];
bool vis[MAX_LR], usd[MAX_LR];
int lev[MAX_LR + 1], mat[MAX_LR];

bool augment(int l) {
  if (l == L) return true;
  if (vis[l]) return false;
  vis[l] = true;
  rep (i, adj[l].size()) {
    int r = adj[l][i], l2 = mat[r];
    if (lev[l2] > lev[l] && augment(l2)) {
      mat[r] = l;
      return true;
    }
  }
  return false;
}

int bipartite_matching() {
  fill(mat, mat + R, L);
  memset(usd, 0, sizeof(bool) * L);
  bool update;
  do {
    fill(lev, lev + L + 1, -1);
    lev[L] = R;
    queue<int> que;
    rep (l, L) if (!usd[l]) {
      que.push(l);
      lev[l] = 0;
    }
    while (!que.empty()) {
      int l = que.front();
      que.pop();
      rep (i, adj[l].size()) {
        int r = adj[l][i], l2 = mat[r];
        if (lev[l2] < 0) {
          lev[l2] = lev[l] + 1;
          que.push(l2);
        }
      }
    }

    memset(vis, 0, sizeof(bool) * L);
    update = false;
    rep (l, L) if (!usd[l] && augment(l)) usd[l] = update = true;
  } while (update);

  return count(usd, usd + L, true);
}


int NumberGraph::largestSet(vector <string> graphSet, vector <int> joiningSet) {
  int m = 1;
  while (joiningSet[0] % (m * 2) == 0) m *= 2;

  map<int, vector<int> > ass;
  stringstream ss(accumulate(all(graphSet), string()));
  for (int a; ss >> a; ) ass[a % m].pb(a);

  int ans = 1;
  tr (ass, ite) {
    vector<int> as = ite->second;

    vector<int> bs[2];
    rep (i, as.size()) bs[(as[i] / m) % 2].pb(as[i]);

    rep (i0, bs[0].size()) {
      int b0 = bs[0][i0];
      rep (i1, bs[1].size()) {
        int b1 = bs[1][i1];
        if (!cpresent(joiningSet, abs(b1 - b0))) continue;

        vector<int> cs[2];
        rep (j0, bs[0].size()) if (i0 != j0 && cpresent(joiningSet, abs(bs[0][j0] - b1))) cs[0].pb(bs[0][j0]);
        rep (j1, bs[1].size()) if (i1 != j1 && cpresent(joiningSet, abs(bs[1][j1] - b0))) cs[1].pb(bs[1][j1]);

        L = cs[0].size();
        R = cs[1].size();
        rep (l, L) {
          adj[l].clear();
          rep (r, R) if (!cpresent(joiningSet, abs(cs[0][l] - cs[1][r]))) adj[l].pb(r);
        }
        ans = max(ans, 2 + (L + R - bipartite_matching()));
      }
    }
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
			string graphSet[]         = {"1 2 3 4 6 9 13 15 16 18 21 26"};
			int joiningSet[]          = {2,6,10};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = NumberGraph().largestSet(vector <string>(graphSet, graphSet + (sizeof graphSet / sizeof graphSet[0])), vector <int>(joiningSet, joiningSet + (sizeof joiningSet / sizeof joiningSet[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string graphSet[]         = {"4 11 12 10 9 6 2 7 1 8 5"};
			int joiningSet[]          = {3,5,1,7};
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = NumberGraph().largestSet(vector <string>(graphSet, graphSet + (sizeof graphSet / sizeof graphSet[0])), vector <int>(joiningSet, joiningSet + (sizeof joiningSet / sizeof joiningSet[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string graphSet[]         = {"100 260 164 244 84 340 52 2"
,"12 388 4 308 180 228 484"};
			int joiningSet[]          = {16,176,208,48,240,80};
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = NumberGraph().largestSet(vector <string>(graphSet, graphSet + (sizeof graphSet / sizeof graphSet[0])), vector <int>(joiningSet, joiningSet + (sizeof joiningSet / sizeof joiningSet[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string graphSet[]         = {"10 6 130 162 164 39 73 27 72 167 41"};
			int joiningSet[]          = {3,63,95,123,57,91,35,137 ,135,125,33,121,17,5,31 ,45,67,29,157};
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = NumberGraph().largestSet(vector <string>(graphSet, graphSet + (sizeof graphSet / sizeof graphSet[0])), vector <int>(joiningSet, joiningSet + (sizeof joiningSet / sizeof joiningSet[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string graphSet[]         = {"2136 2108 876 8"
,"6 348 8 1784 1146 1596 608 446 14"
,"64"
," 344 1452 1938 692 376 1482 860 1870"};
			int joiningSet[]          = {644,844,348,604,1260,516,868,2100,260 ,1492,316,1076,268,852,12,1500,4,772 ,1108,188,1444,1764,84,1732,532,332 ,1588,500,700,1116,252,1060,68,1092 ,724,132,484,340,684,1276,28,1788,588};
			int expected__            = 12;

			clock_t start__           = clock();
			int received__            = NumberGraph().largestSet(vector <string>(graphSet, graphSet + (sizeof graphSet / sizeof graphSet[0])), vector <int>(joiningSet, joiningSet + (sizeof joiningSet / sizeof joiningSet[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string graphSet[]         = {"1000000"};
			int joiningSet[]          = {1};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = NumberGraph().largestSet(vector <string>(graphSet, graphSet + (sizeof graphSet / sizeof graphSet[0])), vector <int>(joiningSet, joiningSet + (sizeof joiningSet / sizeof joiningSet[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string graphSet[]         = {"1 2 3 4 5 6 7 8"};
			int joiningSet[]          = {1};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = NumberGraph().largestSet(vector <string>(graphSet, graphSet + (sizeof graphSet / sizeof graphSet[0])), vector <int>(joiningSet, joiningSet + (sizeof joiningSet / sizeof joiningSet[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string graphSet[]         = ;
			int joiningSet[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = NumberGraph().largestSet(vector <string>(graphSet, graphSet + (sizeof graphSet / sizeof graphSet[0])), vector <int>(joiningSet, joiningSet + (sizeof joiningSet / sizeof joiningSet[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string graphSet[]         = ;
			int joiningSet[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = NumberGraph().largestSet(vector <string>(graphSet, graphSet + (sizeof graphSet / sizeof graphSet[0])), vector <int>(joiningSet, joiningSet + (sizeof joiningSet / sizeof joiningSet[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string graphSet[]         = ;
			int joiningSet[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = NumberGraph().largestSet(vector <string>(graphSet, graphSet + (sizeof graphSet / sizeof graphSet[0])), vector <int>(joiningSet, joiningSet + (sizeof joiningSet / sizeof joiningSet[0])));
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
