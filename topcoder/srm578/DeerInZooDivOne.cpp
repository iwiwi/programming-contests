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

struct DeerInZooDivOne {
  int getmax(vector <int> a, vector <int> b);
};

namespace MCF {
const int MAX_V = 1010;
struct e_t { int to, init, cap, cst, rev; };
int V;

vector<e_t> adj[MAX_V];
double h[MAX_V];
int ex[MAX_V], iter[MAX_V];
bool visit[MAX_V];

void add_edge(int i, int j, int cap, int cst) {
  adj[i].push_back((e_t){j, cap, cap, +cst, adj[j].size()});
  adj[j].push_back((e_t){i,   0,   0, -cst, adj[i].size() - 1});
}

void dfs(int v) {
  visit[v] = true;
  rep (i, adj[v].size()) {
    e_t &e = adj[v][i];
    if (e.cap > 0 && !visit[e.to] && e.cst + h[v] - h[e.to] < 0) dfs(e.to);
  }
}

int dfs(int v, int f) {
  if (ex[v] < 0) {
    int d = min(f, -ex[v]);
    ex[v] += d;
    return d;
  }
  for (; iter[v] < (int)adj[v].size(); ++iter[v]) {
    e_t &e = adj[v][iter[v]];
    if (e.cap > 0 && e.cst + h[v] - h[e.to] < 0) {
      int d = dfs(e.to, min(f, e.cap));
      if (d > 0) {
        e.cap -= d;
        adj[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int min_cost_circulation() {
  double eps = 0;
  rep (v, V) rep (i, adj[v].size()) if (adj[v][i].cap > 0) eps = max(eps, -(double)adj[v][i].cst);
  while (eps * (V + 1) > 1) {
    eps /= 4;
    rep (v, V) rep (i, adj[v].size()) {
      e_t &e = adj[v][i];
      if (e.cap > 0 && e.cst + h[v] - h[e.to] < 0) {
        ex[e.to] += e.cap;
        ex[v] -= e.cap;
        adj[e.to][e.rev].cap += e.cap;
        e.cap = 0;
      }
    }
    for (;;) {
      rep (v, V) visit[v] = false;
      rep (v, V) if (ex[v] > 0) dfs(v);
      rep (v, V) if (visit[v]) h[v] -= eps;
      rep (v, V) iter[v] = 0;
      bool ok = true;
      rep (v, V) {
        for (int f; ex[v] > 0 && (f = dfs(v, ex[v])) > 0; ) ex[v] -= f;
        if (ex[v] > 0) ok = false;
      }
      if (ok) break;
    }
  }
  int res = 0;
  rep (v, V) rep (i, adj[v].size()) {
    e_t &e = adj[v][i];
    if (e.init > e.cap) res += e.cst * (e.init - e.cap);
  }
  return res;
}
}  // namespace MCF



typedef pair<int, int> pii;

map<pair<pii, pii>, int> mem;

int N;
vector<int> adj[60];

int doit(int r1, int p1, int r2, int p2) {
  pair<int, int> z1 = mp(r1, p1), z2 = mp(r2, p2);
  pair<pii, pii> key = mp(min(z1, z2), max(z1, z2));
  if (mem.count(key)) return mem[key];

  vector<pair<pair<int, int>, int> > es;
  rep (i1, adj[r1].size()) rep (i2, adj[r2].size()) {
    int v1 = adj[r1][i1], v2 = adj[r2][i2];
    if (v1 == p1 || v2 == p2) continue;
    int gain = doit(v1, r1, v2, r2);
    es.pb(mp(mp(i1, i2), gain));
  }

  int L = adj[r1].size();
  int R = adj[r2].size();
  MCF::V = L + R + 2;
  int S = L + R;
  int T = L + R + 1;
  rep (v, MCF::V) MCF::adj[v].clear();
  MCF::add_edge(T, S, 100, 0);
  rep (i1, L) MCF::add_edge(S     , i1, 1, 0);
  rep (i2, R) MCF::add_edge(L + i2, T, 1, 0);
  rep (i, es.size()) {
    MCF::add_edge(es[i].first.first, L + es[i].first.second, 1, -es[i].second);
  }

  int res = 1 + -MCF::min_cost_circulation();
  return mem[key] = res;
}

vector<int> cc2;

void compute_cc(int v, int p) {
  cc2.pb(v);
  rep (i, adj[v].size()) if (adj[v][i] != p) compute_cc(adj[v][i], v);
}

int DeerInZooDivOne::getmax(vector <int> a, vector <int> b) {
  N = a.size() + 1;
  rep (v, N) adj[v].clear();
  rep (i, N - 1) {
    adj[a[i]].pb(b[i]);
    adj[b[i]].pb(a[i]);
  }

  int ans = 0;
  mem.clear();

  rep (r1, N) {
    int n1 = adj[r1].size();
    rep (i1, n1) {
      int p1 = adj[r1][0];

      adj[r1].erase(find(all(adj[r1]), p1));
      adj[p1].erase(find(all(adj[p1]), r1));

      cc2.clear();
      compute_cc(p1, -1);

      mem.clear();
      rep (i2, cc2.size()) {
        int r2 = cc2[i2];
        ans = max(ans, doit(r1, p1, r2, -1));
      }

      adj[r1].pb(p1);
      adj[p1].pb(r1);
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
			int a[]                   = {0, 1, 2};
			int b[]                   = {1, 2, 3};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {1, 8, 1, 7, 4, 2, 5, 2};
			int b[]                   = {5, 3, 6, 8, 2, 6, 8, 0};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {0};
			int b[]                   = {1};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {0, 11, 10, 10, 19, 17, 6, 17, 19, 10, 10, 11, 9, 9, 14, 2, 13, 11, 6};
			int b[]                   = {7, 5, 2, 12, 8, 9, 16, 8, 4, 18, 8, 13, 15, 13, 17, 16, 3, 1, 7};
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {14, 13, 28, 15, 20, 4, 9, 6, 1, 23, 19, 25, 25, 8, 14, 16, 2, 8, 15, 25, 22, 22, 28, 10, 10, 14, 24, 27, 8};
			int b[]                   = {21, 5, 12, 13, 27, 1, 24, 17, 27, 17, 23, 14, 18, 26, 7, 26, 11, 0, 25, 23, 3, 29, 22, 11, 22, 29, 15, 28, 29};
			int expected__            = 11;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
        int a[]                   = {7, 0, 1, 13, 22, 3, 16, 21, 25, 21, 5, 5, 3, 20, 20, 19, 21, 1, 20, 1, 26, 25, 24, 12, 18, 21, 9, 29, 28};
			int b[]                   = {15, 13, 29, 15, 14, 8, 15, 24, 1, 27, 10, 12, 4, 21, 8, 26, 6, 20, 2, 26, 14, 17, 23, 21, 25, 13, 6, 11, 19};
			int expected__            = 12;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 6: {
        int a[]                   = {13, 0, 1, 10, 18, 13, 5, 11, 3, 11, 4, 1, 19, 16, 15, 16, 3, 17, 8};
        int b[]                   = {11, 8, 17, 7, 7, 9, 13, 0, 5, 12, 11, 14, 0, 7, 3, 19, 2, 11, 6};
        int expected__            = 8;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			int a[]                   = ;
			int b[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
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
