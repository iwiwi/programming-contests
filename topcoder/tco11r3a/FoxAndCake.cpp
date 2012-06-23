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

struct FoxAndCake {
  string ableToDivide(int n, int m, vector <int> x, vector <int> y);
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

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int W, H;
char fld[1010][1010];

int vid(int x, int y) {
  assert(0 <= x && x < W);
  assert(0 <= y && y < H);
  return (y * W + x) * 2;
}

string FoxAndCake::ableToDivide(int W0, int H0, vector <int> X0, vector <int> Y0) {
  map<int, int> xs, ys;

  rep (i, 7) {
    for (int d = -5; d <= 5; ++d) {
      int tx = X0[i] + d, ty = Y0[i] + d;
      if (1 <= tx && tx <= W0) xs.insert(mp(tx, 0));
      if (1 <= ty && ty <= H0) ys.insert(mp(ty, 0));
    }
  }

  W = 0, H = 0;
  tr (xs, ite) ite->second = W++;
  tr (ys, ite) ite->second = H++;

  V = W * H * 2 + 2;
  S = W * H * 2;
  T = W * H * 2 + 1;
  rep (v, V) adj[v].clear();

  printf("V = %d\n", V);

  rep (y, H) {
    rep (x, W) {
      rep (i, 7) {
        if (mp(x, y) == mp(xs[X0[i]], ys[Y0[i]])) {
          printf("%c", "#SSSCCC"[i]);
          goto done;
        }
      }
      printf(".");
   done:;
    }
    puts("");
  }

  rep (y, H) rep (x, W) {
    if (mp(x, y) == mp(xs[X0[0]], ys[Y0[0]])) continue;  // '#'

    add_edge(vid(x, y), vid(x, y) + 1, 1);
    rep (d, 4) {
      int tx = x + dx[d], ty = y + dy[d];
      if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
      add_edge(vid(x, y) + 1, vid(tx, ty), 1);
    }
  }

  rep (i, 3) {
    int s = vid(xs[X0[1 + i]], ys[Y0[1 + i]]);
    int t = vid(xs[X0[4 + i]], ys[Y0[4 + i]]) + 1;
    add_edge(S, s, 1);
    add_edge(t, T, 1);
  }

  int f = max_flow();
  if (f == 3) return "Yes";
  else return "No";
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
			int n                     = 2;
			int m                     = 4;
			int x[]                   = {1,1,1,1,2,2,2};
			int y[]                   = {1,2,3,4,2,3,4};
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = FoxAndCake().ableToDivide(n, m, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 2;
			int m                     = 4;
			int x[]                   = {1,1,2,1,2,1,2};
			int y[]                   = {1,2,2,3,3,4,4};
			string expected__         = "No";

			clock_t start__           = clock();
			string received__         = FoxAndCake().ableToDivide(n, m, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 6;
			int m                     = 6;
			int x[]                   = {1,1,3,4,3,4,5};
			int y[]                   = {2,6,4,5,5,4,2};
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = FoxAndCake().ableToDivide(n, m, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 999999999;
			int m                     = 999999999;
			int x[]                   = {500000000,1,1,1,999999999,999999999,999999999};
			int y[]                   = {500000000,1,2,3,999999997,999999998,999999999};
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = FoxAndCake().ableToDivide(n, m, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 1000000000;
			int m                     = 1000000000;
			int x[]                   = {500000000,1,1,2,999999998,999999999,999999999};
			int y[]                   = {500000000,1,2,1,999999999,999999998,999999999};
			string expected__         = "No";

			clock_t start__           = clock();
			string received__         = FoxAndCake().ableToDivide(n, m, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
        int n                     = 123421412;
			int m                     = 352432432;
			int x[]                   = {23423, 423432, 51243, 32423, 1, 1, 2};
			int y[]                   = {1232, 45435, 34324, 32423, 1, 2, 1};
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = FoxAndCake().ableToDivide(n, m, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int n                     = ;
			int m                     = ;
			int x[]                   = ;
			int y[]                   = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndCake().ableToDivide(n, m, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int n                     = ;
			int m                     = ;
			int x[]                   = ;
			int y[]                   = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndCake().ableToDivide(n, m, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
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
