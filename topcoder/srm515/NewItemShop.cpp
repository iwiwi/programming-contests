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

struct NewItemShop {
  double getMaximum(int swords, vector <string> customers);
};

const int T = 24;

int N2, N;
int I[30], C[30];
double P[30];

bool vis[30][30][1 << 12];
double mem[30][30][1 << 12];

double search(int t, int s, int b) {
  if (t == T || s == 0) return 0.0;
  if (C[t] == -1) return search(t + 1, s, b);

  if (vis[t][s][b]) return mem[t][s][b];
  int i = I[t], c = C[t];
  double p = P[t];
  double res = 0.0;

  if (i >= 0 && 0 == (b & (1 << i))) {
    res = search(t + 1, s, b);
  } else {
    // not come
    res += (1.0 - p) * search(t + 1, s, b);

    // come
    int tb = i == -1 ? b : b - (1 << i);
    res += p * max(search(t + 1, s, tb),
                   search(t + 1, s - 1, tb) + c);
  }

  vis[t][s][b] = true;
  return mem[t][s][b] = res;
}

double NewItemShop::getMaximum(int swords, vector <string> customers) {
  N = customers.size();
  N2 = 0;

  memset(I, -1, sizeof(I));
  memset(C, -1, sizeof(C));
  memset(P, -1, sizeof(P));

  rep (i, customers.size()) {
    int myid = count(all(customers[i]), ' ') > 0 ? N2++ : -1;

    vector<pair<int, pair<int, int> > > v;

    stringstream ss(customers[i]);
    for (string s; ss >> s; ) {
      int t, c, p;
      sscanf(s.c_str(), "%d,%d,%d", &t, &c, &p);
      v.pb(mp(t, mp(c, p)));
    }

    double ps = 100;
    rep (i, v.size()) {
      int t = v[i].first, c = v[i].second.first, p = v[i].second.second;
      I[t] = myid;
      C[t] = c;
      P[t] = p / ps;
      ps -= p;
    }
  }

  memset(vis, 0, sizeof(vis));
  return search(0, swords, (1 << N2) - 1);
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
			int swords                = 1;
			string customers[]        = { "8,1,80 16,100,11", "12,10,100" };
			double expected__         = 19.0;

			clock_t start__           = clock();
			double received__         = NewItemShop().getMaximum(swords, vector <string>(customers, customers + (sizeof customers / sizeof customers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int swords                = 2;
			string customers[]        = { "8,1,80 16,100,11", "12,10,100" };
			double expected__         = 21.8;

			clock_t start__           = clock();
			double received__         = NewItemShop().getMaximum(swords, vector <string>(customers, customers + (sizeof customers / sizeof customers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int swords                = 1;
			string customers[]        = { "0,90,25 2,90,25 4,90,25 6,90,25", "7,100,80" };
			double expected__         = 90.0;

			clock_t start__           = clock();
			double received__         = NewItemShop().getMaximum(swords, vector <string>(customers, customers + (sizeof customers / sizeof customers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int swords                = 3;
			string customers[]        = { "17,31,41 20,59,26 23,53,5", "19,89,79", "16,32,38 22,46,26", "18,43,38 21,32,7" };
			double expected__         = 135.5121414;

			clock_t start__           = clock();
			double received__         = NewItemShop().getMaximum(swords, vector <string>(customers, customers + (sizeof customers / sizeof customers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int swords                = 5;
			string customers[]        = { "1,1,10", "2,2,9", "3,3,8", "4,4,7", "5,5,6", "6,6,5", "7,7,4", "8,8,3", "9,9,2", "10,10,1" };
			double expected__         = 2.1999744634845344;

			clock_t start__           = clock();
			double received__         = NewItemShop().getMaximum(swords, vector <string>(customers, customers + (sizeof customers / sizeof customers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
        int swords                = 1;
			string customers[]        = {"1,1,1"};
			double expected__         = 0.01;

			clock_t start__           = clock();
			double received__         = NewItemShop().getMaximum(swords, vector <string>(customers, customers + (sizeof customers / sizeof customers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int swords                = ;
			string customers[]        = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = NewItemShop().getMaximum(swords, vector <string>(customers, customers + (sizeof customers / sizeof customers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int swords                = ;
			string customers[]        = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = NewItemShop().getMaximum(swords, vector <string>(customers, customers + (sizeof customers / sizeof customers[0])));
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
