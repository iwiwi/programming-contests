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

struct RabbitWorking {
  double getMaximum(vector <string> profit);
};

const double EPS = 1E-10;
const int MAX_V = 100010;

struct e_t {
  int to;
  double cap;
  int rev;
};

int V, S, T;
vector<e_t> adj[MAX_V];

int lev[MAX_V], done[MAX_V];

void add_edge(int i, int j, double c) {
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
      if (e.cap <= EPS || lev[e.to] != -1) continue;
      lev[e.to] = lev[v] + 1;
      que.push(e.to);
    }
  }
  return lev[T] != -1;
}

double augment(int v, double f) {
  if (v == T || f < EPS) return f;
  for (; done[v] < (int)adj[v].size(); done[v]++) {
    e_t &e = adj[v][done[v]];
    if (lev[e.to] != lev[v] + 1) continue;
    double t = augment(e.to, min(f, e.cap));
    if (t > EPS) {
      e.cap -= t;
      adj[e.to][e.rev].cap += t;
      return t;
    }
  }
  return 0;
}

double max_flow() {
  double f = 0, t;
  while (levelize()) {
    memset(done, 0, sizeof(done));
    while (EPS < (t = augment(S, 1E30))) f += t;
  }
  return f;
}

double RabbitWorking::getMaximum(vector <string> profit) {
  int N = profit.size();

  double lb = 0.0, ub = 10.0;
  rep (iter, 100) {
    double x = (lb + ub) / 2.0;

    V = N + (N * (N - 1) / 2) + 2;
    S = N + (N * (N - 1) / 2);
    T = N + (N * (N - 1) / 2) + 1;
    rep (v, V) adj[v].clear();

    double f = 0;
    rep (i, N) {
      add_edge(S, i, 199 * x);
      f += 199 * x;
    }

    int v = N;
    rep (i, N) rep (j, i) {
      add_edge(i, v, 1E30);
      add_edge(j, v, 1E30);
      add_edge(v, T, (profit[i][j] - '0') + 2 * x);
      f += (profit[i][j] - '0') + 2 * x;
      ++v;
    }

    double a = (f - max_flow()) - 199 * x * N;
    if (a >= EPS) lb = x;
    else ub = x;
  }

  return lb;
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

	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ(double expected, double result) { if (isnan(expected)) { return isnan(result); } else if (isinf(expected)) { if (expected > 0) { return result > 0 && isinf(result); } else { return result < 0 && isinf(result); } } else if (isnan(result) || isinf(result)) { return false; } else if (fabs(result - expected) < MAX_DOUBLE_ERROR) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }

	int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) {
		cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received);
			if (rerr > 0) {
				sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			string profit[]           = { "071",
  "702",
  "120" }
;
			double expected__         = 0.017676767676767676;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string profit[]           = { "061",
  "602",
  "120" }
;
			double expected__         = 0.015228426395939087;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string profit[]           = { "0" }
;
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string profit[]           = { "013040",
  "100010",
  "300060",
  "000008",
  "416000",
  "000800" }
;
			double expected__         = 0.021996615905245348;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string profit[]           = { "06390061",
  "60960062",
  "39090270",
  "96900262",
  "00000212",
  "00222026",
  "66761201",
  "12022610" }
;
			double expected__         = 0.06871794871794872;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			string profit[]           = {"00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000"}
;
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			string profit[]           = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string profit[]           = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
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
