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

struct PointyWizardHats {
  int getNumHats(vector <int> topHeight, vector <int> topRadius, vector <int> bottomHeight, vector <int> bottomRadius);
};

const int MAX_V = 510;

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


namespace enemy {

/*
int solve(vector <int> bh, vector <int> br, vector <int> ah, vector <int> ar) {
  int Na = ah.size();
  int Nb = bh.size();
  vector<pair<int, int> > A;
  rep (i, ah.size()) A.pb(mp(ar[i], ah[i]));
  sort(all(A));

  vector<bool> FREE(Nb, true);
  int RES = 0;
  rep (a, Na) {
    int best = -1;
    rep (b, Nb)
        if (FREE[b])
          if (br[b] < A[a].first)
            if (A[a].first * (long long)bh[b] > A[a].second*(long long)br[b]) {
              if (best == -1) best = b;
              else if (br[b] * (long long)bh[best] > bh[b] * (long long)br[best]) best = b;
            }
    if (best > -1) {
      FREE[best] = false;
      RES++;
    }
  }
  return RES;
}
*/

int cap[10000], vv[10000];
vector<int> adj[2000];
queue<int> fila;
int S, T, pai[2000], apai[2000];
bool mk[2000];

class SS{
 public:
  double x, y;
  void pdt(int a, int b) {
    x = double(b) / double(a);
    y = double(b);
  }
};

SS a[100], b[100];

int fluxo() {
  for (int i = 0; i <= T; ++i) mk[i] = false;
  while (fila.size()) fila.pop();

  mk[S] = true;
  fila.push(S);
}
};

typedef long long ll;

int PointyWizardHats::getNumHats(vector <int> topHeight, vector <int> topRadius,
                                 vector <int> bottomHeight, vector <int> bottomRadius) {
  //return enemy::solve(topHeight, topRadius, bottomHeight, bottomRadius);

  L = topHeight.size();
  R = bottomHeight.size();
  memset(adj, 0, sizeof(adj));

  rep (i, L) rep (j, R) {
    ll th = topHeight[i], tr = topRadius[i];
    ll bh = bottomHeight[j], br = bottomRadius[j];
    adj[i][j] = tr * bh < br * th && tr < br;
  }

  return bipartite_matching();
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
			int topHeight[]           = {30};
			int topRadius[]           = {3};
			int bottomHeight[]        = {3};
			int bottomRadius[]        = {30};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = PointyWizardHats().getNumHats(vector <int>(topHeight, topHeight + (sizeof topHeight / sizeof topHeight[0])), vector <int>(topRadius, topRadius + (sizeof topRadius / sizeof topRadius[0])), vector <int>(bottomHeight, bottomHeight + (sizeof bottomHeight / sizeof bottomHeight[0])), vector <int>(bottomRadius, bottomRadius + (sizeof bottomRadius / sizeof bottomRadius[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int topHeight[]           = {4,4};
			int topRadius[]           = {4,3};
			int bottomHeight[]        = {5,12};
			int bottomRadius[]        = {5,4};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = PointyWizardHats().getNumHats(vector <int>(topHeight, topHeight + (sizeof topHeight / sizeof topHeight[0])), vector <int>(topRadius, topRadius + (sizeof topRadius / sizeof topRadius[0])), vector <int>(bottomHeight, bottomHeight + (sizeof bottomHeight / sizeof bottomHeight[0])), vector <int>(bottomRadius, bottomRadius + (sizeof bottomRadius / sizeof bottomRadius[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int topHeight[]           = {3};
			int topRadius[]           = {3};
			int bottomHeight[]        = {1,1};
			int bottomRadius[]        = {2,4};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = PointyWizardHats().getNumHats(vector <int>(topHeight, topHeight + (sizeof topHeight / sizeof topHeight[0])), vector <int>(topRadius, topRadius + (sizeof topRadius / sizeof topRadius[0])), vector <int>(bottomHeight, bottomHeight + (sizeof bottomHeight / sizeof bottomHeight[0])), vector <int>(bottomRadius, bottomRadius + (sizeof bottomRadius / sizeof bottomRadius[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int topHeight[]           = {10,10};
			int topRadius[]           = {2,5};
			int bottomHeight[]        = {2,9};
			int bottomRadius[]        = {3,6};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = PointyWizardHats().getNumHats(vector <int>(topHeight, topHeight + (sizeof topHeight / sizeof topHeight[0])), vector <int>(topRadius, topRadius + (sizeof topRadius / sizeof topRadius[0])), vector <int>(bottomHeight, bottomHeight + (sizeof bottomHeight / sizeof bottomHeight[0])), vector <int>(bottomRadius, bottomRadius + (sizeof bottomRadius / sizeof bottomRadius[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int topHeight[]           = {3,4,5};
			int topRadius[]           = {5,4,3};
			int bottomHeight[]        = {3,4,5};
			int bottomRadius[]        = {3,8,5};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = PointyWizardHats().getNumHats(vector <int>(topHeight, topHeight + (sizeof topHeight / sizeof topHeight[0])), vector <int>(topRadius, topRadius + (sizeof topRadius / sizeof topRadius[0])), vector <int>(bottomHeight, bottomHeight + (sizeof bottomHeight / sizeof bottomHeight[0])), vector <int>(bottomRadius, bottomRadius + (sizeof bottomRadius / sizeof bottomRadius[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int topHeight[]           = {1,2,3,4,5};
			int topRadius[]           = {2,3,4,5,6};
			int bottomHeight[]        = {2,3,4,5,6};
			int bottomRadius[]        = {1,2,3,4,5};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = PointyWizardHats().getNumHats(vector <int>(topHeight, topHeight + (sizeof topHeight / sizeof topHeight[0])), vector <int>(topRadius, topRadius + (sizeof topRadius / sizeof topRadius[0])), vector <int>(bottomHeight, bottomHeight + (sizeof bottomHeight / sizeof bottomHeight[0])), vector <int>(bottomRadius, bottomRadius + (sizeof bottomRadius / sizeof bottomRadius[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int topHeight[]           = {123,214,232,323,342,343};
			int topRadius[]           = {123,123,232,123,323,434};
			int bottomHeight[]        = {545,322,123,545,777,999};
			int bottomRadius[]        = {323,443,123,656,767,888};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = PointyWizardHats().getNumHats(vector <int>(topHeight, topHeight + (sizeof topHeight / sizeof topHeight[0])), vector <int>(topRadius, topRadius + (sizeof topRadius / sizeof topRadius[0])), vector <int>(bottomHeight, bottomHeight + (sizeof bottomHeight / sizeof bottomHeight[0])), vector <int>(bottomRadius, bottomRadius + (sizeof bottomRadius / sizeof bottomRadius[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			int topHeight[]           = {999,999,999,10000,10000,10000};
			int topRadius[]           = {10000,10000,10000,1,2,3};
			int bottomHeight[]        = {2324,2323,234,5454,323,232};
			int bottomRadius[]        = {1,2,3222,434,5454,23};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = PointyWizardHats().getNumHats(vector <int>(topHeight, topHeight + (sizeof topHeight / sizeof topHeight[0])), vector <int>(topRadius, topRadius + (sizeof topRadius / sizeof topRadius[0])), vector <int>(bottomHeight, bottomHeight + (sizeof bottomHeight / sizeof bottomHeight[0])), vector <int>(bottomRadius, bottomRadius + (sizeof bottomRadius / sizeof bottomRadius[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 8: {
			int topHeight[]           = ;
			int topRadius[]           = ;
			int bottomHeight[]        = ;
			int bottomRadius[]        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PointyWizardHats().getNumHats(vector <int>(topHeight, topHeight + (sizeof topHeight / sizeof topHeight[0])), vector <int>(topRadius, topRadius + (sizeof topRadius / sizeof topRadius[0])), vector <int>(bottomHeight, bottomHeight + (sizeof bottomHeight / sizeof bottomHeight[0])), vector <int>(bottomRadius, bottomRadius + (sizeof bottomRadius / sizeof bottomRadius[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int topHeight[]           = ;
			int topRadius[]           = ;
			int bottomHeight[]        = ;
			int bottomRadius[]        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PointyWizardHats().getNumHats(vector <int>(topHeight, topHeight + (sizeof topHeight / sizeof topHeight[0])), vector <int>(topRadius, topRadius + (sizeof topRadius / sizeof topRadius[0])), vector <int>(bottomHeight, bottomHeight + (sizeof bottomHeight / sizeof bottomHeight[0])), vector <int>(bottomRadius, bottomRadius + (sizeof bottomRadius / sizeof bottomRadius[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			int topHeight[]           = ;
			int topRadius[]           = ;
			int bottomHeight[]        = ;
			int bottomRadius[]        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PointyWizardHats().getNumHats(vector <int>(topHeight, topHeight + (sizeof topHeight / sizeof topHeight[0])), vector <int>(topRadius, topRadius + (sizeof topRadius / sizeof topRadius[0])), vector <int>(bottomHeight, bottomHeight + (sizeof bottomHeight / sizeof bottomHeight[0])), vector <int>(bottomRadius, bottomRadius + (sizeof bottomRadius / sizeof bottomRadius[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}

void out(vector<int> v) {
  rep (i, v.size()) printf("%d%c", v[i], i + 1 == v.size() ? '\n' : ' ');
}

int main(int argc, char *argv[]) {
  while (true) {
    int L = 1 + rand() % 50;
    int R = 1 + rand() % 50;

    vector<int> TH(L), TR(L), BH(R), BR(R);
    rep (i, L) { TH[i] = 1 + rand() % 10000; TR[i] = 1 + rand() % 10000; }
    rep (i, R) { BH[i] = 1 + rand() % 10000; BR[i] = 1 + rand() % 10000; }

    int my = PointyWizardHats().getNumHats(TH, TR, BH, BR);
    int en = enemy::solve(TH, TR, BH, BR);
    if (my != en) {
      out(TH);
      out(TR);
      out(BH);
      out(BR);
      break;
    }
  }

	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
