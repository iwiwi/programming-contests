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
#include <complex>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

struct EllysDeathStars {
  double getMax(vector <string> stars, vector <string> ships);
};

typedef complex<double> p_t;
const double EPS = 1e-10;


namespace mf {
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
      if (e.cap < EPS || lev[e.to] != -1) continue;
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
    if (lev[e.to] <= lev[v]) continue;
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
}




double dot(const p_t &p, const p_t &q) { return real(conj(p) * q); }
double det(const p_t &p, const p_t &q) { return imag(conj(p) * q); }

double dist_l_p(const p_t &p, const p_t &a, const p_t &u) {
  return abs(det(p - a, u)) / abs(u);
}

pair<double, double> cross_l_c(p_t a, const p_t &u, const p_t &c, double r) {
  a -= c;
  double b = real(u * conj(a)), d = b * b - norm(u) * (norm(a) - r * r);
  d = max(d, 0.0);
  return make_pair((-b + sqrt(d)) / norm(u), (-b - sqrt(d)) / norm(u));
}



int NSTAR, NSHIP;
p_t S[60];
p_t F[60], T[60], move[60];
double speed[60], range[60], energy[60], end[60];

double EllysDeathStars::getMax(vector <string> stars, vector <string> ships) {
  NSTAR = stars.size();
  rep (i, NSTAR) sscanf(stars[i].c_str(), "%lf %lf", &S[i].real(), &S[i].imag());

  NSHIP = ships.size();
  rep (i, NSHIP) sscanf(ships[i].c_str(), "%lf %lf %lf %lf %lf %lf %lf",
                         &F[i].real(), &F[i].imag(), &T[i].real(), &T[i].imag(),
                         speed + i, range + i, energy + i);

  vector<double> evt;
  rep (i, NSTAR) rep (j, NSHIP) {
    if (T[j] == F[j]) continue;
    if (dist_l_p(S[i], F[j], T[j] - F[j]) > range[j] - EPS) continue;

    p_t m = (T[j] - F[j]);
    m /= abs(m);
    m *= speed[j];
    double e = abs(T[j] - F[j]) / speed[j];

    pair<double, double> c = cross_l_c(F[j], m, S[i], range[j]);
    evt.pb(max(0.0, min(e, c.first)));
    evt.pb(max(0.0, min(e, c.second)));

    move[j] = m;
    end[j] = e;
  }

  sort(all(evt));
  if (evt.size() <= 1) return 0;

  int I = evt.size() - 1;
  mf::V = NSHIP + I * NSTAR + 2;
  mf::S = NSHIP + I * NSTAR;
  mf::T = NSHIP + I * NSTAR + 1;
  rep (v, mf::V) mf::adj[v].clear();

  rep (j, NSHIP) mf::add_edge(mf::S, j, energy[j]);

  rep (k, I) {
    double time = (evt[k + 1] + evt[k]) / 2.0;
    double span = evt[k + 1] - evt[k];
    if (span < EPS) continue;

    rep (i, NSTAR) {
      rep (j, NSHIP) {
        if (time > end[j] + EPS) continue;
        p_t p = F[j] + move[j] * time;
        if (abs(S[i] - p) < range[j]) mf::add_edge(j, NSHIP + k * NSTAR + i, span);
      }

      mf::add_edge(NSHIP + k * NSTAR + i, mf::T, span);
    }
  }

  return mf::max_flow();
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
			string stars[]            = {"2 2"};
			string ships[]            = {"1 1 5 3 2 1 2"};
			double expected__         = 0.894427190999916;

			clock_t start__           = clock();
			double received__         = EllysDeathStars().getMax(vector <string>(stars, stars + (sizeof stars / sizeof stars[0])), vector <string>(ships, ships + (sizeof ships / sizeof ships[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string stars[]            = {"12 10", "7 5"};
			string ships[]            = {"10 10 12 10 1 1 3", "6 1 8 10 1 2 3", "3 6 8 2 5 3 1", "42 42 42 42 6 6 6"};
			double expected__         = 4.983770744659944;

			clock_t start__           = clock();
			double received__         = EllysDeathStars().getMax(vector <string>(stars, stars + (sizeof stars / sizeof stars[0])), vector <string>(ships, ships + (sizeof ships / sizeof ships[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string stars[]            = {"5 77", "60 50", "10 46", "22 97", "87 69"};
			string ships[]            = {"42 17 66 11 5 7 13", "10 10 20 20 3 3 3", "13 15 18 9 4 1 2",
 "99 71 63 81 19 4 60", "27 34 56 43 11 3 12"};
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = EllysDeathStars().getMax(vector <string>(stars, stars + (sizeof stars / sizeof stars[0])), vector <string>(ships, ships + (sizeof ships / sizeof ships[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string stars[]            = {"141 393", "834 847", "568 43", "18 228", "515 794",
 "167 283", "849 333", "719 738", "434 261", "613 800",
 "127 340", "466 938", "598 601"};
			string ships[]            = {"410 951 472 100 337 226 210", "713 352 677 908 731 687 300",
 "191 41 337 92 446 716 213", "598 889 446 907 148 650 203",
 "168 556 470 924 344 369 198", "300 182 350 936 737 533 45",
 "410 871 488 703 746 631 80", "270 777 636 539 172 103 56",
 "466 906 522 98 693 77 309", "768 698 846 110 14 643 14",
 "755 724 664 465 263 759 120"};
			double expected__         = 31.965770956316362;

			clock_t start__           = clock();
			double received__         = EllysDeathStars().getMax(vector <string>(stars, stars + (sizeof stars / sizeof stars[0])), vector <string>(ships, ships + (sizeof ships / sizeof ships[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string stars[]            = ;
			string ships[]            = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = EllysDeathStars().getMax(vector <string>(stars, stars + (sizeof stars / sizeof stars[0])), vector <string>(ships, ships + (sizeof ships / sizeof ships[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string stars[]            = ;
			string ships[]            = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = EllysDeathStars().getMax(vector <string>(stars, stars + (sizeof stars / sizeof stars[0])), vector <string>(ships, ships + (sizeof ships / sizeof ships[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string stars[]            = ;
			string ships[]            = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = EllysDeathStars().getMax(vector <string>(stars, stars + (sizeof stars / sizeof stars[0])), vector <string>(ships, ships + (sizeof ships / sizeof ships[0])));
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
