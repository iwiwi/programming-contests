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

struct OldBridges {
  string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn);
};

const int MAX_V = 20010;

struct e_t { int to, cap, rev; };

int V, S, T;
vector<e_t> adj[MAX_V];

int lev[MAX_V], done[MAX_V];

void add_edge(int i, int j, int c) {
  adj[i].push_back((e_t){j, c, adj[j].size()});
  adj[j].push_back((e_t){i, 0, adj[i].size() - 1});
}

bool levelize() {
  memset(lev, -1, sizeof(lev));
  queue<int> que;
  lev[S] = 0;
  que.push(S);
  while (!que.empty()) {
    int v = que.front(); que.pop();
    rep (i, adj[v].size()) {
      e_t &e = adj[v][i];
      if (!e.cap || lev[e.to] != -1) continue;
      lev[e.to] = lev[v] + 1;
      que.push(e.to);
    }
  }
  return lev[T] != -1;
}

int augment(int v, int f) {
  if (v == T || !f) return f;
  for (; done[v] < (int)adj[v].size(); done[v]++) {
    e_t &e = adj[v][done[v]];
    if (lev[e.to] <= lev[v]) continue;
    int t = augment(e.to, min(f, e.cap));
    if (t > 0) {
      e.cap -= t;
      adj[e.to][e.rev].cap += t;
      return t;
    }
  }
  return 0;
}

int max_flow() {
  int f = 0, t;
  while (levelize()) {
    memset(done, 0, sizeof(done));
    while (t = augment(S, INT_MAX)) f += t;
  }
  return f;
}

int N;
vector<string> B;

int eid(int v, int w) {
  return N + 2 * (min(v, w) * N + max(v, w));
}

void construct() {
  V = N + N * N * 2;
  rep (v, V) adj[v].clear();

  rep (v, N) rep (w, v) if (B[v][w] != 'X') {
    int e = eid(v, w);
    add_edge(e, e^1, B[v][w] == 'O' ? 2 : 500);
  }

  rep (v, N) {
    rep (w, N) if (B[v][w] != 'X') {
      int e = eid(v, w);
      add_edge(v, e, 500);
      add_edge(e^1, v, 500);
    }
  }
}


string OldBridges::isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn) {
  B = bridges;
  N = bridges.size();

  {
    construct();
    S = a1;
    T = a2;
    if (max_flow() < an * 2) return "No";
  }
  {
    construct();
    S = b1;
    T = b2;
    if (max_flow() < bn * 2) return "No";
  }
  {
    construct();
    S = V++;
    T = V++;
    add_edge(S, a1, an * 2); add_edge(a2, T, an * 2);
    add_edge(S, b1, bn * 2); add_edge(b2, T, bn * 2);
    int f = max_flow();
    if (f < (an + bn) * 2) return "No";
  }
  {
    construct();
    S = V++;
    T = V++;
    add_edge(S, a1, an * 2); add_edge(a2, T, an * 2);
    add_edge(S, b2, bn * 2); add_edge(b1, T, bn * 2);
    int f = max_flow();
    if (f < (an + bn) * 2) return "No";
  }
  return "Yes";
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

	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) {
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
			cerr << "    Expected: \"" << expected << "\"" << endl;
			cerr << "    Received: \"" << received << "\"" << endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string bridges[]          = {"XOXX","OXOX","XOXO","XXOX"};
			int a1                    = 0;
			int a2                    = 1;
			int an                    = 1;
			int b1                    = 2;
			int b2                    = 3;
			int bn                    = 1;
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = OldBridges().isPossible(vector <string>(bridges, bridges + (sizeof bridges / sizeof bridges[0])), a1, a2, an, b1, b2, bn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string bridges[]          = {"XOXX","OXOX","XOXO","XXOX"};
			int a1                    = 0;
			int a2                    = 2;
			int an                    = 1;
			int b1                    = 1;
			int b2                    = 3;
			int bn                    = 1;
			string expected__         = "No";

			clock_t start__           = clock();
			string received__         = OldBridges().isPossible(vector <string>(bridges, bridges + (sizeof bridges / sizeof bridges[0])), a1, a2, an, b1, b2, bn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string bridges[]          = {"XOXO","OXOX","XOXO","OXOX"};
			int a1                    = 0;
			int a2                    = 2;
			int an                    = 1;
			int b1                    = 1;
			int b2                    = 3;
			int bn                    = 1;
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = OldBridges().isPossible(vector <string>(bridges, bridges + (sizeof bridges / sizeof bridges[0])), a1, a2, an, b1, b2, bn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string bridges[]          = {"XNXO","NXOX","XOXO","OXOX"};
			int a1                    = 0;
			int a2                    = 2;
			int an                    = 1;
			int b1                    = 1;
			int b2                    = 3;
			int bn                    = 2;
			string expected__         = "No";

			clock_t start__           = clock();
			string received__         = OldBridges().isPossible(vector <string>(bridges, bridges + (sizeof bridges / sizeof bridges[0])), a1, a2, an, b1, b2, bn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string bridges[]          = {"XOXOO","OXOXO","XOXOO","OXOXO","OOOOX"};
			int a1                    = 0;
			int a2                    = 2;
			int an                    = 2;
			int b1                    = 1;
			int b2                    = 3;
			int bn                    = 2;
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = OldBridges().isPossible(vector <string>(bridges, bridges + (sizeof bridges / sizeof bridges[0])), a1, a2, an, b1, b2, bn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string bridges[]          = {"XOOOX","OXOOX","OOXOX","OOOXN","XXXNX"};
			int a1                    = 0;
			int a2                    = 4;
			int an                    = 3;
			int b1                    = 1;
			int b2                    = 2;
			int bn                    = 2;
			string expected__         = "No";

			clock_t start__           = clock();
			string received__         = OldBridges().isPossible(vector <string>(bridges, bridges + (sizeof bridges / sizeof bridges[0])), a1, a2, an, b1, b2, bn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string bridges[]          = ;
			int a1                    = ;
			int a2                    = ;
			int an                    = ;
			int b1                    = ;
			int b2                    = ;
			int bn                    = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = OldBridges().isPossible(vector <string>(bridges, bridges + (sizeof bridges / sizeof bridges[0])), a1, a2, an, b1, b2, bn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string bridges[]          = ;
			int a1                    = ;
			int a2                    = ;
			int an                    = ;
			int b1                    = ;
			int b2                    = ;
			int bn                    = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = OldBridges().isPossible(vector <string>(bridges, bridges + (sizeof bridges / sizeof bridges[0])), a1, a2, an, b1, b2, bn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string bridges[]          = ;
			int a1                    = ;
			int a2                    = ;
			int an                    = ;
			int b1                    = ;
			int b2                    = ;
			int bn                    = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = OldBridges().isPossible(vector <string>(bridges, bridges + (sizeof bridges / sizeof bridges[0])), a1, a2, an, b1, b2, bn);
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
